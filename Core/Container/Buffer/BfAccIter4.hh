// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSBFACCITER4_HEADER
#define RAVLSBFACCITER4_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Buffer/BfAccIter3.hh"
//! author="Charles Galambos"
//! lib=RavlCore
//! docentry="Ravl.Core.Arrays.Buffer"
//! date="24/01/2001"

#include "Ravl/RBfAcc.hh"
#include "Ravl/SBfAcc.hh"

namespace RavlN {

  //! userlevel=Advanced
  //: Iterator for 3 buffers.
  
  template<class Data1T,class Data2T,class Data3T,class Data4T>
  class BufferAccessIter4C {
  public:
    inline BufferAccessIter4C();
    //: Default constructor.
    
    inline BufferAccessIter4C(const BufferAccessC<Data1T> &buff,
			      const BufferAccessC<Data2T> &buff2,
			      const BufferAccessC<Data3T> &buff3,
			      const BufferAccessC<Data4T> &buff4,
 			      SizeT size)
      { First(buff,buff2,buff3,size); }
    //: Constructor.

    inline BufferAccessIter4C(const BufferAccessC<Data1T> &buff1,const IndexRangeC &rng1,
			      const BufferAccessC<Data2T> &buff2,const IndexRangeC &rng2,
			      const BufferAccessC<Data3T> &buff3,const IndexRangeC &rng3,
			      const BufferAccessC<Data4T> &buff4,const IndexRangeC &rng4
			      )
      { First(buff1,rng1,
	      buff2,rng2,
	      buff3,rng3); 
      }
    //: Constructor.
    
    inline BufferAccessIter4C(const RangeBufferAccessC<Data1T> &buff,
			      const RangeBufferAccessC<Data2T> &buff2,
			      const RangeBufferAccessC<Data3T> &buff3,
			      const RangeBufferAccessC<Data4T> &buff4
			      )
      { First(buff,buff2,buff3); }
    //: Constructor.

    inline BufferAccessIter4C(const SizeBufferAccessC<Data1T> &buff,
			      const SizeBufferAccessC<Data2T> &buff2,
			      const SizeBufferAccessC<Data3T> &buff3,
			      const SizeBufferAccessC<Data4T> &buff4
			      )
      { First(buff,buff2,buff3); }
    //: Constructor.
    
    inline bool First(const BufferAccessC<Data1T> &buff1,const IndexRangeC &rng1,
		      const BufferAccessC<Data2T> &buff2,const IndexRangeC &rng2,
		      const BufferAccessC<Data3T> &buff3,const IndexRangeC &rng3,
		      const BufferAccessC<Data4T> &buff4,const IndexRangeC &rng4
		      );
    //: Goto first element.
    // returns true if there is a first element.
    
    inline bool First(const BufferAccessC<Data1T> &buff,
		      const BufferAccessC<Data2T> &buff2,
		      const BufferAccessC<Data3T> &buff3,
		      const BufferAccessC<Data4T> &buff4,
		      SizeT size);
    //: Goto first element.
    // returns true if there is a first element.
    
    inline bool First(const RangeBufferAccessC<Data1T> &buff,
		      const RangeBufferAccessC<Data2T> &buff2,
		      const RangeBufferAccessC<Data3T> &buff3,
		      const RangeBufferAccessC<Data4T> &buff4
		      );
    //: Goto first element.
    // returns true if there is a first element.

    inline bool First(const SizeBufferAccessC<Data1T> &buff,
		      const SizeBufferAccessC<Data2T> &buff2,
		      const SizeBufferAccessC<Data3T> &buff3,
		      const SizeBufferAccessC<Data4T> &buff4
		      );
    //: Goto first element.
    // returns true if there is a first element.
    
    inline bool IsElm() const
      { return at1 != endOfRow; }
    //: At valid element ?

    inline operator bool() const
      { return at1 != endOfRow; }
    //: At valid element ?
    
    inline void Next();
    //: Goto next element.
    // Call ONLY if IsElm() is valid.

    inline void operator++()
      { Next(); }
    //: Goto next elment.

    inline void operator++(int)
      { Next(); }
    //: Goto next elment.
    
    inline Data1T &Data1()
      { return *at1; }
    //: Access data.
    
    inline const Data1T &Data1() const
      { return *at1; }
    //: Access data.
    
    inline Data2T &Data2()
      { return *at2; }
    //: Access data.
    
    inline const Data2T &Data2() const
      { return *at2; }
    //: Access data.
    
    inline Data3T &Data3()
      { return *at3; }
    //: Access data.
    
    inline const Data3T &Data3() const
      { return *at3; }
    //: Access data.

    inline Data4T &Data4()
      { return *at4; }
    //: Access data.
    
    inline const Data4T &Data4() const
      { return *at4; }
    //: Access data.
    
    inline void Invalidate();
    //: Make IsElm() return false.
    
  private:
    Data1T *at1;
    Data2T *at2;
    Data3T *at3;
    Data4T *at4;
    const Data1T *endOfRow;
  };
  
  //////////////////////////////////////////////////////
  
