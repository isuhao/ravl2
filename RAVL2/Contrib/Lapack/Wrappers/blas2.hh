// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2007, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
// $Id: blas2.hh 7674 2010-03-29 16:05:54Z alexkostin $
#ifndef BLAS2_H
#define BLAS2_H

#include "Ravl/MatrixRUT.hh"
#include "Ravl/Vector.hh"

namespace BlasN
{
  //! add outer product to Matrix
  void AddOuterProduct(RavlN::MatrixRUTC &M, const RavlN::VectorC &V, double alpha);

} //end of namespace

#endif
