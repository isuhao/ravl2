// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_SEGMENTATION_HEADER
#define RAVLIMAGE_SEGMENTATION_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Images.Segmentation"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Segmentation/Segmentation.hh"

#include "Ravl/Array2dSqr2Iter2.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/RefCounter.hh"
#include "Ravl/HSet.hh"
#include "Ravl/IntC.hh"
#include "Ravl/Tuple2.hh"
#include "Ravl/Moments2d2.hh"

namespace RavlImageN {
  
  //! userlevel=Develop
  //: Segmentation map.
  
  class SegmentationBodyC 
    : public RCBodyVC
  {
  public:
    SegmentationBodyC(ImageC<UIntT> nsegmap,UIntT nlabels)
      : segmap(nsegmap),
	labels(nlabels)
    {}
    //: Constructor.
    
    SArray1dC<HSetC<UIntT> > Adjacency(bool biDir = false);
    //: Generate a table of region adjacencies.
    // For each region, a set of adjacent regions is 
    // generated.   If biDir is false, only adjacenies from
    // regions with a smaller id to those with a larger ID are
    // generated, otherwise both direction are registered.
    
    SArray1dC<HashC<UIntT,UIntC> > BoundryLength();
    //: Generate a table of region adjacencies boundry lengths.
    // only adjacenies from regions with a smaller id to those 
    // with a larger ID are generated
    
    UIntT RemoveSmallComponents(IntT thrSize);
    //: Remove small components from map, label them as 0.
    
    UIntT CompressAndRelabel(SArray1dC<UIntT> newLabs);
    //: Compress newlabs and re-label segmentation.
    // this correctly resolves multilevel mappings.
    // Note: newLabs will be changed to contain a mapping
    // from the original labels to there new values.
    
    SArray1dC<UIntT> Areas();
    //: Compute the areas of all the segmented regions.
    
    SArray1dC<UIntT> RedoArea(SArray1dC<UIntT> area,SArray1dC<UIntT> map);
    //: recompute the areas from the original areas and a mapping.
    
    SArray1dC<UIntT> IdentityLabel();  
    //: Make an array of labels mapping to themselves.
    // This is useful for making merge tables which can
    // the be passed to CompressAndRelabel.
    
    template<class PixelT,class CmpT>
    UIntT MergeComponents(ImageC<PixelT> &dat,UIntT thrSize,RealT maxDist,CmpT &cmp,IntT iter = 1);
    //: Merge simlar components smaller than 'thrSize'.
    // This just looks for the difference between adjacent pixels from different regions.
    // FIXME :- It maybe better to look at the average difference.
    
    ImageC<UIntT> &SegMap()
    { return segmap; }
    //: Access segmentation map.
    
    UIntT Labels()
    { return labels; }
    //: Access number of labels.
    
    SArray1dC<Moments2d2C> ComputeMoments(bool ignoreZero = false);
    //: Compute moments for each of the segmented regions.
    // if ignoreZero is true, region labeled 0 is ignored.
    
  protected:
    UIntT RelabelTable(SArray1dC<UIntT> &labelTable, UIntT currentMaxLabel);
    //: Compress labels.
    
    ImageC<UIntT> segmap; // Segmentation map.
    UIntT labels;         // Number of labels in map.
  };
  
  //! userlevel=Normal
  //: Segmentation map.
  
