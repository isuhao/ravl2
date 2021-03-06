// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_PARAMETERS_HH
#define RAVL_PARAMETERS_HH
////////////////////////////////////////////////////////////////////////////
//! author="Robert Crida"
//! lib=Optimisation
//! date="10/2/1998"
//! userlevel=Normal
//! example=testCost.cc
//! file="Ravl/PatternRec/Optimise/Parameters.hh"
//! docentry="Ravl.API.Pattern Recognition.Optimisation.Cost Functions"
//! rcsid="$Id: Parameters.hh 6651 2008-03-05 14:16:39Z craftit $"

#include "Ravl/RefCounter.hh"
#include "Ravl/Vector.hh"
#include "Ravl/Matrix.hh"

namespace RavlN {

  // --------------------------------------------------------------------------
  // **********  ParametersBodyC  *********************************************
  // --------------------------------------------------------------------------
  //: Implementation class for optimisation parameter bounds.
  //
  // This is the implemtation class for optimisation parameter bounds. The
  // ParametersC handle class should be used.
  
  class ParametersBodyC
    : public RCBodyC
  {
  public:
    ParametersBodyC (const VectorC &minP, 
		     const VectorC &maxP, 
		     const SArray1dC<IntT> &steps);
    //: Constructor
    //!param: minP  - lower bound on function input
    //!param: maxP  - upper bound on function input
    //!param: steps - number of steps to use with each parameter (if applicable)
    // All parameters are enabled in optimisation.
    
    ParametersBodyC (const VectorC &minP, 
		     const VectorC &maxP, 
		     const SArray1dC<IntT> &steps,
		     const SArray1dC<IntT> &mask);
    //: Constructor
    //!param: minP  - lower bound on function input
    //!param: maxP  - upper bound on function input
    //!param: steps - number of steps to use with each parameter (if applicable)
    //!param: mask  - specifies which elements of P to use in X
    // Only the parameters with a mask value of 1 are presented to the optimiser.
    
    ParametersBodyC (SizeT nparams);
    //: Constructor.
    // This setsup nparams with defaults settings of :
    // minP=0 maxP=1 Steps=1 mask=0 (constP = 0)
    
    ParametersBodyC (const ParametersBodyC &other);
    //: Copy Constructor.
    
    ParametersBodyC (istream &in);
    //: Constructs for a stream
    
    ParametersBodyC & Copy () const;
    //: Makes a deep copy
    
    VectorC Random();
    //: Generate a random positon in the parameter space.
    
  protected:
    inline SizeT Size() const
    { return _minP.Size(); }
    //: Get number of parameters in set.
    
    void SetMask (const SArray1dC<IntT> &mask);
    //: Changes the parameter mask
    
    void SetConstP (const VectorC &constP);
    //: Specifies the values to use for constant parameters
    
    const VectorC &MinX () const {
      if(m_cacheDirty) UpdateCache();
      return m_minX;
    }
    //: Lower parameter bound for optimisation
    
    const VectorC &MaxX () const {
      if(m_cacheDirty) UpdateCache();
      return m_maxX; 
    }
    //: Upper parameter bound for optimisation
    
    const SArray1dC<IntT> &Steps () const {
      if(m_cacheDirty) UpdateCache();      
      return m_stepsP;
    }
    //: Number of steps in each parameter for optimisation
    
    const MatrixC &TransP2X () const {
      if(m_cacheDirty) UpdateCache();
      return m_transP2X;      
    }
    //: Transformation between P and X
    
    const MatrixC &TransX2P () const {
      if(m_cacheDirty) UpdateCache();
      return m_transX2P;
    }
    //: Transformation between X and P
    
    const VectorC &ConstP () const {
      if(m_cacheDirty) UpdateCache();
      return m_constP;
    }
    //: Vector with constant P elements set, else 0
    
    const VectorC &StartX () const {
      if(m_cacheDirty) UpdateCache();
      return m_startX;
    }
    //: Returns initial parameter value which is TransP2X * constP
    
    void Setup(IndexC p,RealT min,RealT max,IntT steps,IntT mask = 1);
    //: Setup paramiter p.
    
    void Setup(IndexC p,RealT min,RealT max,IntT steps,RealT constV,IntT mask = 1);
    //: Setup paramiter p, and constant value.
    
    void Save (ostream &out) const;
    //: Saves to stream, from which can be constructed
    
    friend class ParametersC;
    //: Handle class
    
  private:
    VectorC _minP;
    VectorC _maxP;
    VectorC _constP;
    SArray1dC<IntT> _steps;
    SArray1dC<IntT> _mask;

    void UpdateCache() const;
    
    mutable bool m_cacheDirty;
    mutable VectorC m_minX;
    mutable VectorC m_maxX;
    mutable MatrixC m_transP2X;
    mutable MatrixC m_transX2P;
    mutable VectorC m_constP;
    mutable VectorC m_startX;
    mutable SArray1dC<IntT> m_stepsP;
  };
  
