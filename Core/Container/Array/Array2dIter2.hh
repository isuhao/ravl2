// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY2DITER2_HEADER
#define RAVL_ARRAY2DITER2_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Arrays.2D"
//! file="Ravl/Core/Container/Array/Array2dIter2.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="24/08/1999"
//! userlevel=Default

#include "Ravl/Array2d.hh"
#include "Ravl/BfAcc2Iter2.hh"

namespace RavlN {
  
  //! userlevel=Normal
  //: dual Array2dC iterator.
  // This will iterate through two rectangles of the same size.  The rectangles need not
  // have the same origin.  
  
  template<class Data1T,class Data2T>
  class Array2dIter2C 
    : public BufferAccess2dIter2C<Data1T,Data2T>
  {
  public:
    Array2dIter2C()
    {}
    //: Default constructor.
    
    Array2dIter2C(const Array2dC<Data1T> &arr1,const Array2dC<Data2T> &arr2,bool matching = true)
      : BufferAccess2dIter2C<Data1T,Data2T>(arr1,arr1.Range2(),
					    arr2,arr2.Range2()),
        dat1(arr1),
        dat2(arr2)
    { 
      if(matching) 
	RavlAssert(dat1.Range().Size() == dat2.Range().Size());
      First();
    }
    //: Constructor.
    // If 'matching' is true, the rectangles must be of the same size. <br>
    // If 'matching' is set to false the size of the rectangle is set to that of the first array, 'arr1'
    // arr1 MUST have a size equal to or smaller than arr2 in both dimensions.
    
    Array2dIter2C(const Array2dC<Data1T> &arr1,const Array2dC<Data2T> &arr2,const IndexRange2dC &rect)
      : dat1(arr1,rect),
        dat2(arr2,rect)
    { BufferAccess2dIter2C<Data1T,Data2T>::First(dat1,dat1.Range2(),
						 dat2,dat2.Range2()); 
    }
    //: Constructor.
    // Iterate through 'rect' in both arrays. 'rect' must be within both arr1 and arr2.

    Array2dIter2C(const Array2dC<Data1T> &arr1,const IndexRange2dC &irng1,
		  const Array2dC<Data2T> &arr2,const IndexRange2dC &irng2)
      : dat1(arr1,irng1),
        dat2(arr2,irng2)
    { BufferAccess2dIter2C<Data1T,Data2T>::First(dat1,dat1.Range2(),
						 dat2,dat2.Range2()); 
    }
    //: Constructor.
    // Iterate through 'rect' in both arrays. irng1 should have the same or smaller
    // overall size than irng2.
    
    inline bool First() {
      return BufferAccess2dIter2C<Data1T,Data2T>::First(dat1,dat1.Range2(),
							dat2,dat2.Range2()); 
    }
    //: Goto first element in the array.
    // Return TRUE if there actually is one.

    Index2dC Index() const { 
      RavlAssert(dat1.IsValid());
      return Index2dC((IntT) (&(rit.Data1()) - dat1.ReferenceElm()),
		      (IntT) (&(cit.Data1()) - rit.Data1().ReferenceElm()));
    }
    //: Get index of current location.
    // Has to be calculate, and so is slightly slow.
        
  protected:
    Array2dC<Data1T> dat1;
    Array2dC<Data2T> dat2;
  };
}

#endif