  class SegmentationC 
    : public RCHandleC<SegmentationBodyC>
  {
  public:
    SegmentationC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    SegmentationC(ImageC<UIntT> nsegmap,UIntT nlabels)
      : RCHandleC<SegmentationBodyC>(*new SegmentationBodyC(nsegmap,nlabels))
    {}
    //: Constructor.
    
    SegmentationC(const Tuple2C<ImageC<UIntT>,UIntT> &tup)
      : RCHandleC<SegmentationBodyC>(*new SegmentationBodyC(tup.Data1(),tup.Data2()))
    {}
    //: Constructor.

    
  protected:
    SegmentationBodyC &Body()
    { return RCHandleC<SegmentationBodyC>::Body(); }
    //: Access body.
    
    const SegmentationBodyC &Body() const
    { return RCHandleC<SegmentationBodyC>::Body(); }
    //: Access body.
    
  public:
    
    SArray1dC<HSetC<UIntT> > Adjacency(bool biDir = true)
    { return Body().Adjacency(biDir); }
    //: Generate a table of region adjacencies.
    // For each region, a set of adjacent regions is 
    // generated.   If biDir is false, only adjacenies in
    // one direction are generated, otherwise both directions
    // are registered.
    
    SArray1dC<HashC<UIntT,UIntC> > BoundryLength()
    { return Body().BoundryLength(); }
    //: Generate a table of region adjacencies boundry lengths.
    // only adjacenies from regions with a smaller id to those 
    // with a larger ID are generated
    
    UIntT RemoveSmallComponents(IntT thrSize)
    { return Body().RemoveSmallComponents(thrSize); }
    //: Remove small components from map, label them as 0.
    
    SArray1dC<UIntT> Areas()
    { return Body().Areas(); }
    //: Compute the areas of all the segmented regions.
    
    template<class PixelT,class CmpT>
    UIntT MergeComponents(ImageC<PixelT> &dat,UIntT thrSize,RealT maxDist,CmpT &cmp,IntT iter = 1)
    { return Body().MergeComponents(dat,thrSize,maxDist,cmp,iter); }
    //: Merge simlar components smaller than 'thrSize'.
    
    ImageC<UIntT> &SegMap()
    { return Body().SegMap(); }
    //: Access segmentation map.
    
    UIntT Labels()
    { return Body().Labels(); }
    //: Access number of labels.  
    
    SArray1dC<Moments2d2C> ComputeMoments(bool ignoreZero = false)
    { return Body().ComputeMoments(ignoreZero); }
    //: Compute moments for each of the segmented regions.
    // if ignoreZero is true, region labeled 0 is ignored.
    
  };

  //: Merge simlar components smaller than 'thrSize'.
  
  template<class PixelT,class CmpT>
  UIntT SegmentationBodyC::MergeComponents(ImageC<PixelT> &dat,
					   UIntT thrSize,
					   RealT maxDist,
					   CmpT &cmp,
					   IntT iter) 
  {
    if(labels <= 1)
      return labels;
    SArray1dC<RealT> minDist(labels);  
    SArray1dC<UIntT> area = Areas();
    
    for(;iter > 0;iter--) {
      minDist.Fill(maxDist); // Fill with maximum merge threshold./
      SArray1dC<UIntT> minLab =  IdentityLabel();
      
      // Find closest neigbour of small regions.
      
      for(Array2dSqr2Iter2C<UIntT,PixelT> it(segmap,dat);it;) {
	// Do up.
	if(it.DataBR1() != it.DataTR1()) { // Are labels different ?
	  if(area[it.DataBR1()] < thrSize) {
	    RealT d = cmp(it.DataBR2(),it.DataTR2());
	    if(minDist[it.DataBR1()] > d) {
	      minDist[it.DataBR1()] = d;
	      minLab[it.DataBR1()] = it.DataTR1();
	    }
	  }
	  if(area[it.DataTR1()] < thrSize) {
	    RealT d = cmp(it.DataBR2(),it.DataTR2());
	    if(minDist[it.DataTR1()] > d) {
	      minDist[it.DataTR1()] = d;
	      minLab[it.DataTR1()] = it.DataBR1();
	    }
	  }
	}
	
	for(;it.Next();) { // The rest of the image row.
	  // Do up.
	  if(it.DataBR1() != it.DataTR1()) {  // Are labels different ?
	    if(area[it.DataBR1()] < thrSize) {
	      if(it.DataBR1() != it.DataTR1()) {
		RealT d = cmp(it.DataBR2(),it.DataTR2());
		if(minDist[it.DataBR1()] > d) {
		  minDist[it.DataBR1()] = d;
		  minLab[it.DataBR1()] = it.DataTR1();
		}
	    }
	    }
	    if(area[it.DataTR1()] < thrSize) { 
	      RealT d = cmp(it.DataBR2(),it.DataTR2());
	      if(minDist[it.DataTR1()] > d) {
		minDist[it.DataTR1()] = d;
		minLab[it.DataTR1()] = it.DataBR1();
	      }
	    }
	  }
	  
	  // Do back.
	  if(it.DataBR1() != it.DataBL1()) { // Are labels different ?
	    if(area[it.DataBR1()] < thrSize) { 
	      RealT d = cmp(it.DataBR2(),it.DataBL2());
	      if(minDist[it.DataBR1()] > d) {
		minDist[it.DataBR1()] = d;
		minLab[it.DataBR1()] = it.DataBL1();
	      }
	    }
	    if(area[it.DataBL1()] < thrSize) {
	      RealT d = cmp(it.DataBR2(),it.DataBL2());
	      if(minDist[it.DataBL1()] > d) {
		minDist[it.DataBL1()] = d;
		minLab[it.DataBL1()] = it.DataBR1();
	      }
	    }
	  }
	}
      }
      CompressAndRelabel(minLab);
      if(iter > 1)
	area = RedoArea(area,minLab);
    }
    return labels;
  }
}
#endif
