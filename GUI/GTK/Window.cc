// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI
//! file="Ravl/GUI/GTK/Window.cc"

#include "Ravl/GUI/Window.hh"
#include "Ravl/GUI/Manager.hh"
#include "Ravl/CallMethods.hh"
#include <gtk/gtk.h>

#define DODEBUG 0

#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x) 
#endif

namespace RavlGUIN {
  
  static int rootWinCount = 0;
  /* when invoked (via signal delete_event), terminates the application.
   */

  //: Constructor.
  
  WindowBodyC::WindowBodyC(int nsx,int nsy,const char *ntitle,GtkWindowType nWinType,int nboarder,bool nrootWin)
    : sx(nsx), sy(nsy),
      boarder(nboarder),
      title(ntitle),
      rootWin(nrootWin),
      closeDown(false),
      cursorChange(false),
      winType(nWinType)
  {
    if(rootWin)
      Manager.GetRootWindow() = WindowC(*this);
  }
  
  //: Destructor.
  
  WindowBodyC::~WindowBodyC() {
    ONDEBUG(cerr << "WindowBodyC::~WindowBodyC() Started." << ((void *) this) << " \n");
    Destroy();
    ONDEBUG(cerr << "WindowBodyC::~WindowBodyC() Done. " << ((void *) this) << " \n");
  }
  
  //: Create the widget.
  
  bool WindowBodyC::Create() {
    ONDEBUG(cerr << "WindowBodyC::Create(), Title=" << title << " Root=" << rootWin << " Type=" << ((int) winType) << " Boarder=" << boarder << "\n");
    if(widget == 0) {
      widget = gtk_window_new (winType);  
      if(rootWin && winType == GTK_WINDOW_TOPLEVEL) {
	rootWinCount++;
      }
      ConnectRef(Signal("delete_event"),*this,&WindowBodyC::Close);
      
    if(title != 0)
      gtk_window_set_title (GTK_WINDOW (widget),title.chars());
    if(boarder != 0)
      gtk_container_set_border_width( GTK_CONTAINER (widget), boarder );    
    }
    if(child.IsValid()) {
      if(child.Create()) {
	gtk_container_add (GTK_CONTAINER (widget), child.Widget());
	gtk_widget_show(child.Widget());
      }
    }
    ConnectSignals();
    return true;
  }
  
  void WindowBodyC::Destroy() {
    if(cursor.IsValid()) 
      cursor.Invalidate();
    
    OneChildBodyC::Destroy();
#if 0
    // Pre-empt destructor...
    // This ensures a expected behavour even
    // if there are still handles to the window
    // somewhere in the program.
    if(!rootWin) {
      if(widget != 0) {
	gtk_widget_hide (widget);
	gtk_widget_destroy(widget);
	widget = 0;
      }
      if(widgetId != 0)
	Manager.Deregister(*this); 
    }
#endif
  }
  
  //: Close window.
  // Thread safe.
  
  bool WindowBodyC::Close() {
    ONDEBUG(cerr << "WindowBodyC::Close() called" << endl);
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUICloseDown));
    ONDEBUG(cerr << "WindowBodyC::Close() done" << endl);
    return true;
  }
  
  //: Set cursor.
  
  void WindowBodyC::SetCursor(CursorC &cur) {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUIUpdateCursor,cur));
  }
  
  //: Update cursor.


  bool WindowBodyC::GUIUpdateCursor(CursorC &newCursor) {
    if(widget == 0 && newCursor.IsValid())
      newCursor.SetWindow(widget->window);
    cursor = newCursor;
    return true;
  }

  //: Set the title of the window.

  bool WindowBodyC::GUISetTitle(StringC &str) {
    title = str.Copy();
    if(widget != 0)
      gtk_window_set_title (GTK_WINDOW (widget),title.chars());
    return true;
  }

  //: Set the title of the window.
  
  void WindowBodyC::SetTitle(const StringC &str) {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUISetTitle,str));
  }
  
  //: Set the title of the window.

  //: Close down window.
  
  bool WindowBodyC::GUICloseDown() {
    ONDEBUG(cerr << "WindowBodyC::GuiCloseDown() called" << endl);
    if(closeDown)
      return true;
    closeDown = true;
    if(rootWin) {
      if (--rootWinCount == 0) {
	ONDEBUG(cerr << "WindowBodyC::GuiCloseDown() calling Manager.Quit()" << endl);
	Manager.Quit(); 
	return true;
      }
    }
    Hide();
    Destroy();
    ONDEBUG(cerr << "WindowBodyC::GuiCloseDown() done" << endl);
    return true;
  }
  
  void WindowBodyC::SetPositioning(GtkWindowPosition& pos) {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUISetPositioning,pos));
  }
  
  bool WindowBodyC::GUISetPositioning(GtkWindowPosition& pos) {
    if (widget!=0)
      gtk_window_set_position(GTK_WINDOW(widget),pos);
    return true;
  }
  
  void WindowBodyC::Raise() {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUIRaise));
  }
  
  bool WindowBodyC::GUIRaise() {
    if (widget!=0)
      gdk_window_raise(widget->window);
    return true;
  }
  
  void WindowBodyC::Lower() {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUILower));
  }
  
  bool WindowBodyC::GUILower() {
    if (widget!=0)
      gdk_window_lower(widget->window);
    return true;
  }

  void WindowBodyC::SetModal(bool& modal) {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::GUISetModal,modal));
  }
  
  bool WindowBodyC::GUISetModal(bool& modal) {
    if (widget!=0)
      gtk_window_set_modal(GTK_WINDOW(widget),modal);
    return true;
  }

  void WindowBodyC::MakeTransient(WindowC& parent) {
    Manager.Queue(Trigger(WindowC(*this),&WindowC::MakeTransient,parent));
  }
  
  bool WindowBodyC::GUIMakeTransient(WindowC& parent) {
    if (widget!=0 && parent.Widget()!=0)
      gtk_window_set_transient_for(GTK_WINDOW(widget),GTK_WINDOW(parent.Widget()));
    return true;
  }
   
  //////////////////////////////////////////////
  //: Constructor.
  
  WindowC::WindowC(int sx,int sy,const char *ntitle,GtkWindowType nWinType,int nboarder,bool nrootWin)
    : OneChildC(*new WindowBodyC(sx,sy,ntitle,nWinType,nboarder,nrootWin))
  {}
}

