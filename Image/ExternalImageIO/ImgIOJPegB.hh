// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPIMAGEIOJPEG_HEADER
#define RAVLDPIMAGEIOJPEG_HEADER
///////////////////////////////////////////////////
//! userlevel=Develop
//! rcsid="$Id$"
//! file="amma/Image/ExtImgIO/ImgIOJPegB.hh"
//! lib=ExtImgIO
//! docentry="Ravl.Image.IO.Formats"
//! author="Charles Galambos"
//! date="29/10/98"

#include "Ravl/Image/ImgIOJPeg.hh"
#include "Ravl/DP/FileFormat.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/Stream.hh"

#include <setjmp.h>

extern "C" {
#include <jpeglib.h>
};

namespace RavlN
{
  //: JPeg Utilities
  
  class DPImageIOJPegBaseC {
  public:    
    DPImageIOJPegBaseC();
    //: Constructor.
    
    ~DPImageIOJPegBaseC();
    //: Destructor.
    
    struct my_error_mgr {
      struct jpeg_error_mgr pub;	/* "public" fields */
      jmp_buf setjmp_buffer;	/* for return to caller */
    };
    
    typedef struct my_error_mgr * my_error_ptr;
    
    const static unsigned int defaultBufferSize = 4096;
    
    unsigned int BufferSize() const
      { return defaultBufferSize; }
    //: Access buffer size.
    
  protected:
    
    bool initalised;
    my_error_mgr jerr;
    unsigned char *buffer;
  };
  
  class DPImageIOJPegIBaseC;

  typedef struct {
    struct jpeg_source_mgr pub;	/* public fields */
    bool start_of_file;
    DPImageIOJPegIBaseC *obj;
    unsigned char *buffer;
  } ravl_source_mgr;
  
  class DPImageIOJPegIBaseC 
    : public DPImageIOJPegBaseC
  {
  public:
    DPImageIOJPegIBaseC(const IStreamC &fin);
    //: Constructor.
    
    ~DPImageIOJPegIBaseC();
    //: Desctructor
    
    void InitI(IStreamC &is);
    //: Initalise Input.
    
    IStreamC &FIn()
      { return fin; }
    //: Access output stream.
    
    bool BaseIsGetEOS() const {
      if(!initalised)
	return true;
      if(source_mgr.pub.bytes_in_buffer > 0)
	return false;
      return const_cast<IStreamC &>(fin).IsEndOfStream();
    }
    //: Test if we're at the end of the stream.
  protected:
    bool SetupFormat(const type_info &ti);
    //: Setup input format.
    // Must be called after header has been read.
    
    IStreamC fin;
    
    ravl_source_mgr source_mgr;
    
    struct jpeg_decompress_struct cinfo;
  };
  
  class DPImageIOJPegOBaseC;
  
  typedef struct {
    struct jpeg_destination_mgr pub; /* public fields */
    DPImageIOJPegOBaseC *obj;
    unsigned char *buffer;
  } ravl_destination_mgr;

  class DPImageIOJPegOBaseC 
    : public DPImageIOJPegBaseC
  {
  public:
    DPImageIOJPegOBaseC(const OStreamC &fout,int compression = 75);
    //: Constructor.
    
    ~DPImageIOJPegOBaseC();
    //: Desctructor
    
    void InitO(OStreamC &os);
    //: Initalise output.
    
    OStreamC &FOut()
      { return fout; }
    //: Access output stream.
  protected:
    bool SetupFormat(const type_info &ti);
    //: Setup output format.
    
    OStreamC fout;
    int compression;
  
    ravl_destination_mgr destination_mgr;
    struct jpeg_compress_struct cinfo;
  };
  
//: Load a PPM image.
  
  template<class PixelT>
  class DPIImageJPegBodyC 
    : public DPIPortBodyC<ImageC<PixelT> >,
      public DPImageIOJPegIBaseC
  {
  public:
    DPIImageJPegBodyC(const StringC &fn);
    //: Constructor from filename.
    
    DPIImageJPegBodyC(const IStreamC &in);
    //: Constructor from stream.
    // Not supported at the moment...
    
    virtual bool IsGetEOS() const;
    //: Is valid data ?
    
    virtual ImageC<PixelT> Get();
    //: Get next piece of data.
    
    virtual bool Get(ImageC<PixelT> &buff);
    //: Get next piece of data.
  protected:
    bool Read(ImageC<PixelT> &buf);
    //: Read image data.
  };
  
  //: Save a  image.
  
  template<class PixelT>
  class DPOImageJPegBodyC : 
    public DPOPortBodyC<ImageC<PixelT> >,
    public DPImageIOJPegOBaseC
  {
  public:
    DPOImageJPegBodyC(const StringC &fn,int compression = 75);
    //: Constructor from filename.
    
    DPOImageJPegBodyC(const OStreamC &strm,int compression = 75);
    //: Constructor from filename.
    // Not supported at the moment...
    
    virtual bool Put(const ImageC<PixelT> &dat);
    //: Put data.
    
    virtual bool IsPutReady() const ;
    //: Is port ready for data ?
    
    
  protected:
    bool Write(const ImageC<PixelT> &buf);
    //: Write image data.
    
    ravl_destination_mgr dstMgr;
    
  };
  //////// DPIImageJPegBodyC ///////////////////////////////////////////////
  
