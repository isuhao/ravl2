////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/Image/ImgIOTiff.hh"
#include "amma/Image/ImgIOTiffB.hh"
#include "amma/ImagIter.hh"
#include <ctype.h>

#define DPDEBUG 0
#if DPDEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

//: Constructor.

DPImageIOTIFFBaseC::DPImageIOTIFFBaseC()
  : tif(0)
{}

//: Destructor.

DPImageIOTIFFBaseC::~DPImageIOTIFFBaseC()
{
  if(tif != 0) {
    TIFFClose(tif);
    ONDEBUG(tif = 0);
  }
}

///////////////////////////////////////

//: Constructor from filename.

DPOImageTIFFByteRGBABodyC::DPOImageTIFFByteRGBABodyC(FilenameC fn)
  : done(FALSE)
{
  ONDEBUG(cerr << "DPOImageTIFFByteRGBABodyC(), Open file '" << fn << "' \n");
  tif = TIFFOpen(fn.chars(),"w");
}

//: Constructor from stream.

DPOImageTIFFByteRGBABodyC::DPOImageTIFFByteRGBABodyC(const OStreamC &strm)
  : outf(strm),
    done(FALSE)
{
  ONDEBUG(cerr << "DPOImageTIFFByteRGBABodyC(), Open stream '" << strm.Name() << "' \n");
  tif = TIFFClientOpen(outf.Name().chars(),"w",
		       this,
		       &TIFFReadProc, &TIFFWriteProc,
		       &TIFFSeekProc, &TIFFCloseProc,
		       &TIFFSizeProc,
		       &TIFFMapFileProc, &TIFFUnmapFileProc
		       );
}

//: Is port ready for data ?

BooleanT DPOImageTIFFByteRGBABodyC::IsPutReady() const 
{ return tif != 0 && !done;  }

//: Write out image.

