// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html


%include "Ravl/Swig/Types.i"
%include "Ravl/Swig/Index.i"

%{
#ifdef SWIGPERL
#undef Copy
#endif

#include "Ravl/SArray1d.hh"

#ifdef SWIGPERL
#define Copy(s,d,n,t)   (MEM_WRAP_CHECK_(n,t) (void)memcpy((char*)(d),(const char*)(s), (n) * sizeof(t)))
#endif
%}

namespace RavlN {

  template<typename DataT>
  class SArray1dC {
  public:
    SArray1dC<DataT>(SizeT size);
    SArray1dC<DataT>();
    %extend {
      DataT &Access(const IndexC &index)
	{ return self->operator[](index); }
    }
    %extend {
      DataT &Access(const UIntT &index)
	{ return self->operator[](index); }
    }
    %extend {
      void Set(const UIntT &index, const DataT & object)
	{ self->operator[](index) = object; }
    }

    SizeT Size() const;
    // Get the size of the array

  };
}
