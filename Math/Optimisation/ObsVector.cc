// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"

#include "ObsVector.hh"

#define DEFAULT_STEP_SIZE 1.0e-6

namespace RavlN {

  //: Constructor
  ObsVectorBodyC::ObsVectorBodyC(const VectorC &nz, const MatrixRSC &nNi)
  {
    z = nz.Copy();
    Ni = nNi.Copy();

    // create vector of step sizes
    zstep = nz.Copy();
    for ( IntT i=nz.Size()-1; i >= 0; i-- )
      zstep[i] = DEFAULT_STEP_SIZE;
  }

  //: Constructor
  ObsVectorBodyC::ObsVectorBodyC(const VectorC &nz, const MatrixRSC &nNi,
				 const VectorC &nzstep)
  {
    z = nz.Copy();
    Ni = nNi.Copy();

    // copy step sizes
    zstep = nzstep.Copy();
  }

  //: Return residual adjusted for any robust aspects to the observation
  double ObsVectorBodyC::Residual(const VectorC &v, const MatrixRSC &Ni)
  {
    // default is to return the non-robust residual

    // compute N^-1*v
    VectorC Niv = Ni*v;

    // compute and return v^T*N^-1*v
    return Niv.Dot(v);
  }

  //: Adjust information matrix/vector term for any robustness
  bool ObsVectorBodyC::AdjustInformation(MatrixRSC &Aterm, VectorC &aterm)
  {
    // default is to do nothing to the matrix/vector
    return true;
  }

  //: Restore values are an aborted modification
  bool ObsVectorBodyC::Restore()
  {
    // default is to do nothing to the matrix/vector
    return true;
  }

  //: Get observation vector
  const VectorC& ObsVectorBodyC::GetZ() const
  {
    return z;
  }

  //: Get observation inverse covariance
  const MatrixRSC& ObsVectorBodyC::GetNi() const
  {
    return Ni;
  }

  //: Set element of observation vector
  bool ObsVectorBodyC::SetElZ(IntT el, RealT val)
  {
    z[el] = val;
    return true;
  }

  //: Set element of observation inverse covariance
  bool ObsVectorBodyC::SetElNi(IntT row, IntT col, RealT val)
  {
    Ni[row][col] = val;
    return true;
  }

  //: Get step sizes for numerical differentiation
  const VectorC& ObsVectorBodyC::GetZStep() const
  {
    return zstep;
  }
}
