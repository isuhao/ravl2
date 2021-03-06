// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTIFFFORMAT_HEADER
#define RAVLTIFFFORMAT_HEADER 1
////////////////////////////////////////////////////////////
//! rcsid="$Id: TiffFormat.hh 5240 2005-12-06 17:16:50Z plugger $"
//! file="Ravl/Image/ExternalImageIO/TiffFormat.hh"
//! lib=RavlExtImgIO
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.IO.Formats"
//! date="29/10/98"

#include "Ravl/DP/FileFormat.hh"
#include "Ravl/Image/Image.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: TIFF File format information.
  
  class FileFormatTIFFBodyC 
    : public FileFormatBodyC 
  {
  public:
    FileFormatTIFFBodyC(const StringC &id,const StringC &desc);
    //: Constructor.
    
    const type_info &ChooseFormat(const type_info &obj_type) const;
    //: Try and choose best format for IO.
    
    virtual const type_info &ProbeLoad(IStreamC &in,const type_info &obj_type) const;
    //: Is stream in std stream format ?
    
    virtual const type_info &ProbeLoad(const StringC &filename,IStreamC &in,const type_info &obj_type) const;
    //: Probe for load.
    
    virtual const type_info &ProbeSave(const StringC &filename,const type_info &obj_type,bool forceFormat) const;
    //: Probe for Save.
    
    virtual DPIPortBaseC CreateInput(const StringC &filename,const type_info &obj_type) const;
    //: Create a input port for loading from file 'filename'.
    // Will create an Invalid port if not supported. <p>
    
    virtual DPOPortBaseC CreateOutput(const StringC &filename,const type_info &obj_type) const;
    //: Create a output port for saving to file 'filename'..
    // Will create an Invalid port if not supported. <p>
    
    virtual DPIPortBaseC CreateInput(IStreamC &in,const type_info &obj_type) const;
    //: Create a input port for loading.
    // Will create an Invalid port if not supported.
    
    virtual DPOPortBaseC CreateOutput(OStreamC &out,const type_info &obj_type) const;
    //: Create a output port for saving.
    // Will create an Invalid port if not supported.
    
    virtual const type_info &DefaultType() const; 
    //: Get prefered IO type.
    
    virtual IntT Priority() const { return 0; }
    //: Find the priority of the format. the higher the better.
    // Default is zero, this is better than the default (streams.)
    
    virtual bool IsStream() const { return false; }
    //: Test if format is a fully streamable.
    // i.e. check if you can read/write more than object object.
    // png supports sequences.. but not with this software for now...
    
  protected:
  };
  
  /////////////////////////////
  //! userlevel=Advanced
  //: Create an instance of a TIFF File Format.
  
  class FileFormatTIFFC : public FileFormatC<ImageC<ByteT> > {
  public:
    FileFormatTIFFC(const StringC &id,const StringC &desc)
      : FileFormatC<ImageC<ByteT> >(*new FileFormatTIFFBodyC(id,desc))
      {}
  };
}

#endif
