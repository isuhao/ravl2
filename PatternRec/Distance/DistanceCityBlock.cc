// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/Distance/DistanceCityBlock.cc"

#include "Ravl/PatternRec/DistanceCityBlock.hh"

namespace RavlN {

  
  //: Measure the distance from d1 to d2.
  
  RealT DistanceCityBlockBodyC::Measure(const VectorC &d1,const VectorC &d2) const {
    return VectorC(d1 - d2).SumOfAbs();
  }
  
  //: Measure the magnitude of d1.
  
  RealT DistanceCityBlockBodyC::Magnitude(const VectorC &d1) const {
    return d1.SumOfAbs();
  }
  
  //: Calculates Jacobian matrix at X
  
  MatrixC DistanceCityBlockBodyC::Jacobian (const VectorC &X) const {
    MatrixC dSdX (1,X.Size());
    for(int i = 0;i < (int) X.Size();i++)
      dSdX[0][i] = Sign(X[i]);
    return dSdX;
  }
  
}
