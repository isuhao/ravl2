// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICLITERALMAPITER_HEADER
#define RAVLLOGICLITERALMAPITER_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Logic"
//! lib=RavlLogic

#include "Ravl/Logic/LiteralIter.hh"

namespace RavlLogicN {
  
  template<class DataT>
  class LiteralMapIterBodyC 
    : public LiteralIterBodyC
  {
  public:
    LiteralMapIterBodyC()
    {}
    //: Default constructor.
    
    virtual DataT &MappedData() {
      RavlAssertMsg(0,"LiteralMapIterBodyC<>::MappedData(), Abstract method called.");
      return *new DataT(); // Dummy return.
    }
    //: Access data.
    
    virtual const DataT &MappedData() const {
      RavlAssertMsg(0,"LiteralMapIterBodyC<>::MappedData() const, Abstract method called.");
      return *new DataT(); // Dummy return.
    }
    //: Access data.
  };
  
  template<class DataT>
  class LiteralMapIterC 
    : public LiteralIterC
  {
  public:
    LiteralMapIterC()
    {}
    //: Default constructor.
    // creates an invalid handle.
    
  protected:
    LiteralMapIterC(LiteralMapIterBodyC<DataT> &bod)
      : LiteralIterC(bod)
    {}
    //: Body constructor
    
    LiteralMapIterBodyC<DataT> &Body()
    { return static_cast<LiteralMapIterBodyC<DataT> &>(LiteralIterC::Body()); }
    //: Access body.
    
    const LiteralMapIterBodyC<DataT> &Body() const
    { return static_cast<const LiteralMapIterBodyC<DataT> &>(LiteralIterC::Body()); }
    //: Access body.
  public:
    
    inline DataT &MappedData() 
    { return Body().MappedData(); }
    //: Value literal is mapped to.
    
    inline const DataT &MappedData() const
    { return Body().MappedData(); }
    //: Value literal is mapped to.

  };
}

#endif
