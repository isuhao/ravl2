// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! docentry="Ravl.Math.Geometry.2D"
//! author="Charles Galambos"
//! date="24/01/2001"
//! rcsid="$Id: VectorMatrix2d.cc 3553 2003-10-14 17:20:04Z jonstarck $"
//! lib=RavlMath
//! file="Ravl/Math/LinearAlgebra/FixedSize/VectorMatrix2d.cc"

#include "Ravl/VectorMatrix2d.hh"

namespace RavlN {
#if !(RAVL_COMPILER_VISUALCPP && !RAVL_COMPILER_VISUALCPPNET)
  template class FVectorMatrixC<2>;
#endif
}
