// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlGUI

#include "Ravl/GUI/Notebook.hh"
#include "Ravl/GUI/PackInfo.hh"
#include "Ravl/GUI/Label.hh"
#include "Ravl/GUI/Manager.hh"
#include <gtk/gtk.h>
#include <iostream.h>

namespace RavlGUIN {

  //: Create the widget.
  
  bool NotebookBodyC::Create() {
    if(widget != 0)
      return true;
    
    widget = gtk_notebook_new();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (widget),tabpos);  
    if(!showtabs)
      gtk_notebook_set_show_tabs(GTK_NOTEBOOK (widget), showtabs);
    if(!showborder)
      gtk_notebook_set_show_border(GTK_NOTEBOOK (widget), showborder);
    
    gtk_widget_show(widget);
    for(DLIterC<WidgetC> it(children);it;it++) {
      WidgetC tab;    
      // Check we have a tab widget.
      if(tabWidges.IsElm(*it))
	tab = tabWidges[*it];
      if(!tab.IsValid()) {
	tab = LabelC("Tmp...");
	tabWidges[*it] = tab;
      }
      GUIAppendPage(*it,tab);
    }
    ConnectSignals();
    return true;
  }
  
  
  //: Remove page number 'pageNo'
  // GUI Thread only.
  
  bool NotebookBodyC::GUIRemovePage(IntT &pageNo) {
    if(widget == 0) {
      cerr << "NotebookBodyC::GUIRemovePage(), ERROR: Called before widget initalised. \n";
      return true;
    }
    gtk_notebook_remove_page(GTK_NOTEBOOK (widget),pageNo);
    return true;
  }
  
  
  //: Remove page number 'pageNo'
  
  void NotebookBodyC::RemovePage(IntT &pageNo) {
    Manager.Queue(Trigger(NotebookC(*this),&NotebookC::GUIRemovePage,pageNo));
  }
  
  
  //: Remove page number 'pageNo'
  // GUI Thread only.
  
  bool NotebookBodyC::GUIRemovePageW(WidgetC &page) {
    if(widget == 0) {
      cerr << "NotebookBodyC::GUIRemovePage(), ERROR: Called before widget initalised. \n";
      return true;
    }
    int pageNo = gtk_notebook_page_num(GTK_NOTEBOOK (widget),page.Widget());
    if(pageNo < 0) {
      cerr << "NotebookBodyC::GUIRemovePage(), ERROR: Asked to remove unknown page. \n";
      return true;
    }
    gtk_notebook_remove_page(GTK_NOTEBOOK (widget),pageNo);
    return true;
  }
  
  //: Remove page number 'pageNo'
  
  void NotebookBodyC::RemovePage(WidgetC &pageNo) {
    Manager.Queue(Trigger(NotebookC(*this),&NotebookC::GUIRemovePageW,pageNo));  
  }
  
  //: Append a new page.
  
  bool NotebookBodyC::GUIAppendPage(WidgetC &page,WidgetC &tab) {
    if(widget == 0) {
      Add(page);
      tabWidges[page] = tab;
      return true;
    }
    // Create child page.
    if(page.Widget() == 0)
      if(!page.Create())
	return true;
    page.Show();
    // Create tab widget.
    if(tab.Widget() == 0)
      if(!tab.Create())
	return true;
    tab.Show();
    // Add page.
    gtk_notebook_append_page(GTK_NOTEBOOK (widget),page.Widget(),tab.Widget());
    return false;
  }
  
  //: Append a new page.
  
  void NotebookBodyC::AppendPage(WidgetC &page,WidgetC &tab) {
    Manager.Queue(Trigger(NotebookC(*this),&NotebookC::GUIAppendPage,page,tab));
  }
  
  //: Show a page from the notebook.
  // GUI Thread only.
  
  bool NotebookBodyC::GUIShowPage(WidgetC &page) {
    if(widget == 0) {
      cerr << "NotebookBodyC::GUIShowPage(), ERROR: Called before widget initalised. \n";
      return true;
    }
    if(page.Widget() == 0) {
      WidgetC tab;    
      // Check we have a tab widget.
      if(tabWidges.IsElm(page))
	tab = tabWidges[page];
      if(!tab.IsValid()) {
	tab = LabelC("Tmp...");
	tabWidges[page] = tab;
      }
      GUIAppendPage(page,tab);
    }  
    int pageNo = gtk_notebook_page_num(GTK_NOTEBOOK (widget),page.Widget());
    if(pageNo < 0) {
      cerr << "NotebookBodyC::GUIShowPage(), Failed to find page for widget. \n";
      return true;
    }
    gtk_notebook_set_page(GTK_NOTEBOOK (widget),pageNo);
    return true;
  }
  
  //: Show a page from the notebook.
  
  void NotebookBodyC::ShowPage(WidgetC &page) {
    Manager.Queue(Trigger(NotebookC(*this),&NotebookC::GUIShowPage,page));
  }
  
  
  
  ///////////////////////////////////////////
  
  //: Default constructor
  
  NotebookC::NotebookC()
    : ContainerWidgetC(*new NotebookBodyC())
  {}
}
