// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLFINDEX_HEADER
#define RAVLFINDEX_HEADER 1
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Indexing"
//! file="Ravl/Core/Base/FIndex.hh"
//! lib=RavlCore
//! userlevel=Default
//! author="Charles Galambos"
//! date="24/01/2001"

#include "Ravl/TFVector.hh"
#include "Ravl/Index.hh"

namespace RavlN {
  
  //! userlevel=Advanced
  //: Fixed sized Index
  
  template<unsigned int N>
  class FIndexC 
    : public TFVectorC<IndexC,N>
  {
  public:
    FIndexC()
      {}
    //: Default constructor.

    FIndexC(const TFVectorC<IndexC,N> &oth)
      : TFVectorC<IndexC,N>(oth)
      {}
    //: Base class constructor.
    
    FIndexC(SizeT dim)
      { RavlAssert(dim == N); }
    //: Constructor with requested size.
    
    inline UIntT Hash(void) const;
    // Generates a randomised hash value for this index.
    
    // Arithmetic operations
    // ---------------------
    
    inline const FIndexC<N> & operator*=(IntT alpha);
    // Multiplies this index by number 'alpha'.

    inline const FIndexC<N> & operator*=(RealT alpha);
    // Multiplies this index by real number 'alpha'.

    inline const FIndexC<N> & operator/=(IntT alpha);
    // Divides this index by number 'alpha'.

    inline const FIndexC<N> & operator/=(RealT alpha);
    // Divides this index by real number 'alpha'.

    inline FIndexC<N> operator*(IntT alpha) const;
    // Multiplies this index by number 'alpha'.

    inline FIndexC<N> operator*(RealT alpha) const;
    // Multiplies this index by real number 'alpha'.

    inline FIndexC<N> operator/(IntT alpha) const;
    // Divides this index by number 'alpha'.

    inline FIndexC<N> operator/(RealT alpha) const;
    // Divides this index by real number 'alpha'.
    
  };
  
  template<unsigned int N>
  inline 
  const FIndexC<N> &FIndexC<N>::operator*=(IntT alpha) {
    for(int i = 0;i < N;i++)
      data[i] *= alpha;
    return *this;
  }
  
  template<unsigned int N>
  inline 
  const FIndexC<N> & 
  FIndexC<N>::operator*=(RealT alpha) {
    for(int i = 0;i < N;i++)
      data[i] = IndexC(data[i] * alpha);
    return *this;
  }
  
  template<unsigned int N>
  inline 
  const FIndexC<N> &FIndexC<N>::operator/=(IntT alpha) {
    for(int i = 0;i < N;i++)
      data[i] /= alpha;
    return *this;
  }
  
  template<unsigned int N>
  inline 
  const FIndexC<N> &FIndexC<N>::operator/=(RealT alpha) {
    for(int i = 0;i < N;i++)
      data[i] = IndexC(data[i] / alpha);
    return *this;
  }

  template<unsigned int N>
  inline 
  FIndexC<N> FIndexC<N>::operator*(IntT alpha) const { 
    FIndexC<N> ret;
    for(int i = 0;i < N;i++)
      ret[i] = data[i] * alpha;
    return ret;
  }
  
  template<unsigned int N>
  inline 
  FIndexC<N> 
  FIndexC<N>::operator*(RealT alpha) const { 
    FIndexC<N> ret;
    for(int i = 0;i < N;i++)
      ret[i] = IndexC(data[i] * alpha);
    return ret;
  }

  template<unsigned int N>
  inline 
  FIndexC<N> 
  FIndexC<N>::operator/(IntT alpha) const { 
    FIndexC<N> ret;
    for(int i = 0;i < N;i++)
      ret[i] = IndexC(data[i] / alpha);
    return ret;
  }
  
  template<unsigned int N>
  inline 
  FIndexC<N> 
  FIndexC<N>::operator/(RealT alpha) const { 
    FIndexC<N> ret;
    for(int i = 0;i < N;i++)
      ret[i] = IndexC(data[i] / alpha);
    return ret;
  }

  template<unsigned int N>
  inline 
  UIntT FIndexC<N>::Hash() const  { 
    UIntT HVal = data[0].V();
    for(UIntT i = 1;i < N;i++) { 
      HVal += ((UIntT) data[i].V());
      HVal ^= data[i].V() << (i * (sizeof(IndexC) * 2));
    }
    return HVal;
  }
  
}
  
#endif
