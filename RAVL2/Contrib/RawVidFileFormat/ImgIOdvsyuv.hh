// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_IMGIODVSYUV_HEADER
#define RAVLIMAGE_IMGIODVSYUV_HEADER 1
////////////////////////////////////////////////////
//! file="Ravl/Image/VideoIO/ImgIOdvsyuv.hh"
//! lib=RavlVideoIO
//! docentry="Ravl.API.Images.Video.Video IO"
//! example=exImgSeq.cc
//! rcsid="$Id: ImgIOdvsyuv.hh 5240 2005-12-06 17:16:50Z plugger $"
//! author="Simon Ennis"
//! date="08/04/99"

#include "Ravl/DP/SPort.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteYUV422Value.hh"
#include "Ravl/Stream.hh"
#include "Ravl/Assert.hh"
#include "Ravl/TimeCode.hh" 
#include "Ravl/Types.hh"
#include "Ravl/Image/Utilities.hh"
#include "Ravl/Audio/Types.hh"
#include "Ravl/Buffer.hh"
#include "Ravl/Image/NewGrabfileReader.hh"
#include "Ravl/Image/NewGrabfileWriter.hh"
#include "Ravl/Image/WarpScale.hh"

using namespace RavlImageN;
using namespace RavlN;

namespace RavlImageN {
  


  ///////////////////////////////////
  //! userlevel=Develop
  //: Basic information about a cif file
  
  class DPImageDVSYUV422BaseBodyC {
  public:  
    DPImageDVSYUV422BaseBodyC(const Index2dC &size = Index2dC(576,720))
      : frameSize(0),
      frameNo(0),
      seqSize((UIntT) -1)
      { SetupForVariant(size); }
    //: Constructor.
    // This constructs with the basic yuv format.
    
    bool SetupForVariant(const StringC &suffix);
    //: Setup for variant.
    // str should be one of :
    
    bool SetupForVariant(const Index2dC &size);
    //: Setup for variant.
    // Where size in the size of the Y image.
    
    inline UIntT CalcOffset(UIntT frameNo) const {
      RavlAssert(frameSize > 0);
      return frameSize * frameNo; 
    }
    //: Calculate the offset of a frame.

    inline IntT CalcOffset(IntT frameNo) const  {
      RavlAssert(frameSize > 0);
      return frameSize * frameNo; 
    }
    //: Calculate the offset of a frame.
  
    void SetSequenceSize(UIntT val) { seqSize = val; }
    //: Set the sequence size.
    
    UIntT SeqSize() const { return seqSize; }
    //: Get the sequence size.
    
    
  protected:
    static inline bool is_odd (IndexC x) {return bool (x%2 != 0);}
    // Is an index odd ?

    ImageRectangleC rect; // Size of YUV variant. Origin 0,0
    UIntT frameSize; // Size of one frame in bytes.
    UIntT frameNo; // Current frameno.
    UIntT seqSize;  // Number of frames in sequence, ((UIntT) -1) if unknown
  };
  
  ///////////////////////////////////
  //! userlevel=Develop
  //: Load a YUV image in YUV format.
  
  class DPIImageDVSYUV422BodyC 
    : public DPISPortBodyC<ImageC<ByteYUV422ValueC> >,
      public DPImageDVSYUV422BaseBodyC
  {
  public:  
    DPIImageDVSYUV422BodyC(GrabfileReaderC& file_reader,const IStreamC &nStrm,const Index2dC &size = Index2dC(576,720));
    //: Constructor from stream 
    
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off);
    //: Delta Seek, goto location relative to the current one.
  
    virtual UIntT Tell() const; 
    //: Find current location in stream.
    
    virtual UIntT Size() const; 
  //: Find the total size of the stream.
    
    virtual ImageC<ByteYUV422ValueC> Get();
    //: Get next image.
    
    virtual bool Get(ImageC<ByteYUV422ValueC> &buff);
    //: Get next image.
    
    virtual bool IsGetReady() const 
      {  
        return file_read.Ok();
      }
    //: Is some data ready ?
    // TRUE = yes.
    // Defaults to !IsGetEOS().
    
    virtual bool IsGetEOS() const
      { 
         return file_read.HaveMoreFrames();
      }
    //: Has the End Of Stream been reached ?
  // TRUE = yes.
    
  protected:
    IStreamC strm; 
    GrabfileReaderC& file_read;  
  };
  
  ///////////////////////////////////
  //! userlevel=Develop
  //: Save a YUV image in YUV format.
  
  class DPOImageDVSYUV422BodyC 
    : public DPOSPortBodyC<ImageC<ByteYUV422ValueC> >,
      public DPImageDVSYUV422BaseBodyC
  {
  public:
    DPOImageDVSYUV422BodyC(GrabfileWriterC& file_write,const OStreamC &nStrm,const Index2dC &size  = Index2dC(576,720));
    //: Constructor from stream 
    
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    // Returns FALSE, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off);
    //: Delta Seek, goto location relative to the current one.
    
    virtual UIntT Tell() const; 
    //: Find current location in stream.
    
    virtual UIntT Size() const; 
    //: Find the total size of the stream.
  
    bool Put(const ImageC<ByteYUV422ValueC> &Img);
    //: Put image to a stream.
    
    virtual bool IsPutReady() const 
      { return strm.good(); }
    //: Read to write some data ?
    // TRUE = yes.
    
    virtual void PutEOS() {}
    //: Put End Of Stream marker.
   
  protected: 
    OStreamC strm;
    GrabfileWriterC& file_writer;
    mutable VideoModeT vmode;
    mutable ByteFormatT bformat;
    mutable IntT vbuffer;
    mutable ImageC<ByteYUV422ValueC> Imgcopy;
  };

  //! userlevel=Normal
  //: Load a YUV image in YUV format.
  
  class DPIImageDVSYUV422C 
    : public DPISPortC<ImageC<ByteYUV422ValueC> >
  {
  public:
    DPIImageDVSYUV422C(GrabfileReaderC& file_reader,const StringC &fn);
    //: Constructor from filename.  
    
    DPIImageDVSYUV422C(GrabfileReaderC& file_reader,const IStreamC &nStrm,const Index2dC &size = Index2dC(576,720))
      : DPEntityC(*new DPIImageDVSYUV422BodyC(file_reader,nStrm,size))
      {}
    //: Constructor from stream 
    
  };
  
  //! userlevel=Normal
  //: Save a YUV image in YUV format.
  
  class DPOImageDVSYUV422C 
    : public DPOSPortC<ImageC<ByteYUV422ValueC> >
  {
  public:
    DPOImageDVSYUV422C(GrabfileWriterC& file_write,const StringC &fn);
    //: Constructor from filename.  
    
    DPOImageDVSYUV422C(GrabfileWriterC& file_write,const OStreamC &nStrm,const Index2dC &size = Index2dC(576,720))
      : DPEntityC(*new DPOImageDVSYUV422BodyC(file_write,nStrm,size))
      {}
    //: Constructor from stream 
    
  };

}

#endif