  //////////////////////////////////////////
  
  // --------------------------------------------------------------------------
  // **********  ParametersC  *************************************************
  // --------------------------------------------------------------------------
  //: Handle class for optimisation parameter bounds.
  //
  // Handle class for parameter bounds class. Used to specify constraints for
  // the optimiser on starting conditions, parameter boundaries and resolution
  // for each parameter. Also used to fix certain parameters as constants during
  // optimisation. this is achieved as follows: A mask is used to disable some
  // parameters which will then be treated by the cost function as constants
  // and become invisible to the optimiser.<p>
  //
  // Note that there is a distinction made here between the vector X which is
  // input to the cost function and optimised and the input parameters to the
  // function P. X is a subset of P.
  
  class ParametersC : public RCHandleC<ParametersBodyC>
  {
  public:
    inline ParametersC ()
    {}
    //: Default constructor
    
    ParametersC (const VectorC &minP, 
		 const VectorC &maxP, 
		 const SArray1dC<IntT> &steps)
      : RCHandleC<ParametersBodyC>(*new ParametersBodyC (minP,maxP,steps))
    {}
    //: Constructor
    //!param: minP  - lower bound on function input
    //!param: maxP  - upper bound on function input
    //!param: steps - number of steps to use with each parameter (if applicable)
    // All parameters are enabled in optimisation.
    
    ParametersC (const VectorC &minP, 
		 const VectorC &maxP, 
		 const SArray1dC<IntT> &steps,
		 const SArray1dC<IntT> &mask)
      : RCHandleC<ParametersBodyC>(*new ParametersBodyC (minP,maxP,steps,mask))
    {}
    //: Constructor
    //!param: minP  - lower bound on function input
    //!param: maxP  - upper bound on function input
    //!param: steps - number of steps to use with each parameter (if applicable)
    //!param: mask  - specifies which elements of P to use in X
    // Only the parameters with a mask value of 1 are presented to the optimiser.
    
    ParametersC (SizeT nparams)
      : RCHandleC<ParametersBodyC>(*new ParametersBodyC (nparams))
    {}
    //: Constructor.
    // This setsup nparams with defaults settings of :
    // minP=0 maxP=1 Steps=1 mask=0 (constP = 0)
    
    ParametersC (istream &in)
      : RCHandleC<ParametersBodyC>(*new ParametersBodyC (in))
    {}
    //: Constructs from stream
    
    inline SizeT Size() const
    { return Body().Size(); }
    //: Get number of paramtiers in set.
    
    inline void SetMask (const SArray1dC<IntT> &mask)
    { Body().SetMask (mask); }
    //: Sets which parameters are enabled
    
    inline void SetConstP (const VectorC &constP)
    { Body().SetConstP (constP); }
    //: Sets const parameter values and starting point for enabled ones
    
    inline const VectorC &MinX () const
    { return Body().MinX (); }
    //: Lower bound on optimisation parameters
    
    inline const VectorC &MaxX () const
    { return Body().MaxX (); }
    //: Upper bound on optimisation parameters
    
    inline const SArray1dC<IntT> &Steps () const
    { return Body().Steps (); }
    //: Number of steps to use for each dimension
    
    inline const MatrixC &TransP2X () const
    { return Body().TransP2X (); }
    //: Matrix for converting P to X
    
    inline const MatrixC &TransX2P () const
    { return Body().TransX2P (); }
    //: Matrix for converting X to P.
    // Note that const P elements will be 0 and must add the vector ConstP
    // below for proper estimate of P.
    
    inline const VectorC &ConstP () const
    { return Body().ConstP(); }
    //: Vector containing constant P elements and 0s
    
    inline const VectorC &StartX () const
    { return Body().StartX (); }
    //: Starting vector for X which is subset of value specified in SetConstP.
    
    inline void Setup(IndexC p,RealT min,RealT max,IntT steps,IntT mask = 1)
    { Body().Setup(p,min,max,steps,mask); }
    //: Setup paramiter p.
    
    inline void Setup(IndexC p,RealT min,RealT max,IntT steps,RealT constV,IntT mask = 1)
    { Body().Setup(p,min,max,steps,constV,mask); }
    //: Setup paramiter p, and constant value.
    
    inline void Save (ostream &out) const
    { Body().Save (out); }
    //: Writes object to stream, cna be loaded using constructor
    
    inline VectorC Random()
    { return Body().Random(); }
    //: Generate a random positon in the parameter space.
  };
  
}

#endif
