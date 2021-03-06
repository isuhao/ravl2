# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id: defs.mk 7033 2008-11-18 14:14:59Z simondennis $"
#! file="Ravl/Image/ImageIO/defs.mk"

PACKAGE = Ravl/Image

DESCRIPTION =  File IO methods.

HEADERS = ImgIOPNMB.hh ImgIOPNM.hh PNMFormat.hh ImgIO.hh 

SOURCES = ImgIOPNM.cc PNMFormat.cc ImgIOInt.cc ImgIOByte.cc \
 ImgIOUInt16.cc ImgIOByteRGB.cc ImgIOByteYUV.cc ImgIOReal.cc \
 ImgIORealRGB.cc ImgIOByteRGBA.cc ImgIORealRGBA.cc ImgIORealYUV.cc ImgIOUInt16RGB.cc \
 ImgIOByteYUVA.cc ImgIOFloat.cc \
 ImgIOByteYCbCrBT601Value.cc ImgIOUInt16YCbCrBT601Value.cc ImgIOYCbCrBT601ValueFloat.cc \
 ImgIOByteYCbCr422BT601Value.cc ImgIOUInt16YCbCr422BT601Value.cc \
 ImgTypeCnv.cc ImgTypeCnv2.cc ImgTypeCnv3.cc ImgTypeCnv4.cc \
 ImgIOByteYUV422.cc ImgIOByteVYU.cc ImgTypeCnv5.cc ImgTypeCnv6.cc \
 ImgIOByteYCbCrBT709Value.cc ImgIOUInt16YCbCrBT709Value.cc ImgIOYCbCrBT709ValueFloat.cc \
 ImgIOByteYCbCr422BT709Value.cc ImgIOUInt16YCbCr422BT709Value.cc


# ImgIOPixel.cc  PixelIO.cc 

MUSTLINK = RavlImgIO.cc 

PLIB = RavlImageIO

EXAMPLES = exImgIO.cc

TESTEXES = testImgIO.cc

USESLIBS = RavlCore RavlIO RavlImage

PROGLIBS = RavlOS

EHT = Ravl.API.Images.IO.html

AUXDIR = share/RAVL/pixmaps
AUXFILES = monkey.ppm
