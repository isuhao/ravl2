// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id: DesignKMeans.cc 3913 2004-01-30 10:57:00Z craftit $"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Cluster/DesignKMeans.cc"

#include "Ravl/PatternRec/DesignKMeans.hh"
#include "Ravl/HSet.hh"
#include "Ravl/Math.hh"
#include "Ravl/SArray1dIter2.hh"
#include "Ravl/SArray1dIter3.hh"
#include "Ravl/PatternRec/SampleIter.hh"
#include "Ravl/PatternRec/DataSet2Iter.hh"
#include "Ravl/PatternRec/ClassifierNearestNeighbour.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/VirtualConstructor.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlN {
  
  //: Load from stream.
  
  DesignKMeansBodyC::DesignKMeansBodyC(istream &strm)
    : DesignClusterBodyC(strm)
  { 
    IntT version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignKMeansBodyC(istream &), Unrecognised version number in stream. ");
    strm >> distance >> k; 
  }
  //: Load from binary stream.
  
  DesignKMeansBodyC::DesignKMeansBodyC(BinIStreamC &strm)
    : DesignClusterBodyC(strm)
  {
    IntT version;
    strm >> version;
    if(version != 0)
      throw ExceptionOutOfRangeC("DesignKMeansBodyC(BinIStreamC &), Unrecognised version number in stream. ");
    strm >> distance >> k; 
  }
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignKMeansBodyC::Save (ostream &out) const {
    if(!DesignClusterBodyC::Save(out))
      return false;
    IntT version = 0;
    out << ' ' << version << ' ' << distance << ' ' <<  k;
    return true;    
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool DesignKMeansBodyC::Save (BinOStreamC &out) const {
    if(!DesignClusterBodyC::Save(out))
      return false;
    IntT version = 0;
    out << version << distance << k;
    return true;
  }
  
  //: Create a clasifier.
  
  FunctionC DesignKMeansBodyC::Apply(const SampleC<VectorC> &in) {
    SArray1dC<VectorC> means = FindMeans(in);
    if(means.Size() == 0)
      return FunctionC();
    return ClassifierNearestNeighbourC(SampleC<VectorC>(means),distance);
  }
  
  //: Create function from the given data, and sample weights.
  
  FunctionC DesignKMeansBodyC::Apply(const SampleC<VectorC> &in,const SampleC<RealT> &weights) {
    SArray1dC<VectorC> means = FindMeans(in,weights);
    if(means.Size() == 0)
      return FunctionC();
    return ClassifierNearestNeighbourC(SampleC<VectorC>(means),distance);    
  }
  
  //: Create a clasifier.
  
  SArray1dC<MeanCovarianceC> DesignKMeansBodyC::Cluster(const SampleC<VectorC> &in) {
    SArray1dC<VectorC> means = FindMeans(in);
    SArray1dC<MeanCovarianceC> ret(means.Size());
    for(SArray1dIter2C<VectorC,MeanCovarianceC> it(means,ret);it;it++)
      it.Data2() = MeanCovarianceC(1,it.Data1(),MatrixC::Identity(it.Data1().Size()));
    return ret;
  }
  
  //: Find means for 'in'.
  
  SArray1dC<VectorC> DesignKMeansBodyC::FindMeans(const SampleC<VectorC> &in) {
    ONDEBUG(cerr << "DesignKMeansBodyC::Apply(), Called with " << in.Size() << " vectors. K=" << k << "\n");
    SArray1dC<VectorC> means(k);
    if(in.Size() == 0) {
      cerr << "DesignKMeansBodyC::Apply(), WARNING: No data samples given. \n";
      return SArray1dC<VectorC>();
    }
    if(in.Size() <= k) {
      cerr << "DesignKMeansBodyC::Apply(), WARNING: Fewer samples than means. \n";
      //return ClassifierNearestNeighbourC(in,distance);
      means = SArray1dC<VectorC>(in.Size());
      SampleIterC<VectorC> sit(in);
      for(SArray1dIterC<VectorC> it(means);it;it++,sit++)
	*it = *sit;
      return means;
    }
    
    // Pick some random points from the set to use as initial means.
    
    HSetC<UIntT> used;
    UIntT index,dim;
    dim = in.First().Size();
    
    for(SArray1dIterC<VectorC> it(means);it;it++) {
      do {
	index = RandomInt() % in.Size();
	if(used[index])
	  continue;
	*it = in[index].Copy();
	used += index;
      } while(0);
    }
    
    // Reassign according to distance.
    
    SArray1dC<VectorC> sums(k);
    SArray1dC<UIntT> counts(k);
    for(SArray1dIter2C<VectorC,UIntT> zit(sums,counts);zit;zit++) {
      zit.Data1() = VectorC(dim);
      zit.Data2() = 0;
    }
    RealT cost = 0,oldcost;
    IntT iters = 0;
    SArray1dIterC<VectorC> mit(means);

    // Update means iteratively.
    
    do {
      oldcost = cost;
      cost = 0;
      
      // Reclassify samples.
      
      for(SampleIterC<VectorC> it(in);it;it++) {
	mit.First();
	RealT minDist = distance.Measure(*mit,*it);
	index = 0;
	for(mit++;mit;mit++) {
	  RealT dist =  distance.Measure(*mit,*it);
	  if(dist < minDist) {
	    minDist = dist;
	    index = mit.Index().V();
	  }
	}
	cost += minDist;
	sums[index] += *it;
	counts[index]++;
      }
      
      // Update means.
      
      for(SArray1dIter3C<VectorC,UIntT,VectorC> uit(sums,counts,means);uit;uit++) {
	if(uit.Data2() > 0)
	  uit.Data3() = uit.Data1() / ((RealT) uit.Data2());
	else {
	  // Reinitalise from a random sample.
	  index = RandomInt() % in.Size();
	  uit.Data3() = (in[index]).Copy();
	}
	uit.Data1().Fill(0);
	uit.Data2() = 0;
      }
      iters++;
      ONDEBUG(cerr <<"Iteration complete. Cost=" << cost << " Oldcost=" << oldcost << "\n");
    } while(iters < 3 || ((oldcost - cost) > 1e-6) );
    
    return means;
  }
  
  //: Find weighted means for 'in'.
  
  SArray1dC<VectorC> DesignKMeansBodyC::FindMeans(const SampleC<VectorC> &in,const SampleC<RealT> &weights) {
    ONDEBUG(cerr << "DesignKMeansBodyC::Apply(), Called with " << in.Size() << " vectors. K=" << k << "\n");
    SArray1dC<VectorC> means(k);
    if(in.Size() == 0) {
      cerr << "DesignKMeansBodyC::Apply(), WARNING: No data samples given. \n";
      return SArray1dC<VectorC>();
    }
    if(in.Size() <= k) {
      cerr << "DesignKMeansBodyC::Apply(), WARNING: Fewer samples than means. \n";
      //return ClassifierNearestNeighbourC(in,distance);
      means = SArray1dC<VectorC>(in.Size());
      SampleIterC<VectorC> sit(in);
      for(SArray1dIterC<VectorC> it(means);it;it++,sit++)
	*it = *sit;
      return means;
    }
    
    // Pick some random points from the set to use as initial means.
    
    HSetC<UIntT> used;
    UIntT index,dim;
    dim = in.First().Size();
    
    for(SArray1dIterC<VectorC> it(means);it;it++) {
      do {
	index = RandomInt() % in.Size();
	if(used[index])
	  continue;
	*it = in[index].Copy();
	used += index;
      } while(0);
    }
    
    // Reassign according to distance.
    
    SArray1dC<VectorC> sums(k);
    SArray1dC<RealT> counts(k);
    for(SArray1dIter2C<VectorC,RealT> zit(sums,counts);zit;zit++) {
      zit.Data1() = VectorC(dim);
      zit.Data2() = 0;
    }
    RealT cost = 0,oldcost;
    IntT iters = 0;
    SArray1dIterC<VectorC> mit(means);

    // Update means iteratively.
    
    do {
      oldcost = cost;
      cost = 0;
      
      // Reclassify samples.
      
      for(DataSet2IterC<SampleC<VectorC>,SampleC<RealT> > it(in,weights);it;it++) {
	mit.First();
	RealT minDist = distance.Measure(*mit,it.Data1());
	index = 0;
	for(mit++;mit;mit++) {
	  RealT dist =  distance.Measure(*mit,it.Data1());
	  if(dist < minDist) {
	    minDist = dist;
	    index = mit.Index().V();
	  }
	}
	cost += minDist * it.Data2();
	sums[index].MulAdd(it.Data1(),it.Data2());
	counts[index] += it.Data2();
      }
      
      // Update means.
      
      for(SArray1dIter3C<VectorC,RealT,VectorC> uit(sums,counts,means);uit;uit++) {
	if(uit.Data2() > 0)
	  uit.Data3() = uit.Data1() / ((RealT) uit.Data2());
	else {
	  // Reinitalise from a random sample.
	  index = RandomInt() % in.Size();
	  uit.Data3() = (in[index]).Copy();
	}
	uit.Data1().Fill(0);
	uit.Data2() = 0;
      }
      iters++;
      ONDEBUG(cerr <<"Iteration complete. Cost=" << cost << " Oldcost=" << oldcost << "\n");
    } while(iters < 3 || ((oldcost - cost) > 1e-6) );
    
    return means;    
  }


  
  RAVL_INITVIRTUALCONSTRUCTOR_FULL(DesignKMeansBodyC,DesignKMeansC,DesignClusterC);

  
}