  template<class Data1T,class Data2T,class Data3T,class Data4T>
  inline 
  BufferAccessIter4C<Data1T,Data2T,Data3T,Data4T>::BufferAccessIter4C()
    : at1(0), 
      endOfRow(0)
  {}

  template<class Data1T,class Data2T,class Data3T,class Data4T>
  inline 
  bool BufferAccessIter4C<Data1T,Data2T,Data3T,Data4T>::First(const BufferAccessC<Data1T> &buff,
							      const BufferAccessC<Data2T> &buff2,
							      const BufferAccessC<Data3T> &buff3,
							      const BufferAccessC<Data4T> &buff4,
							      SizeT size)
  {
    if(size <= 0) {
      at1 = 0;
      endOfRow = 0;
      return false;
    }
    at1 = const_cast<Data1T *>(buff.ReferenceElm());
    at2 = const_cast<Data2T *>(buff2.ReferenceElm());
    at3 = const_cast<Data3T *>(buff3.ReferenceElm());
    at4 = const_cast<Data4T *>(buff4.ReferenceElm());
    endOfRow = &(at1[size]);
    return true;
  }

  template<class Data1T,class Data2T,class Data3T,class Data4T>
  inline 
  bool BufferAccessIter4C<Data1T,Data2T,Data3T,Data4T>::First(const BufferAccessC<Data1T> &buff1,const IndexRangeC &rng1,
							      const BufferAccessC<Data2T> &buff2,const IndexRangeC &rng2,
							      const BufferAccessC<Data3T> &buff3,const IndexRangeC &rng3,
							      const BufferAccessC<Data4T> &buff4,const IndexRangeC &rng4
							      )
  {
    if(rng1.Size() <= 0) {
      at1 = 0;
      endOfRow = 0;
      return false;
    }
    RavlAssert(rng1.Size() <= rng2.Size()); 
    RavlAssert(rng1.Size() <= rng3.Size()); 
    RavlAssert(rng1.Size() <= rng4.Size()); 
    at1 = const_cast<Data1T *>(&buff1[rng1.Min()]);
    at2 = const_cast<Data2T *>(&buff2[rng2.Min()]);
    at3 = const_cast<Data3T *>(&buff3[rng3.Min()]);
    at4 = const_cast<Data4T *>(&buff4[rng4.Min()]);
    endOfRow = &(at1[rng1.Size()]);
    return true;
  }
  
  template<class Data1T,class Data2T,class Data3T,class Data4T>
  inline 
  bool BufferAccessIter4C<Data1T,Data2T,Data3T,Data4T>::First(const RangeBufferAccessC<Data1T> &buff,
							      const RangeBufferAccessC<Data2T> &buff2,
							      const RangeBufferAccessC<Data3T> &buff3,
							      const RangeBufferAccessC<Data4T> &buff4
							      )
  {
    RavlAssert(buff.Size() <= buff2.Size()); 
    RavlAssert(buff.Size() <= buff3.Size()); 
    RavlAssert(buff.Size() <= buff4.Size()); 
    if(buff.Size() <= 0) {
      at1 = 0;
      endOfRow = 0;
      return false ;
    }
    at1 = const_cast<Data1T *>(&buff[buff.IMin()]);
    at2 = const_cast<Data2T *>(&buff2[buff2.IMin()]);
    at3 = const_cast<Data3T *>(&buff3[buff3.IMin()]);
    at4 = const_cast<Data4T *>(&buff4[buff4.IMin()]);
    endOfRow = &(at1[buff.Size()]);
    return true;
  }

  template<class Data1T,class Data2T,class Data3T,class Data4T>
  inline 
  bool BufferAccessIter4C<Data1T,Data2T,Data3T,Data4T>::First(const SizeBufferAccessC<Data1T> &buff,
							      const SizeBufferAccessC<Data2T> &buff2,
							      const SizeBufferAccessC<Data3T> &buff3,
							      const SizeBufferAccessC<Data4T> &buff4
							      )
  {
    RavlAssert(buff.Size() <= buff2.Size()); 
    RavlAssert(buff.Size() <= buff3.Size()); 
    RavlAssert(buff.Size() <= buff4.Size()); 
    if(buff.Size() <= 0) {
      at1 = 0;
      endOfRow = 0;
      return false;
    }
    at1 = const_cast<Data1T *>(buff.ReferenceElm());
    at2 = const_cast<Data2T *>(buff2.ReferenceElm());
    at3 = const_cast<Data3T *>(buff3.ReferenceElm());
    at4 = const_cast<Data4T *>(buff4.ReferenceElm());
    endOfRow = &(at1[buff.Size()]);
    return true;
  }
  
  template<class Data1T,class Data2T,class Data3T,class Data4T>
  inline 
  void 
  BufferAccessIter4C<Data1T,Data2T,Data3T,Data4T>::Next() {
    RavlAssert(at1 != endOfRow);
    at1++;
    at2++;
    at3++;
    at4++;
  }
  
  template<class Data1T,class Data2T,class Data3T,class Data4T>
  inline 
  void 
  BufferAccessIter4C<Data1T,Data2T,Data3T,Data4T>::Invalidate() { 
    at1 = 0;
    endOfRow = 0; 
  }
  
}
#endif
