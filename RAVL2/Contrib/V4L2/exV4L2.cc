// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////////////////
//! file = "Ravl/Contrib/V4L2/exV4L2.cc"
//! lib = RavlImgIOV4L2
//! author = "Warren Moore"
//! docentry = "Ravl.Images.Video.Video IO.Video4Linux2"

#include "Ravl/Option.hh"
#include "Ravl/DP/Port.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/Image/ByteYUV422Value.hh"
#include "Ravl/DP/SequenceIO.hh"

using namespace RavlN;
using namespace RavlImageN;

template <class PixelT> int process(IntT frames, const StringC &iname, const StringC &oname)
{
  // Open the IO streams
  DPIPortC< ImageC<PixelT> > ip;
  DPOPortC< ImageC<PixelT> > op;
  if (!OpenISequence(ip, iname, "", true))
  {
    cerr << "Failed to open input sequence (" << iname << ")" << endl;
    return 1;
  }
  if (!OpenOSequence(op, oname, "", true))
  {
    cerr << "Failed to open output sequence (" << oname << ")" << endl;
    return 1;
  }

  // Set some attributes
  ip.SetAttr("width",  720);
  ip.SetAttr("height", 576);
  
  // Frame capture loop
  bool seq = (frames > 0);
  ImageC<PixelT> img;
  while (!ip.IsGetEOS())
  {
    // Get the image
    if (!ip.Get(img))
      break;
    
    // Output the image
    op.Put(img);
    
    // Stop grabbing yet?
    if (seq)
    {
      if (frames == 0)
        break;
      frames--;
    }
  }

  return 0;
}

int main(int argc, char **argv)
{
  // Process the options
  OptionC opt(argc, argv);
  bool grey     = opt.Boolean("g",  false,                 "Greyscale capture.");
  bool yuv422   = opt.Boolean("y",  false,                 "YUV 422 capture.");
  IntT frames   = opt.Int(    "f",  0,                     "Number of frames to capture (0 = infinite).");
  StringC iname = opt.String( "",   "@V4L2:/dev/video0#1", "Input name.");
  StringC oname = opt.String( "",   "@X",                  "Output name.");
  opt.Check();
  
  // Greyscale capture
  if (grey)
    return process<ByteT>(frames, iname, oname);
  else
    if (yuv422)
      return process<ByteYUV422ValueC>(frames, iname, oname);
  
  // RGB capture
  return process<ByteRGBValueC>(frames, iname, oname);
}

