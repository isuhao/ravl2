// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage
//! file="Ravl/Image/Base/Image.cc"

#include "Ravl/Image/Image.hh"

namespace RavlImageN {
  
  //: Override default IO to handle byte images correctly.
  
  ostream &operator<<(ostream &s,const ImageC<ByteT> &img) {
    s << img.Rectangle() << "\n";
    for(BufferAccess2dIterC<ByteT> it(img,img.Range2());it;) {
      do {
	s << (IntT) *it << ' ';
      } while(it.Next());
      s << '\n';
    }
    return s;
  }
  
  //: Load byte image from stream 
  // Override default IO to handle byte images correctly.
  
  istream &operator>>(istream &s,ImageC<ByteT> &img) {
    IndexRange2dC rect;
    s >> rect;
    img = ImageC<ByteT>(rect);
    int x;
    for(BufferAccess2dIterC<ByteT> it(img,img.Range2());it;) {
      s >> x;
      *it = (ByteT) x;
    }
    return s;
  }
}
