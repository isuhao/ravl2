// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DESIGNFUNCTIONSUPERVISED_HEADER
#define RAVL_DESIGNFUNCTIONSUPERVISED_HEADER 1
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! author="Charles Galambos"
//! docentry="Ravl.Pattern Recognition.Functions"
//! file="Ravl/PatternRec/DataSet/DesignFunctionSupervised.hh"

#include "Ravl/PatternRec/Function.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/PatternRec/Designer.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Supervised function designer.
  
  class DesignFunctionSupervisedBodyC
    : public DesignerBodyC
  {
  public:
    DesignFunctionSupervisedBodyC()
    {}
    //: Default constructor.
    
    DesignFunctionSupervisedBodyC(istream &strm);
    //: Load from stream.
    
    DesignFunctionSupervisedBodyC(BinIStreamC &strm);
    //: Load from binary stream.
    
    virtual bool Save (ostream &out) const;
    //: Writes object to stream.
    
    virtual bool Save (BinOStreamC &out) const;
    //: Writes object to binary stream.

    virtual FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out);
    //: Create function from the given data.
    
    virtual FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weight);
    //: Create function from the given data, and sample weights.
    
  };
  
  //! userlevel=Normal
  //: Supervised function designer.
  
  class DesignFunctionSupervisedC
    : public DesignerC
  {
  public:
    DesignFunctionSupervisedC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DesignFunctionSupervisedC(istream &strm);
    //: Load from stream.
    
    DesignFunctionSupervisedC(BinIStreamC &strm);
    //: Load from binary stream.
    
  protected:
    DesignFunctionSupervisedC(DesignFunctionSupervisedBodyC &bod)
      : DesignerC(bod)
    {}
    //: Body constructor.

    DesignFunctionSupervisedC(DesignFunctionSupervisedBodyC *bod)
      : DesignerC(bod)
    {}
    //: Body ptr constructor.
    
    DesignFunctionSupervisedBodyC &Body()
    { return static_cast<DesignFunctionSupervisedBodyC &>(DesignerC::Body()); }
    //: Access body.
    
    const DesignFunctionSupervisedBodyC &Body() const
    { return static_cast<const DesignFunctionSupervisedBodyC &>(DesignerC::Body()); }
    //: Access body.
    
  public:
    FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out)
    { return Body().Apply(in,out); }
    //: Create function from the given data.
    
    FunctionC Apply(const SampleC<VectorC> &in,const SampleC<VectorC> &out,const SampleC<RealT> &weight)
    { return Body().Apply(in,out,weight); }
    //: Create function from the given data, and sample weights.
    
  };
  
  // DesignFunctionSupervisedC
  
  inline istream &operator>>(istream &strm,DesignFunctionSupervisedC &obj) {
    obj = DesignFunctionSupervisedC(strm);
    return strm;
  }
  //: Load from a stream.
  // Uses virtual constructor.
  
  inline ostream &operator<<(ostream &out,const DesignFunctionSupervisedC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.
  
  inline BinIStreamC &operator>>(BinIStreamC &strm,DesignFunctionSupervisedC &obj) {
    obj = DesignFunctionSupervisedC(strm);
    return strm;
  }
  //: Load from a binary stream.
  // Uses virtual constructor.
  
  inline BinOStreamC &operator<<(BinOStreamC &out,const DesignFunctionSupervisedC &obj) {
    obj.Save(out);
    return out;
  }
  //: Save to a stream.
  // Uses virtual constructor.

}


#endif
