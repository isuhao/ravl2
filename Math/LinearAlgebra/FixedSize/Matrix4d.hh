// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLMATRIX4D_HEADER
#define RAVLMATRIX4D_HEADER 1
/////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/Geometry/Euclidean/Matrix4d.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Geometry.4D"

#include "Ravl/FMatrix.hh"

namespace RavlN {
  
  //: 4 by 4 matrix of real values.
  
  class Matrix4dC
    : public FMatrixC<4,4>
  {
  public:
    Matrix4dC()
      {}
    //: Default constructor.
    
    Matrix4dC(const TFMatrixC<RealT,4,4> &base)
      : FMatrixC<4,4>(base)
      {}
    //: Constructor.
    
    Matrix4dC(RealT v00,RealT v01,RealT v02,RealT v03,
	      RealT v10,RealT v11,RealT v12,RealT v13,
	      RealT v20,RealT v21,RealT v22,RealT v23,
	      RealT v30,RealT v31,RealT v32,RealT v33) { 
      data[0][0] = v00;
      data[0][1] = v01;
      data[0][2] = v02;
      data[0][3] = v03;
      data[1][0] = v10;
      data[1][1] = v11;
      data[1][2] = v12;
      data[1][3] = v13;
      data[2][0] = v20;
      data[2][1] = v21;
      data[2][2] = v22;
      data[2][3] = v23;
      data[3][0] = v30;
      data[3][1] = v31;
      data[3][2] = v32;
      data[3][3] = v33;
    }
    //: Constructor.
    
    inline RealT Det() const;
    // Returns the determinant of the matrix.

  protected:
    static inline 
    RealT AdjointDet(RealT b00, RealT b01, RealT b02,
                     RealT b10, RealT b11, RealT b12,
                     RealT b20, RealT b21, RealT b22);
    // Computes the determinant of the matrix 3x3 created from b[ij] 
    // elements.
    
  };
  
  inline 
  RealT Matrix4dC::AdjointDet(RealT b00, RealT b01, RealT b02,
			       RealT b10, RealT b11, RealT b12,
			       RealT b20, RealT b21, RealT b22) {
    return    b00 * (b11*b22 - b12*b21)
      + b10 * (b21*b02 - b22*b01)
      + b20 * (b01*b12 - b02*b11);
  }


  inline 
  RealT
  Matrix4dC::Det() const {
    return 
      data[0][0] * AdjointDet(data[1][1], data[1][2], data[1][3],
			      data[2][1], data[2][2], data[2][3],
			      data[3][1], data[3][2], data[3][3])
      - data[0][1] * AdjointDet(data[1][0], data[1][2], data[1][3],
				data[2][0], data[2][2], data[2][3],
				data[3][0], data[3][2], data[3][3])
      + data[0][2] * AdjointDet(data[1][0], data[1][1], data[1][3],
				data[2][0], data[2][1], data[2][3],
				data[3][0], data[3][1], data[3][3])
      - data[0][3] * AdjointDet(data[1][0], data[1][1], data[1][2],
				data[2][0], data[2][1], data[2][2],
				data[3][0], data[3][1], data[3][2]);
  }
  
}

#endif
