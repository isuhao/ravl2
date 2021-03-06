// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_SARR2ITER3_HEADER
#define RAVL_SARR2ITER3_HEADER 1
////////////////////////////////////////////////////////////
//! docentry="Ravl.API.Core.Arrays.3D"
//! rcsid="$Id$
//! file="Ravl/Core/Container/SArray/SArray3dIter3.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="10/09/1998"
//! userlevel=Advanced

#include "Ravl/SArray3d.hh"
#include "Ravl/SArray3d.hh"

namespace RavlN {
  //! userlevel=Advanced
  //: Triple SArray3dC iterator.
  // Triple Simple 3d array iterator.
  
  template<class Data1T,class Data2T,class Data3T>
  class SArray3dIter3C 
    : public BufferAccess3dIter3C<Data1T,Data2T,Data3T>
  {
  public:
    SArray3dIter3C()
    {}
    //: Default constructor.
    
    SArray3dIter3C(const SArray3dC<Data1T> &arr,
		   const SArray3dC<Data2T> &narr2,
		   const SArray3dC<Data3T> &narr3)
      : arr1(arr),
	arr2(narr2),
	arr3(narr3)
    { First(); }
    //: Constructor.
    
    inline bool First() {
      return BufferAccess3dIter3C<Data1T,Data2T,Data3T>::First(arr1.BufferAccess(),arr1.ByteStride1(),arr1.ByteStride2(),
                                                               arr2.BufferAccess(),arr2.ByteStride1(),arr2.ByteStride2(),
                                                               arr3.BufferAccess(),arr3.ByteStride1(),arr3.ByteStride2(),
                                                               arr1.Size1(),arr1.Size2(),arr1.Size3());
    }
    //: Goto first element in array.
    // returns true if there is a first element.

    Index3dC Index() const
    { return arr1.IndexOf(this->Data1()); }
    //: Get index of current location in array 1.
    // Has to be calculate, and so is slightly slow.
    
  protected:    
    SArray3dC<Data1T> arr1;
    SArray3dC<Data2T> arr2;
    SArray3dC<Data3T> arr3;
  };
  
  ////////////////////////////////////////////////////////////////  
  
}

#endif
