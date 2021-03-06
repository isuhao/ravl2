// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_BGRAVALUE_HEADER
#define RAVLIMAGE_BGRAVALUE_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id: BGRAValue.hh 6970 2008-09-23 17:04:52Z ees1wc $"
//! author="Charles Galambos"
//! docentry="Ravl.API.Images.Pixel Types.RGB"
//! userlevel=Normal
//! lib=RavlImage
//! file="Ravl/Image/Base/BGRAValue.hh"

#include "Ravl/Image/RGBValue.hh"

namespace RavlImageN {
  
  using namespace RavlN;
#if RAVL_VISUALCPP_NAMESPACE_BUG
  using RavlN::BinIStreamC;
  using RavlN::BinOStreamC;
  using RavlN::TFVectorC;
#endif


  //: BGRA Pixel.
  
  template<class CompT>
  class BGRAValueC
    : public TFVectorC<CompT,4>
  {
  public:
    
    // Constructors, copies, assigment, setting, and destructor
    // --------------------------------------------------------
    
    inline BGRAValueC(CompT r = 0,
		      CompT g = 0,
		      CompT b = 0, 
		      CompT a = 0) {
      this->data[2] = r;
      this->data[1] = g;
      this->data[0] = b;
      this->data[3] = a;
    }
    //: Constructs a colour from four colour components. 
    // Note: the arguments are given in the order r,g,b,a.
    
    BGRAValueC(const RGBValueC<CompT> & rgb,const CompT &a = 0) {
      this->data[2] = rgb.Red();
      this->data[1] = rgb.Green();
      this->data[0] = rgb.Blue();
      this->data[3] = a;      
    }
    // Creates the colour from the triple RGB colour 'rgb' and the fourth
    // colour component 'x'.
    
    inline
    RGBValueC<CompT> RGB() const
    { return RGBValueC<CompT>(Red(),Green(),Blue()); }
    //: Get a RGB pixel value.
    
    inline const CompT & Red() const
    { return this->data[2]; }
    // Returns the level of the red component.
    
    inline const CompT & Green() const
    { return this->data[1]; }
    // Returns the level of the green component.
    
    inline const CompT & Blue() const
    { return this->data[0]; }
    // Returns the level of the blue component.
    
    inline const CompT & X() const
    { return this->data[3]; }
    // Returns the level of the fourth colour component.
    
    inline CompT & Red()
    { return this->data[2]; }
    // Access to the red component.
    
    inline CompT & Green()
    { return this->data[1]; }
    // Access to the green component.
    
    inline CompT & Blue()
    { return this->data[0]; }
    // Access to the blue component.
  
    inline CompT & A()
    { return this->data[3]; }
    // Access to the fourth colour component.    
  };
  
}
#endif
