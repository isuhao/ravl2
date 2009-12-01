//! rcsid="$Id$"
//! lib=RavlAAM
//! file="Ravl/CompVision/ActiveAppearanceModels/aamLocaliseFace.hh"
//! docentry="Ravl.API.Images.AAM"
//! userlevel="Normal"
//! author="Jean-Yves Guillemaut"

#include "Ravl/Image/AAMActiveAppearanceModel.hh"
#include "Ravl/Image/AAMAppearanceModel.hh"

#include "Ravl/Option.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/IO.hh"
#include "Ravl/DP/SequenceIO.hh"

using namespace RavlN;
using namespace RavlImageN;

int main (int argc, char** argv)
{
  OptionC opts(argc,argv);
  StringC vidIn = opts.String("i","@V4L2:/dev/video0#1", "Video source.");
  StringC aamFile = opts.String("aam","aam.abs","Active appearence model. ");
  bool displayFace = opts.Boolean("df",true,"Display fitted face ");
  opts.Check();
  
  DPIPortC<ImageC<ByteT> > imgStream;

  if(!OpenISequence(imgStream,vidIn)) {
    std::cerr << "Failed to open video stream. '" << vidIn.chars() << "' \n";
    return 1;
  }
  
  AAMActiveAppearanceModelC aam;
  
  if(!RavlN::Load(aamFile,aam)) {
    std::cerr << "Failed to load active appearence model '" << aamFile << "' ";
    return 1;
  }
  
  VectorC faceParam(aam.Dimensions());
  faceParam.Fill(0);
  
  AAMAppearanceModelC am = aam.AppearanceModel();
  for(UIntT i = 0;i < am.FixedMean().Size();i++)
    faceParam[i] = am.FixedMean()[i];

  VectorC defaultParam = faceParam.Copy();

  ImageC<ByteT> img;
  
  while(1) {
    if(!imgStream.Get(img))
      break;
    RealT residual;
    am.MakePlausible(faceParam);
    faceParam = aam.RefinePose(img,faceParam,residual);
    std::cerr << "Residual=" << residual << "\n";
    if(residual > 0.5)
      faceParam = defaultParam.Copy();
    
    if(displayFace) {
      ImageC<ByteT> rendImg = img.Copy();
      IndexRange2dC rng = rendImg.Frame();
      AAMAppearanceC appear = am.Synthesize(faceParam,1.0);
      rng.ClipBy(appear.Image().Frame());
      for(Array2dIter2C<ByteT,ByteT> it(rendImg,appear.Image(),rng);it;it++) {
        if(it.Data2() != 0)
          it.Data1() = it.Data2();
      }
      
      RavlN::Save("@X:Overlay",rendImg);
    }
    //RavlN::Save("@X:Input",img);
    
  }
  
  return 0;
}