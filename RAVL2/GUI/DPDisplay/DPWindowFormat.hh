// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLGUI_DPWINDOWFORMAT_HEADER
#define RAVLGUI_DPWINDOWFORMAT_HEADER 1
//////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id: DPWindowFormat.hh 6701 2008-04-09 16:07:40Z ees1wc $"
//! lib=RavlDPDisplay
//! file="Ravl/GUI/DPDisplay/DPWindowFormat.hh"
//! author="Charles Galambos"
//! docentry="Ravl.API.Graphics.Data Display"

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/GUI/DPDisplayObj.hh"

namespace RavlGUIN {
  
  class DPDisplayObjC;
  
  
  class DPWindowFormatBodyC
    : public FileFormatBodyC
  {
  public:
    DPWindowFormatBodyC();
    //: Default constructor.
    
    virtual ~DPWindowFormatBodyC() { }
    //: Need virtual destructor for class with virtual methods

    virtual const type_info &ProbeSave(const StringC &filename,const type_info &obj_type,bool forceFormat) const;
    //: Probe for Save.
    
    virtual DPOPortBaseC CreateOutput(const StringC &filename,const type_info &obj_type) const;
    //: Create a output port for saving.
    // Will create an Invalid port if not supported.
    
    virtual const type_info &DefaultType() const
    { return typeid(DPDisplayObjC); }
    //: Get prefered IO type.
    
    virtual bool IsStream() const { return true; }
    //: Test if format is a fully streamable.
    // i.e. check if you can read/write more than object object.
    
  };

  class DPWindowFormatC
    : public FileFormatBaseC
  {
  public:
    DPWindowFormatC()
      : FileFormatBaseC(*new DPWindowFormatBodyC())
    {}
    //: Default constructor.
  };

}

#endif
