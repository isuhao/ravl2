// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI3D

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Button.hh"
#include "Ravl/GUI/Canvas.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/GUI/Slider.hh"
#include "Ravl/GUI/LBox.hh"
#include "Ravl/GUI/Canvas3D.hh"
#include "Ravl/GUI/DViewPoint3D.hh"
#include "Ravl/GUI/DCube3D.hh"
#include "Ravl/GUI/DTriMesh3D.hh"
#include "Ravl/GUI/DLight3D.hh"
#include "Ravl/GUI/MouseEvent.hh"
#include "Ravl/Option.hh"
#include "Ravl/GUI/Bitmap.hh"
#include "Ravl/Vector3d.hh"
#include "Ravl/3D/TriMesh.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/OS/Date.hh"

#include <gtk/gtk.h>
#include <gdk/gdk.h>

using namespace RavlN;
using namespace RavlGUIN;


bool InitGL()
{
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  return true;
}

bool pressFunc(MouseEventC &me) {
  cerr << "Press " << me.X() << " " << me.Y() << "\n";
  return true;
}

bool releaseFunc(MouseEventC &me) {
  cerr << "Release " << me.X() << " " << me.Y() << "\n";
  return true;
}

bool moveFunc(MouseEventC &me) {
  cerr << "Move " << me.X() << " " << me.Y() << "\n";
  return true;
}

using namespace Ravl3DN;

int main(int nargs,char *args[]) 
{
  Manager.Init(nargs,args);
  
  OptionC opts(nargs,args); // Make sure help option is detected.
  bool doMotion = opts.Boolean("m",false,"Detect motion events.");
  StringC meshFile = opts.String("t","/vol/vssp/motion3d/DispMap/cubehead/detail.tri","Mesh to load ");
  bool useDisplayList = opts.Boolean("dl",false,"Use display lists. ");
  opts.Check();

  DObject3DC object;
  if(!meshFile.IsEmpty()) {
    TriMeshC ts;
    //: Load a mesh from a file.
    if(!Load(meshFile,ts,"",true)) {
      cerr << "Failed to load file. \n";
      return 1;
    }
    object = DTriMesh3DC(ts);
  } else
    object = DCube3DC(Vector3dC(1,1,1),RealRGBValueC(0,1,0));
  
  WindowC win(100,100,"Hello");
  Canvas3DC area(800,800);
  area.SetRenderMode(C3D_SMOOTH);
  Connect(area.Signal("button_press_event"),&pressFunc);
  Connect(area.Signal("button_release_event"),&releaseFunc);
  if(doMotion)
    Connect(area.Signal("motion_notify_event"),&moveFunc);
  
  win.Add(area);
  cerr << "Starting gui. \n";
  win.Show();
  Manager.Execute();
  Sleep(1);
  area.Render(&InitGL); // Set things up.
  area.Light(RealRGBValueC(0.8,0.8,0.8),Point3dC(3,3,10));
  area.ViewPoint(90,Point3dC(0,0,3)); // Setup view point.
  
  if(useDisplayList)
    object.EnableDisplayList();
  
  for(RealT i = 0;i < 1000;i++) {
    // Draw rotated cube
    area.Transform(i * 5,  // Angle.
		   Vector3dC(0,1,0), // Axis of rotation
		   object); // Object to draw.
    area.SwapBuffers();
  }
  cerr << "Execute done, waiting... \n";
  Manager.Wait();
}
