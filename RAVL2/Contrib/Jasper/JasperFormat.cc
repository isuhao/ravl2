// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id: JasperFormat.cc 5079 2005-08-12 11:32:16Z hickson $"
//! lib=RavlImgIOJasper
//! file="Ravl/Image/ExternalImageIO/JasperFormat.cc"

#include "Ravl/Image/JasperFormat.hh"
#include "Ravl/Image/ImgIOJasper.hh"
#include <ctype.h>

#define USE_JASPERWRITE 1

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  
  void InitJasperFormat()
  {}
  
  // JASPER ////////////////////////////////////////////////////////////////
  
  //: Constructor.
  
  FileFormatJasperBodyC::FileFormatJasperBodyC(const RealT i_compressionRate,const StringC &id,const StringC &desc)
    : FileFormatBodyC(id,desc),
      compressionRate(i_compressionRate)
  {}
  
  //: Try and choose best format for IO.
  
  const type_info &FileFormatJasperBodyC::ChooseFormat(const type_info &obj_type) const  {
    return typeid(ImageC<ByteRGBValueC>);   
  }
  
  //: Is stream in std stream format ?
  
  const type_info &
  FileFormatJasperBodyC::ProbeLoad(IStreamC &in,const type_info &obj_type) const {
#if 0
    ONDEBUG(cerr << "FileFormatJasperBodyC::ProbeLoad(), called. \n");
    // Can't probe from a stream at the moment.
    ONDEBUG(cerr << "FileFormatJasperBodyC::ProbeLoad(), Not readable by Jasper. \n");
    return typeid(void);
#else
    DPImageIOJasperBaseC jsp;
    streampos pos = in.Tell(); 
    // Check format
    bool ok = jsp.OpenIStream(in) && jsp.CanReadImage();
    // Reset stream position.
    in.Seek(pos);
    if(ok) return typeid(ImageC<ByteRGBValueC>);    
    return typeid(void);
#endif
  }
  
  const type_info &
  FileFormatJasperBodyC::ProbeLoad(const StringC &nfilename,IStreamC &in,const type_info &obj_type) const {
    DPImageIOJasperBaseC jsp;
    ONDEBUG(cerr << "FileFormatJasperBodyC::ProbeLoad(), Req:" <<obj_type.name() << "  \n");
    if(jsp.OpenRead(nfilename) && jsp.CanReadImage())
      return typeid(ImageC<ByteRGBValueC>);   
    return typeid(void);
  }
  
  const type_info &
  FileFormatJasperBodyC::ProbeSave(const StringC &filename,const type_info &obj_type,bool forceFormat ) const {
#if USE_JASPERWRITE
    if(!forceFormat) {
      if(DPImageIOJasperBaseC::FindFormatByFilename(filename) < 0)
	return typeid(void);
    }
    const type_info &pref = ChooseFormat(obj_type);
    ONDEBUG(cerr << "FileFormatJasperBodyC::ProbeSave(), Req:" << obj_type.name() << "  Ret:" << pref.name() << " \n");
    return pref;
#else
    return typeid(void);   
#endif
  }
  
  //: Create a input port for loading from file 'filename'.
  // Will create an Invalid port if not supported. <p>
  DPIPortBaseC FileFormatJasperBodyC::CreateInput(const StringC &fn,const type_info &obj_type) const {
    return DPIImageJasperByteRGBC(fn);
  }
  
  //: Create a output port for saving to file 'filename'..
  // Will create an Invalid port if not supported. <p>
  
  DPOPortBaseC FileFormatJasperBodyC::CreateOutput(const StringC &fn,const type_info &obj_type) const {
#if USE_JASPERWRITE
    return DPOImageJasperByteRGBC(fn,compressionRate);
#else
    return DPOPortBaseC();  
#endif
  }
  
  //: Create a input port for loading.
  // Will create an Invalid port if not supported.
  
  DPIPortBaseC FileFormatJasperBodyC::CreateInput(IStreamC &in,const type_info &obj_type) const { 
    //return ;  // This doesn't work at the moment
    return DPIImageJasperByteRGBC(in);
  }
  
  //: Create a output port for saving.
  // Will create an Invalid port if not supported.
  
  DPOPortBaseC FileFormatJasperBodyC::CreateOutput(OStreamC &out,const type_info &obj_type) const  {
    return DPOImageJasperByteRGBC(out,"jp2",compressionRate);
  }
  
  //: Get prefered IO type.
  
  const type_info &FileFormatJasperBodyC::DefaultType() const  { 
    return typeid(ImageC<ByteRGBValueC>); 
  }

#if USE_JASPERWRITE
  FileFormatJasperC RegisterFileFormatJasper(1.0,"Jasper","Jasper file IO. ");
  FileFormatJasperC RegisterFileFormatJasperLossy1(1.0/7.0,"JasperLossy1","Jasper file IO. (Compression rate = 1:7)");
  FileFormatJasperC RegisterFileFormatJasperLossy2(0.08,"JasperLossy2","Jasper file IO. (Compression rate = 2:25)");
#else
  FileFormatJasperC RegisterFileFormatJasper(1.0,"Jasper","Jasper file IO. (only reading supported)");
  FileFormatJasperC RegisterFileFormatJasperLossy1(1.0/7.0,"JasperLossy1","Jasper file IO. (only reading supported).");
  FileFormatJasperC RegisterFileFormatJasperLossy2(0.08,"JasperLossy2","Jasper file IO. (only reading supported).");
#endif
  
}
