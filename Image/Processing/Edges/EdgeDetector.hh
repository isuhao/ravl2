// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_EDGEDETECTOR_HEADER
#define RAVLIMAGE_EDGEDETECTOR_HEADER 1
//! author="Charles Galambos"
//! userlevel=Normal
//! rcsid="$Id$"
//! lib=RavlImageProc

#include "Ravl/Image/EdgeDeriche.hh"
#include "Ravl/Image/EdgeSobel.hh"
#include "Ravl/Image/EdgeNonMaxSuppression.hh"
#include "Ravl/Image/SqrComposition.hh"
#include "Ravl/Image/EdgeLink.hh"
#include "Ravl/Image/EdgeSobel.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Edge detector body
  // This class wraps up all the components you need to go from grey scale image
  // to a list of Edgels or pixel locations.
  
  class EdgeDetectorBodyC 
    : public RCBodyC
  {
  public:
    EdgeDetectorBodyC(bool useDeriche,RealT minHyst,RealT maxHyst);
    //: Constructor.
    
    bool Apply(const ImageC<RealT> &img,SArray1dC<EdgelC> &edges);
    //: Apply the edge detector to 'img', returning a list of edgels.
    
    SArray1dC<EdgelC> PApply(const ImageC<RealT> &img) {
      SArray1dC<EdgelC> ret;
      Apply(img,ret);
      return ret;
    }
    //: Apply the edge detector to 'img', returning a list of edgels.
    
  protected:
    RealT minHyst,maxHyst;
    
    EdgeDericheC edgeDet;
    EdgeNonMaxSuppressionC nonMaxSup;
    SqrCompositionC sqrCompose;
    
    bool eightConnect; // Use eight connectivity ?
  };
  
  //! userlevel=Develop
  //: Edge detector.
  // This class wraps up all the components you need to go from grey scale image
  // to a list of Edgels or pixel locations.
  
  class EdgeDetectorC 
    : public RCHandleC<EdgeDetectorBodyC>
  {
  public:
    EdgeDetectorC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    EdgeDetectorC(bool useDeriche,RealT minHyst= 15,RealT maxHyst = 20)
      : RCHandleC<EdgeDetectorBodyC>(*new EdgeDetectorBodyC(useDeriche,minHyst,maxHyst))
    {}
    //: Constructor.
    
  protected:
    
  public:
    bool Apply(const ImageC<RealT> &img,SArray1dC<EdgelC> &edges)
    { return Body().Apply(img,edges); }
    //: Apply the edge detector to 'img', returning a list of edgels.
    
    SArray1dC<EdgelC> PApply(const ImageC<RealT> &img) 
    { return Body().PApply(img); }
    //: Apply the edge detector to 'img', returning a list of edgels.
    
  };
  
}

#endif
