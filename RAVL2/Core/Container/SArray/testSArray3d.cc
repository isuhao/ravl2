// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlCore
//! file="Ravl/Core/Container/SArray/testSArray3d.cc"
//! docentry="Ravl.API.Core.Arrays.3D"
//! userlevel=Develop

#include "Ravl/SArray3d.hh"
#include "Ravl/Slice1d.hh"
#include "Ravl/SArray3dIter.hh"
#include "Ravl/SArray3dIter2.hh"
#include "Ravl/SArray3dIter3.hh"
#include "Ravl/Stream.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/BinStream.hh"

using namespace RavlN;

int testBasic();
int testIO();

int main() {
  int ln ;
  if((ln = testBasic()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  if((ln = testIO()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  cerr << "Test passed ok. \n";
  return 0;
}

int testBasic() {
  cerr << "Starting test of SArray3d.\n";
  SArray3dC<int> testArr(10,10,10);
  SArray3dC<Index3dC> testArrI(10,10,10);

  testArr[Index3dC(1,1,1)] = 2;
  
  int place = 0;
  for(IndexC i = 0;i < 10;i++) {
    for(IndexC j = 0;j < 10;j++) {
      for(IndexC k = 0;k < 10;k++) {
        testArrI[i][j][k] = Index3dC(i,j,k);
	testArr[i][j][k] = place++;
      }
    }
  }
  
  int v = 0;
#if 0
  Slice1dC<int> slice = testArr.Diagonal();
  for(Slice1dIterC<int> its(slice);its;its++,v+=11) {
    if(*its != v) {
      cerr << "Diagonal slice test failed. " << *its << " " << v << "\n";
      return 1;
    }
  }
#endif
  for(SArray3dIterC<Index3dC> it(testArrI);it;it++) {
    if(it.Index() != *it) return __LINE__;
  }
  v = 0;
  for(SArray3dIterC<int> it(testArr);it;it++,v++) {
    if(*it != v) {
      cerr << "Iterator test failed. " << *it << " " << v << "\n";
      return 1;
    }
    *it = 0;
  }
  testArr /= 2;
  testArr += 1;
  testArr = testArr + testArr;
  
  place = 0;
  for(SArray3dIter2C<Index3dC,int> it(testArrI,testArr);it;it++) {
    it.Data2() = place++;
    if(it.Index() != it.Data1())
      return __LINE__;
  }
  place = 0;
  SArray3dC<short> testArrS(10,10,10);
  for(SArray3dIter3C<Index3dC,int,short> it(testArrI,testArr,testArrS);it;it++) {
    if(it.Data2() != place++)
      return __LINE__;
    if(it.Index() != it.Data1())
      return __LINE__;
  }
  return 0; 
}

int testIO() {
  cerr << "Starting IO test of SArray3d.\n";
  SArray3dC<RealT> m(2,3,4);
  
  for(int i = 0;i < 2;i++)
    for(int j = 0;j < 3;j++)
      for(int k = 0;k < 4;k++)
	m[i][j][k] = i + j + k;
  
  // Check binary io.
  {
    StrOStreamC os;
    {
      BinOStreamC bin(os);
      bin << m;
    }
    SArray3dC<RealT> m2;
    {
      StrIStreamC ifs(os.String());
      BinIStreamC bin(ifs);
      bin >> m2; 
    }
    if((m - m2).SumOfSqr() > 0.000001)
      return __LINE__;
  }
  
  // Check text io.
  {
    StrOStreamC os;
    {
      os << m;
    }
    SArray3dC<RealT> m2;
    {
      StrIStreamC ifs(os.String());
      ifs >> m2; 
    }
    if((m - m2).SumOfSqr() > 0.000001)
      return __LINE__;
  }
  return 0;
}

template class SArray3dC<UIntT>;
template class SArray3dIterC<UIntT>;
template class SArray3dIter2C<UIntT,RealT>;
template class SArray3dIter3C<UIntT,RealT,ByteT>;
