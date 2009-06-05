// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_ARRAY2DSQR3311ITER4_HEADER
#define RAVL_ARRAY2DSQR3311ITER4_HEADER 1
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.API.Core.Arrays.2D"
//! author="Charles Galambos"
//! lib=RavlCore
//! file="Ravl/Core/Container/Array/Array2dSqr3311Iter4.hh"

#include "Ravl/Array2d.hh"
#include "Ravl/BufferAccess2dIter4.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Iterate through an array accessing 3x3 area in two arrays, and 1 pixel area in two other arrays.
  // The square can be accessed with DataBL,DataBR etc...
  // which access the following array elements. <p>
  //  TL TM TR <br>
  //  ML MM MR <br>
  //  BL BM BR <br>
  // for the first array.
  
  template<class Data1T,class Data2T,class Data3T,class Data4T>
  class Array2dSqr3311Iter4C 
    : protected BufferAccess2dIter4C<Data1T,Data2T,Data3T,Data4T>
  {
  public:
    Array2dSqr3311Iter4C()
    {}
    //: Default constructor.
    
    Array2dSqr3311Iter4C(const Array2dC<Data1T> &narray1,
			 const Array2dC<Data2T> &narray2,
			 const Array2dC<Data3T> &narray3,
			 const Array2dC<Data4T> &narray4
			 ) 
      : array1(narray1),
	array2(narray2),
	array3(narray3),
	array4(narray4)
    { First(); }
    //: Constructor.
    
    bool First() {
      IndexRange2dC frame1 = array1.Frame().Expand(-1);
      IndexRange2dC frame2 = array2.Frame().Expand(-1);
      RavlAssert(frame1 == frame2 );
      if(!BufferAccess2dIter4C<Data1T,Data2T,Data3T,Data4T>::First(array1.BufferAccess(),array1.ByteStride(),frame1,
                                                            array2.BufferAccess(),array2.ByteStride(),frame2,
                                                            array3.BufferAccess(),array3.ByteStride(),frame1,
                                                            array4.BufferAccess(),array4.ByteStride(),frame1
                                                            ))
        return false;
      up1 = ShiftPointerInBytes(&(this->Data1()),-array1.ByteStride());
      dn1 = ShiftPointerInBytes(&(this->Data1()),array1.ByteStride());
      up2 = ShiftPointerInBytes(&(this->Data2()),-array2.ByteStride());
      dn2 = ShiftPointerInBytes(&(this->Data2()),array2.ByteStride());
      return true;
    }
    //: Goto first element in the array.
    
    bool NextRow() {
      if(!BufferAccess2dIter4C<Data1T,Data2T,Data3T,Data4T>::NextRow())
        return false;
      up1 = ShiftPointerInBytes(&(this->Data1()),-array1.ByteStride());
      dn1 = ShiftPointerInBytes(&(this->Data1()),array1.ByteStride());
      up2 = ShiftPointerInBytes(&(this->Data2()),-array2.ByteStride());
      dn2 = ShiftPointerInBytes(&(this->Data2()),array2.ByteStride());
      return true;
    }
    //: Goto next row.
    // Returns true if left on a valid row.

    bool Next() {
      if(!BufferAccess2dIter4C<Data1T,Data2T,Data3T,Data4T>::Next()) {
        up1 = ShiftPointerInBytes(&(this->Data1()),-array1.ByteStride());
        dn1 = ShiftPointerInBytes(&(this->Data1()),array1.ByteStride());
        up2 = ShiftPointerInBytes(&(this->Data2()),-array2.ByteStride());
        dn2 = ShiftPointerInBytes(&(this->Data2()),array2.ByteStride());
        return false;
      }
      up1++;
      dn1++;
      up2++;
      dn2++;
      return true;
    }
    //: Goto next element.
    
    bool IsElm() const
    { return this->m_cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    operator bool() const
    { return this->m_cit.IsElm(); }
    //: Test if iterator is at a valid element.
    
    void operator++() 
    { Next(); }
    //: Goto next element.

    void operator++(int) 
    { Next(); }
    //: Goto next element.
    
    Data1T &DataBL1() 
    { return dn1[-1]; }
    //: Access bottom left data element from array 1

    const Data1T &DataBL1() const
    { return dn1[-1]; }
    //: Access bottom left data element from array 1 

    Data1T &DataBM1() 
    { return *dn1; }
    //: Access bottom mid data element from array 1

    const Data1T &DataBM1() const
    { return *dn1; }
    //: Access bottom mid data element from array 1

    Data1T &DataBR1() 
    { return dn1[1]; }
    //: Access bottom right data element from array 1

    const Data1T &DataBR1() const
    { return dn1[1]; }
    //: Access bottom right data element from array 1

    Data1T &DataML1() 
    { return (&(this->m_cit.Data1()))[-1]; }
    //: Access middle left data element from array 1
    
    const Data1T &DataML1() const
    { return (&(this->m_cit.Data1()))[-1]; }
    //: Access middle left data element from array 1
    
    Data1T &DataMM1() 
    { return this->m_cit.Data1(); }
    //: Access middle data element from array 1
    
    const Data1T &DataMM1() const
    { return this->m_cit.Data1(); }
    //: Access middle data element from array 1
    
    Data1T &Data1() 
    { return this->m_cit.Data1(); }
    //: Access middle data element from array 1
    
    const Data1T &Data1() const
    { return this->m_cit.Data1(); }
    //: Access middle data element from array 1
    
    Data1T &DataMR1() 
    { return (&(this->m_cit.Data1()))[1]; }
    //: Access middle right data element from array 1
    
    const Data1T &DataMR1() const
    { return (&(this->m_cit.Data1()))[1]; }
    //: Access middle right data element from array 1

    Data1T &DataTL1() 
    { return up1[-1]; }
    //: Access top left data element from array 1
    
    const Data1T &DataTL1() const
    { return up1[-1]; }
    //: Access top left data element from array 1

    Data1T &DataTM1() 
    { return *up1; }
    //: Access top middle element from array 1
    
    const Data1T &DataTM1() const
    { return *up1; }
    //: Access top middle element from array 1
    
    Data1T &DataTR1() 
    { return up1[1]; }
    //: Access top right data element from array 1
    
    const Data1T &DataTR1() const
    { return up1[1]; }
    //: Access top right data element from array 1
    
    Data2T &DataBL2() 
    { return dn2[-1]; }
    //: Access bottom left data element from array 2 

    const Data2T &DataBL2() const
    { return dn2[-1]; }
    //: Access bottom left data element from array 2

    Data2T &DataBM2() 
    { return *dn2; }
    //: Access bottom mid data element from array 2

    const Data2T &DataBM2() const
    { return *dn2; }
    //: Access bottom mid data element from array 2

    Data2T &DataBR2() 
    { return dn2[1]; }
    //: Access bottom right data element from array 2

    const Data2T &DataBR2() const
    { return dn2[1]; }
    //: Access bottom right data element from array 2

    Data2T &DataML2() 
    { return (&(this->m_cit.Data2()))[-1]; }
    //: Access middle left data element from array 2
    
    const Data2T &DataML2() const
    { return (&(this->m_cit.Data2()))[-1]; }
    //: Access middle left data element from array 2
    
    Data2T &DataMM2() 
    { return this->m_cit.Data2(); }
    //: Access middle data element from array 2
    
    const Data2T &DataMM2() const
    { return this->m_cit.Data2(); }
    //: Access middle data element from array 2
    
    Data2T &Data2() 
    { return this->m_cit.Data2(); }
    //: Access middle data element from array 2
    
    const Data2T &Data2() const
    { return this->m_cit.Data2(); }
    //: Access middle data element from array 2
    
    Data2T &DataMR2() 
    { return (&(this->m_cit.Data2()))[1]; }
    //: Access middle right data element from array 2
    
    const Data2T &DataMR2() const
    { return (&(this->m_cit.Data2()))[1]; }
    //: Access middle right data element from array 2

    Data2T &DataTL2() 
    { return up2[-1]; }
    //: Access top left data element from array 2
    
    const Data2T &DataTL2() const
    { return up2[-1]; }
    //: Access top left data element from array 2

    Data2T &DataTM2() 
    { return *up2; }
    //: Access top middle element from array 2
    
    const Data2T &DataTM2() const
    { return *up2; }
    //: Access top middle element from array 2
    
    Data2T &DataTR2() 
    { return up2[1]; }
    //: Access top right data element from array 2
    
    const Data2T &DataTR2() const
    { return up2[1]; }
    //: Access top right data element from array 2
    
    Data3T &Data3() 
    { return this->m_cit.Data3(); }
    //: Access middle data element of 3rd array.
    
    const Data3T &Data3() const
    { return this->m_cit.Data3(); }
    //: Access middle data element of 3rd array.

    Data4T &Data4() 
    { return this->m_cit.Data4(); }
    //: Access middle data element of 4th array.
    
    const Data4T &Data4() const
    { return this->m_cit.Data4(); }
    //: Access middle data element of 4th array.

    Index2dC Index() const
    { return array1.IndexOf(this->DataMM1()); }
    //: Get index of current location of the middle pixel in the first array.
    // Has to be calculate, and so is slightly slow.

  protected:
    Array2dC<Data1T> array1;
    Array2dC<Data2T> array2;
    Array2dC<Data3T> array3;
    Array2dC<Data4T> array4;
    Data1T *up1;
    Data1T *dn1;
    Data2T *up2;
    Data2T *dn2;
  };
}



#endif
