// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DYNAMICLINK_HEADER
#define RAVL_DYNAMICLINK_HEADER 1
//! rcsid="$Id: DynamicLink.hh 5240 2005-12-06 17:16:50Z plugger $"
//! lib=RavlOSIO
//! userlevel=Normal
//! docentry="Ravl.API.OS.Dynamic Linking"
//! author="Charles Galambos"
//! example=exDynamicLink.cc
//! date="04/07/2000"
//! file="Ravl/OS/IO/DynamicLink.hh"

#include "Ravl/String.hh"

namespace RavlN {

  bool DynamicLinkLoadDepends(const char *nm);
  //: Load library dependancy file.
  // Returns true on success
  
  bool DynamicLinkLoad(const StringC &libName);
  //: Load a library.
  // Returns true on success.
}


#endif
