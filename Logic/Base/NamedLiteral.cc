// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/NamedLiteral.hh"
#include "Ravl/MTLocks.hh"

namespace RavlLogicN {

  //: Get the name of symbol.
  
  StringC NamedLiteralBodyC::Name() const {
    return name;
  }

  //: Get hash value for symbol.
  UIntT NamedLiteralBodyC::Hash() const {
    return name.Hash();
  }
    
  //: Is this equial to another LiteralC ?

  bool NamedLiteralBodyC::IsEqual(const LiteralC &oth) const {
    return oth.Name() == name;
  }

  //---------------------------------------------------------------------
  
  static HashC<StringC,LiteralC> namedLiterals;
  
  //: Constructor.
  
  NamedLiteralC::NamedLiteralC(const StringC &name)
  {
    LiteralC ret;
    MTReadLockC rlock(3);
    if(namedLiterals.Lookup(name,ret)) {
      (*this) = ret;
      return ;
    }
    rlock.Unlock();
    MTWriteLockC wlock(3);
    LiteralC &tmp = namedLiterals[name];
    if(tmp.IsValid()) { // Make sure its not been setup while we swapped locks.
      (*this) = tmp;
      return ;
    }
    // Create a new literal.
    tmp = NamedLiteralC(*new NamedLiteralBodyC(name));
    (*this) = tmp;
  }
}
