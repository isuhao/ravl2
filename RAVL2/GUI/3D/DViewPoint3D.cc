// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////
//! rcsid="$Id: DViewPoint3D.cc 6374 2007-10-02 15:09:14Z alexkostin $"
//! lib=RavlGUI3D
//! file="Ravl/GUI/3D/DViewPoint3D.cc"

#include "Ravl/GUI/DViewPoint3D.hh"
#include "Ravl/GUI/Canvas3D.hh"
#include <GL/gl.h>
#include <GL/glu.h>

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {

  //: Render object.
  bool DViewPoint3DBodyC::GUIRender(Canvas3DC &canvas) const
  {
    //cerr << "DViewPoint3DBodyC::Render(), Called. \n";
    // Setup GL stuff.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    RealT dAspect = 1;//canvas.Size()[0]/canvas.Size()[1];
    ONDEBUG(cerr << "gluPerspective(), FOV=" << fov <<" Aspect:" << dAspect << " Near=" << m_dNear << " Far=" << m_dFar << "\n");
    gluPerspective(fov, dAspect, m_dNear, m_dFar);
    gluLookAt(eye.X(),    eye.Y(),    eye.Z(),
              centre.X(), centre.Y(), centre.Z(),
              up.X(),     up.Y(),     up.Z());

    //glDepthRange(1,5);

    //we dont need to touch model matrix here
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    //glTranslatef(0,0,-15);

    return true;
  }

}