  //: Constructor from filename.
  
  template<class PixelT>
  DPIImageJPegBodyC<PixelT>::DPIImageJPegBodyC(const StringC &nfn) 
    : DPImageIOJPegIBaseC(nfn)
  {}
  
  //: Constructor from stream.
  
  template<class PixelT>
  DPIImageJPegBodyC<PixelT>::DPIImageJPegBodyC(const IStreamC &in)
    : DPImageIOJPegIBaseC(in)
  {}

  //: Is valid data ?
  
  template<class PixelT>
  bool DPIImageJPegBodyC<PixelT>::IsGetEOS() const 
  { return BaseIsGetEOS(); }
  
  
  //: Get next piece of data.
  
  template<class PixelT>
  ImageC<PixelT> DPIImageJPegBodyC<PixelT>::Get() {
    ImageC<PixelT> ret;
    if(BaseIsGetEOS())
      return ret;
    if(!Read(ret))
      cerr << "DPIImageJPegBodyC<PixelT>::Get(), Error reading file.\n";
    return ret;
  }
  
  
  
  //: Get next piece of data.
  
  template<class PixelT>
  bool DPIImageJPegBodyC<PixelT>::Get(ImageC<PixelT> &buff) {
    if(fin.IsEndOfStream())
      return false;
    return Read(buff);
  }
  
  
  //: Read image data.
  
  template<class PixelT>
  bool DPIImageJPegBodyC<PixelT>::Read(ImageC<PixelT> &buff) {
    
    // Establish the setjmp return context for my_error_exit to use.
    if (setjmp(jerr.setjmp_buffer)) {
      // If we get here, the JPEG code has signaled an error.
      return false;
    }
    
    jpeg_read_header(&cinfo, true);
    jpeg_start_decompress(&cinfo);
    
    /* We may need to do some setup of our own at this point before reading
     * the data.  After jpeg_start_decompress() we have the correct scaled
     * output image dimensions available, as well as the output colormap
     * if we asked for color quantization.
     */ 
    
    buff = ImageC<PixelT>(cinfo.image_height,cinfo.image_width);  
    JSAMPROW buffer[1];	/* pointer to JSAMPLE row[s] */
    
    const IndexC LCol = buff.LCol();
    IndexC crow = buff.TRow();
    
    while (cinfo.output_scanline < cinfo.output_height) {
      buffer[0] = (JSAMPROW) (& (buff[crow++][LCol]));
      jpeg_read_scanlines(&cinfo,buffer , 1);    
    }
    
    jpeg_finish_decompress(&cinfo);
    
    return true;
  }
  
  //// DPOImageJPegBodyC /////////////////////////////////////////////
  
  //: Constructor from filename.
  
  template<class PixelT>
  DPOImageJPegBodyC<PixelT>::DPOImageJPegBodyC(const StringC &nfn,int ncompression) 
    : DPImageIOJPegOBaseC(OStreamC(nfn),ncompression)
  {}
  
  
  //: Constructor from filename.
  
  template<class PixelT>
  DPOImageJPegBodyC<PixelT>::DPOImageJPegBodyC(const OStreamC &strm,int ncompression) 
    : DPImageIOJPegOBaseC(strm,ncompression)
  {}
  
  
  //: Put data.
  
  template<class PixelT>
  bool DPOImageJPegBodyC<PixelT>::Put(const ImageC<PixelT> &dat) {
    if(!initalised) {
      cerr << "DPOImageJPegBodyC<PixelT>::Write(), Not initalised. \n";
      return false;
    }
    if(!fout.good())
      return false;
    return Write(dat);
  }
  
  
  //: Is port ready for data ?
  
  template<class PixelT>
  bool DPOImageJPegBodyC<PixelT>::IsPutReady() const {
    if(!initalised)
      return false;
    return fout.good();
  }
  
  
  //: Write image data.
  
  template<class PixelT>
  bool DPOImageJPegBodyC<PixelT>::Write(const ImageC<PixelT> &buff) {
    
    // Establish the setjmp return context for my_error_exit to use.
    if (setjmp(jerr.setjmp_buffer)) {
      cerr << "DPOImageJPegBodyC<PixelT>::Write(), Error found. \n";
      // If we get here, the JPEG code has signaled an error.
      return false;
    }
    
    JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
    
    cinfo.image_width = buff.Cols(); 	/* image width and height, in pixels */
    cinfo.image_height = buff.Rows();
    
    if(!SetupFormat(typeid(PixelT)))
    return false; /* Don't know pixel type... */
    
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, compression, true /* limit to baseline-JPEG values */);
    
    jpeg_start_compress(&cinfo, true);
    
    const IndexC LCol = buff.LCol();
    IndexC crow = buff.TRow();
    while (cinfo.next_scanline < cinfo.image_height) {
      row_pointer[0] = (JSAMPROW)(& (buff[crow++][LCol]));
      jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    
    jpeg_finish_compress(&cinfo);
    
    return true;
  }
  
}
#endif
  