BooleanT DPOImageTIFFByteRGBABodyC::Put(const ImageC<ByteRGBXValueC> &img)
{
  uint32 w = img.Cnum();
  uint32 h = img.Rnum();
  ONDEBUG(cerr << "DPIImageTIFFByteRGBABodyC::Put(), Called. " << w << " " << h << " \n");
  if (tif == 0) 
    return false;
  
  uint32 rowsperstrip = (uint32) -1;

  TIFFSetField(tif, TIFFTAG_ORIENTATION, ORIENTATION_BOTLEFT);
  TIFFSetField(tif, TIFFTAG_IMAGEWIDTH, w);
  TIFFSetField(tif, TIFFTAG_IMAGELENGTH, h);
  TIFFSetField(tif, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
  TIFFSetField(tif, TIFFTAG_SAMPLESPERPIXEL, 4);
  TIFFSetField(tif, TIFFTAG_BITSPERSAMPLE,8);
  TIFFSetField(tif, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
  TIFFSetField(tif, TIFFTAG_ROWSPERSTRIP,
	       TIFFDefaultStripSize(tif,rowsperstrip));
  TIFFSetField(tif, TIFFTAG_COMPRESSION, COMPRESSION_NONE);

  const IndexT offset = img.LCol();
  
  ONDEBUG(cerr << "DPIImageTIFFByteRGBABodyC::Put(), TRow:" << img.TRow() << " BRow:" << img.BRow() << " . \n");
  for (IndexT row = img.TRow(); row <= img.BRow(); row++)
    TIFFWriteScanline(tif,(char *) &(img[row][offset]), row.V(),0);
  
  TIFFFlush(tif);
  done = TRUE;
  return TRUE;
}


// Read some data.

tsize_t DPOImageTIFFByteRGBABodyC::TIFFReadProc(thandle_t dptr, tdata_t data, tsize_t noBytes) {
  cerr << "DPOImageTIFFByteRGBABodyC::TIFFWriteProc(), WARNING: read called on a write-only stream. \n";
  assert(0);
  return 0;
}

tsize_t DPOImageTIFFByteRGBABodyC::TIFFWriteProc(thandle_t dptr, tdata_t data, tsize_t noBytes) {
  DPOImageTIFFByteRGBABodyC &body = *(DPOImageTIFFByteRGBABodyC *) dptr;
  body.outf.write((const char *) data,noBytes);
  return noBytes;
}

toff_t  DPOImageTIFFByteRGBABodyC::TIFFSeekProc(thandle_t dptr, toff_t off, int whence) {
  DPOImageTIFFByteRGBABodyC &body = *(DPOImageTIFFByteRGBABodyC *) dptr;
  switch(whence)
    {
    case SEEK_SET: body.outf.seekg(off,ios::beg); break;
    case SEEK_CUR: if(off != 0) body.outf.seekg(off,ios::cur); break;
    case SEEK_END: body.outf.seekg(off,ios::end); break;
    default:
      cerr << "DPOImageTIFFByteRGBABodyC::TIFFSeekProc(), WARNING: Illegal value for whence : " << whence << "\n";
    }
  return body.outf.Tell();
}

int DPOImageTIFFByteRGBABodyC::TIFFCloseProc(thandle_t dptr) {
  DPOImageTIFFByteRGBABodyC &body = *((DPOImageTIFFByteRGBABodyC *) dptr);
  body.outf.os() << flush;   
  // We don't actuall close there.
  return 1;
}

toff_t DPOImageTIFFByteRGBABodyC::TIFFSizeProc(thandle_t dptr) {
  DPOImageTIFFByteRGBABodyC &body = *((DPOImageTIFFByteRGBABodyC *) dptr);
  // Not very quick, but it should work...
  toff_t at = body.outf.Tell();
  body.outf.seekg(0,ios::end);
  toff_t ret = body.outf.Tell();
  body.outf.seekg(at,ios::beg);
  return ret;
}

int DPOImageTIFFByteRGBABodyC::TIFFMapFileProc(thandle_t dptr, tdata_t*, toff_t*) {
  return 0;
}

void DPOImageTIFFByteRGBABodyC::TIFFUnmapFileProc(thandle_t dptr, tdata_t, toff_t) {
}

///////////////////////////////////////

//: Constructor from filename.

DPIImageTIFFByteRGBABodyC::DPIImageTIFFByteRGBABodyC(FilenameC fn)
  : done(FALSE)
{
  ONDEBUG(cerr << "DPIImageTIFFByteRGBABodyC(), Open file '" << fn << "' \n");
  tif = TIFFOpen(fn.chars(),"r");
}


//: Constructor from stream.

DPIImageTIFFByteRGBABodyC::DPIImageTIFFByteRGBABodyC(const IStreamC &in)
  : inf(in),
    done(FALSE)
{
  ONDEBUG(cerr << "DPIImageTIFFByteRGBABodyC(), Open istream \n");
  tif = TIFFClientOpen(inf.Name().chars(),"r",
		       this,
		       &TIFFReadProc, &TIFFWriteProc,
		       &TIFFSeekProc, &TIFFCloseProc,
		       &TIFFSizeProc,
		       &TIFFMapFileProc, &TIFFUnmapFileProc
		       );
  
}

//: Is valid data ?

BooleanT DPIImageTIFFByteRGBABodyC::IsGetEOS() const
{ return (done || tif == 0) ; }

//: Get next piece of data.

ImageC<ByteRGBXValueC> DPIImageTIFFByteRGBABodyC::Get()
{
  ONDEBUG(cerr << "DPIImageTIFFByteRGBABodyC::Get(), Called. \n");
  ImageC<ByteRGBXValueC> img;
  if (tif == 0) 
    throw DataNotReadyC("DPIImageTIFFByteRGBABodyC: Not file handle. ");
  size_t npixels;
  uint32* raster;
#if 0
  uint32 w, h;
  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
  npixels = w * h;
  raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
  if (raster == NULL)
    throw DataNotReadyC("DPIImageTIFFByteRGBABodyC: Allocation failed.. ");
  
  if (!TIFFReadRGBAImage(tif, w, h, raster, 0))
    throw DataNotReadyC("DPIImageTIFFByteRGBABodyC: Read failed. ");
  img = ImageC<ByteRGBXValueC>(h,w,BufferRC<ByteRGBXValueC>((ByteRGBXValueC *) raster,true),true);
#else
  TIFFRGBAImage tiffimg;
  char emsg[1024];
  
  if (!TIFFRGBAImageBegin(&tiffimg, tif, 0, emsg)) {
    throw DataNotReadyC("DPIImageTIFFByteRGBABodyC: ImageBegin failed.. ");
  }
  npixels = tiffimg.width * tiffimg.height;
  raster = (uint32*) _TIFFmalloc(npixels * sizeof (uint32));
  if (raster == 0) {
    TIFFRGBAImageEnd(&tiffimg);
    throw DataNotReadyC("DPIImageTIFFByteRGBABodyC: Allocation failed.. ");
  }
  
  if (!TIFFRGBAImageGet(&tiffimg, raster, tiffimg.width, tiffimg.height)) {
    TIFFRGBAImageEnd(&tiffimg);
    throw DataNotReadyC("DPIImageTIFFByteRGBABodyC: Allocation failed.. ");
  }
  ONDEBUG(cerr << "DPIImageTIFFByteRGBABodyC::Get(), Orientation : " << tiffimg.orientation << "\n");
  switch(tiffimg.orientation)
    {
    default:
      cerr << "DPIImageTIFFByteRGBABodyC::Get(), WARNING Unexpected orientation : " << tiffimg.orientation << "\n";
    case ORIENTATION_BOTLEFT:
      img = ImageC<ByteRGBXValueC>(tiffimg.height,tiffimg.width,BufferRC<ByteRGBXValueC>((ByteRGBXValueC *) raster,true),false);
      break;
    case ORIENTATION_TOPLEFT:
      img = ImageC<ByteRGBXValueC>(tiffimg.height,tiffimg.width,BufferRC<ByteRGBXValueC>((ByteRGBXValueC *) raster,true),true);
      break;   
    }
  TIFFRGBAImageEnd(&tiffimg);
#endif
  done = TRUE;
  return img;
}

// Read some data.

tsize_t DPIImageTIFFByteRGBABodyC::TIFFReadProc(thandle_t dptr, tdata_t data, tsize_t noBytes) {
  DPIImageTIFFByteRGBABodyC &body = *(DPIImageTIFFByteRGBABodyC *) dptr;
  body.inf.read((char *) data,noBytes);
  return body.inf.gcount();
}

tsize_t DPIImageTIFFByteRGBABodyC::TIFFWriteProc(thandle_t dptr, tdata_t, tsize_t) {
  cerr << "DPIImageTIFFByteRGBABodyC::TIFFWriteProc(), WARNING: Write called on a read-only stream. \n";
  assert(0);
  return 0;
}

toff_t  DPIImageTIFFByteRGBABodyC::TIFFSeekProc(thandle_t dptr, toff_t off, int whence) {
  DPIImageTIFFByteRGBABodyC &body = *(DPIImageTIFFByteRGBABodyC *) dptr;
  switch(whence)
    {
    case SEEK_SET: body.inf.seekg(off,ios::beg); break;
    case SEEK_CUR: if(off != 0) body.inf.seekg(off,ios::cur); break;
    case SEEK_END: body.inf.seekg(off,ios::end); break;
    default:
      cerr << "DPIImageTIFFByteRGBABodyC::TIFFSeekProc(), WARNING: Illegal value for whence : " << whence << "\n";
    }
  return body.inf.Tell();
}

int DPIImageTIFFByteRGBABodyC::TIFFCloseProc(thandle_t dptr) {
  //DPIImageTIFFByteRGBABodyC &body = *((DPIImageTIFFByteRGBABodyC *) dptr);
  //  return body.inf.is() << flush;   
  // We don't actuall close there.
  return 1;
}

toff_t DPIImageTIFFByteRGBABodyC::TIFFSizeProc(thandle_t dptr) {
  DPIImageTIFFByteRGBABodyC &body = *((DPIImageTIFFByteRGBABodyC *) dptr);
  // Not very quick, but it should work...
  toff_t at = body.inf.Tell();
  body.inf.seekg(0,ios::end);
  toff_t ret = body.inf.Tell();
  body.inf.seekg(at,ios::beg);
  return ret;
}

int DPIImageTIFFByteRGBABodyC::TIFFMapFileProc(thandle_t dptr, tdata_t*, toff_t*) {
  return 0;
}

void DPIImageTIFFByteRGBABodyC::TIFFUnmapFileProc(thandle_t dptr, tdata_t, toff_t) {
}


////////////////////////////////////////////
//: Save a RGBA image in ByteRGBA format.

DPIImageTIFFByteRGBAC::DPIImageTIFFByteRGBAC(FilenameC fn)
  : DPEntityC(*new DPIImageTIFFByteRGBABodyC(fn))
{}

DPIImageTIFFByteRGBAC::DPIImageTIFFByteRGBAC(const IStreamC &strm)
  : DPEntityC(*new DPIImageTIFFByteRGBABodyC(strm))
{}

////////////////////////////////////////////
//: Load a RGBA image in ByteRGBA format.

DPOImageTIFFByteRGBAC::DPOImageTIFFByteRGBAC(FilenameC fn)
  : DPEntityC(*new DPOImageTIFFByteRGBABodyC(fn))
{}

DPOImageTIFFByteRGBAC::DPOImageTIFFByteRGBAC(const OStreamC &strm)
  : DPEntityC(*new DPOImageTIFFByteRGBABodyC(strm))
{}

