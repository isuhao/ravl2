// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MATRIXC_HEADER
#define RAVL_MATRIXC_HEADER 1
///////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Math/LinearAlgebra/General/Matrix.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Charles Galambos"
//! date="24/01/2001"
//! docentry="Ravl.Math.Linear Algebra"

#include "Ravl/TMatrix.hh"
#include "Ravl/FMatrix.hh"

namespace RavlN {
  
  class VectorC;
  class VectorMatrixC;
  
  //! userlevel=Normal
  //: Matrix of real values.
  
  class MatrixC
    : public TMatrixC<RealT>
  {
  public:
    MatrixC()
    {}
    //: Default constructor.

    bool IsReal() const;
    //: Test if matrix only contains real values.
    // This will return false if either nan's (Not an number) 
    // or infinite values are found.

    MatrixC(const VectorC &vec)
      : TMatrixC<RealT>((const TVectorC<RealT> &)vec)
    {}
    //: Treat vector as columb matrix.
    
    MatrixC(UIntT rows,UIntT cols)
      : TMatrixC<RealT>(rows,cols)
    {}
    //: Construct a new matrix of rows x cols.
    
    MatrixC(UIntT rows,UIntT cols,const RealT *data)
      : TMatrixC<RealT>(rows,cols,data)
    {}
    //: Construct a new matrix of rows x cols with row wise array of data.
    
    MatrixC(const TMatrixC<RealT> &oth)
      : TMatrixC<RealT>(oth)
    {}
    //: Base class constructor.
    
    MatrixC(const SArray2dC<RealT> &oth)
      : TMatrixC<RealT>(oth)
    {}
    //: Base class constructor.
    
    MatrixC(RealT v1,RealT v2,
	    RealT v3,RealT v4)
      : TMatrixC<RealT>(v1,v2,v3,v4)
    {}
    //: Construct a 2 x 2 matrix from given values.
    
    MatrixC(RealT v1,RealT v2,RealT v3,
	    RealT v4,RealT v5,RealT v6,
	    RealT v7,RealT v8,RealT v9)
      : TMatrixC<RealT>(v1,v2,v3,v4,v5,v6,v7,v8,v9)
    {}
    //: Construct a 3 x 3 matrix from given values.
    
    template<unsigned int N,unsigned int M>
    MatrixC(const FMatrixC<N,M> &fmat)
      : TMatrixC<RealT>(N,M)
    {
      for(int i = 0;i < N;i++)
	for(int j = 0;j < M;j++)
	  (*this)[i][j] = fmat[i][j];
    }
    //: Construct from a fixed size matrix.
    
    MatrixC Inverse() const;
    //: Calculate the inverse of this matrix.
    // an invalid matrix is returned if this matrix is
    // singular. 
    
    bool InverseIP();
    //: Calculate the inverse of this matrix in place.
    // Returns false if matrix is singular. <p>
    // Notes:
    // The matrix must be square <p>
    // If the matrix is not stored in a continous area of memory a slightly
    // different routine is used to do the inversion.  
    
    MatrixC PseudoInverse(RealT thresh = 1e-5) const;
    //: Do a pseudo inverse 
    // Uses singular value decomposition to decompose the matrix, and sets
    // the singular values smaller than 'thesh' to zero.

    RealT Det() const;
    //: Calculate the determinant of the matrix.
  };
  
  
  bool SolveIP(MatrixC &A,VectorC &b);
  //: Solve a general linear system  A*x = b
  // The input vector is b, which is replaced by the ouput x. <p>
  // This matrix is altered to L-U factored form by the computation. <p>
  // If the input matrix is singular, false is returned and
  // true if the operation succeeded.
  
  VectorC Solve(const MatrixC &A,const VectorC &b);
  //: Solve a general linear system  A*x = b
  // Where X is the returned vector.
  // If matrix is singular a zero length vector is returned.
  
  VectorC SVD(const MatrixC &M);
  //: Singular value decomposition, eg. M = U * D * V.T(). 
  // The diagonal matrix D is returned as a vector. Values for the
  // other matrixes are not computed.
  // If the operation failes the returned vector is invalid.
  
  VectorC SVD_IP(MatrixC &M);
  //: Singular value decomposition, eg. M = U * D * V.T(). 
  // The diagonal matrix D is returned as a vector. Values for the
  // other matrixes are not computed.
  // If the operation failes the returned vector is invalid. <p>
  // NB. This function destory's the contents of this matrix!
  
  VectorC SVD(const MatrixC &M,MatrixC & u, MatrixC & v);
  //: Singular value decomposition, eg. M = U * D * V.T(). 
  // The diagonal matrix D is returned as a vector.
  // This also returns the matrix u and v matrixes, the passed
  // matrixes will be used to store the results if they are
  // of the correct size.
  // If the operation failes the returned vector is invalid.
  
  VectorC SVD_IP(MatrixC &M,MatrixC & u, MatrixC & v);
  //: Singular value decomposition, eg. M = U * D * V.T(). 
  // The diagonal matrix D is returned as a vector.
  // This also returns the matrix u and v matrixes, the passed
  // matrixes will be used to store the results if they are
  // of the correct size.
  // If the operation failes the returned vector is invalid.
  // NB. This function destory's the contents of this matrix!
  
  VectorC EigenValues(const MatrixC &M);
  //: Calculate the eigen values of this matrix, for real symmetric matrices
  // This matrix remains unchanged. A vector of the eigen
  // values is returned. <p>
  // If any errors occured a zero length vector is generated.
  
  VectorC EigenValuesIP(MatrixC &M);
  //: Calculate the eigen values of this matrix, for real symmetric matrices
  // The contents of this matrix is destroyed. A vector of the eigen
  // values is returned.   <p>
  // If any errors occured a zero length vector is generated.
  
  VectorC EigenVectors(const MatrixC &M,MatrixC &E);
  //: Calculate the eigen values and vectors of this matrix, for real symmetric matrices
  // A = E*D*E~ where D is the diagonal matrix of eigenvalues
  //   D[i,j] = ret[i] if i=j and 0 otherwise. 'ret' is the
  // returned vector.
  
  VectorMatrixC EigenVectors(const MatrixC &A);
  //: Calculate the eigen values and vectors of this matrix, for real symmetric matrices
  // A = E*D*E~ where D is the diagonal matrix of eigenvalues
  // D[i,j] = ret[i] if i=j and 0 otherwise. 'ret' is the
  // returned vector and E is the returned matrix.
  
  VectorC EigenVectorsIP(MatrixC &A);
  //: Calculate the eigen values and vectors of this matrix, for real symmetric matrices
  // This matrix is filed with the eigen vectors
  // A = E*D*E~ where D is the diagonal matrix of eigenvalues
  //   D[i,j] = ret[i] if i=j and 0 otherwise. 'ret' is the
  // returned vector.
  
  RealT MaxEigenValue(const MatrixC &A,VectorC &maxv);
  //: Get the maximum eigen value and its vector, for real symmetric matrices
  
  MatrixC RandomMatrix(int n,int m,RealT scale = 1);
  //: Create a random matrix of values between -scale and scale with the given size.
  
  MatrixC RandomSymmetricMatrix(int n,RealT scale = 1);
  //: Create a random symmetric matrix of values between -scale and scale with the given size.
  
  MatrixC RandomPositiveDefiniteMatrix(int n);
  //: Create a random positive definite matrix.
  // The matrix is also symmetric in the current implementation, this may be changed at some point.
  
}

#endif
