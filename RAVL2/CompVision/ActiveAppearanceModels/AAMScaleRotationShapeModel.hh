// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2005, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_SCALEROTATIONSHAPEMODEL_HEADER
#define RAVLIMAGE_SCALEROTATIONSHAPEMODEL_HEADER 1
//! docentry="Ravl.API.Images.AAM"
//! rcsid="$Id: AAMScaleRotationShapeModel.hh 7358 2009-11-04 11:46:22Z omn-crida $"
//! lib=RavlAAM
//! author="Charles Galambos"
//! file="Ravl/CompVision/ActiveAppearanceModels/AAMScaleRotationShapeModel.hh"
//! example = "aamBuildShapeModel.cc;aamViewShapeModel.cc"

#include "Ravl/Image/AAMShapeModel.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Shape model with scale and rotation normalisation.

  class AAMScaleRotationShapeModelBodyC
    : public AAMShapeModelBodyC
  {
  public:
    AAMScaleRotationShapeModelBodyC();
    //: Default constructor.

    AAMScaleRotationShapeModelBodyC(BinIStreamC &is);
    //: Load from bin stream.

    AAMScaleRotationShapeModelBodyC(istream &is);
    //: Load from stream.

    virtual bool Save(BinOStreamC &out) const;
    //: Save to binary stream 'out'.

    virtual bool Save(ostream &out) const;
    //: Save to stream 'out'.

    virtual bool ComputeMean(SampleStreamC<AAMAppearanceC> &sample);
    //: Compute mean control points for the list of appearance provided.

    virtual bool RawParameters(const AAMAppearanceC &inst,VectorC &fixedParams,VectorC &freeParams) const;
    //: Generate raw parameters.
    //!param: inst        - input appearance for which we would like to compute the parameters.
    //!param: fixedParams - output pose parameters (e.g. pose, scale, orientation).
    //!param: freeParams  - output normalised control point coordinates. This vector consists of the concatenation of the X and Y coordinates of all control points in a normalised frame.
    //  The raw parameters are the parameters representing the shape before applying PCA. They consists of the pose parameters, which describe the pose of the model instance in the image, and the shape parameters, which describe its shape.

    virtual void RawProject(const VectorC &fixedParams,const VectorC &freeParams,SArray1dC<Point2dC> &out) const;
    //: Generate control points defining an appearance from the raw parameters.
    //!param: fixedParams - input pose parameters (e.g. pose, scale, orientation).
    //!param: freeParams  - input normalised control point coordinates. This vector consists of the concatenation of the X and Y coordinates of all control points in a normalised frame.
    //!param: out         - ouput control points

    virtual IntT NoFixedParameters() const;
    //: Return number of parameters describing the pose
    //  These parameters include e.g. the position, scale and orientation of the model instance

  protected:

  };

  //! userlevel=Normal
  //: Shape model with scale and rotation normalisation.

  class AAMScaleRotationShapeModelC
    : public AAMShapeModelC
  {
  public:
    AAMScaleRotationShapeModelC()
    {}
    //: Default constructor.

    AAMScaleRotationShapeModelC(bool)
      : AAMShapeModelC(*new AAMScaleRotationShapeModelBodyC())
    {}
    //: Constructor

    AAMScaleRotationShapeModelC(BinIStreamC &is);
    //: Binary stream constructor.

    AAMScaleRotationShapeModelC(istream &is);
    //: Stream constructor.

  protected:
    AAMScaleRotationShapeModelC(AAMShapeModelBodyC &bod)
      : AAMShapeModelC(bod)
    {}
    //: Body constructor.

    AAMScaleRotationShapeModelC(AAMScaleRotationShapeModelBodyC *bod)
      : AAMShapeModelC(bod)
    {}
    //: Body ptr constructor.

    AAMScaleRotationShapeModelBodyC &Body()
    { return static_cast<AAMScaleRotationShapeModelBodyC &>(AAMShapeModelC::Body()); }
    //: Access body.

    const AAMScaleRotationShapeModelBodyC &Body() const
    { return static_cast<const AAMScaleRotationShapeModelBodyC &>(AAMShapeModelC::Body()); }
    //: Access body.

  public:
  };

  inline
  BinOStreamC &operator<<(BinOStreamC &s,const AAMScaleRotationShapeModelC &ap) {
    ap.Save(s);
    return s;
  }
  //: Save shape model with scale and rotation normalisation to binary stream.

  inline
  BinIStreamC &operator>>(BinIStreamC &s,AAMScaleRotationShapeModelC &ap) {
    ap = AAMScaleRotationShapeModelC(s);
    return s;
  }
  //: Read shape model with scale and rotation normalisation from binary stream.

}

#endif
