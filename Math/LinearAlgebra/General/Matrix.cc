// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlMath

#include "Ravl/StdMath.hh"
#include "Ravl/Matrix.hh"

// General matrix functions.

namespace RavlN {

  //: Test if matrix only contains real values.
  // This will return false if either nan's (Not an number) 
  // or infinite values are found.
  
  bool MatrixC::IsReal() const {
    for(BufferAccess2dIterC<RealT> it(*this,Size2());it;it++)
      if(IsInf(*it) || IsNan(*it))
	return false;
    return true;
  }

}
