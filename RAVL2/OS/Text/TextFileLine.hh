// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLTEXTLINE_HEADER
#define RAVLTEXTLINE_HEADER 1
///////////////////////////////////////////////////////
//! file="Ravl/OS/Text/TextFileLine.hh"
//! lib=RavlOS
//! author="Charles Galambos"
//! docentry="Ravl.API.OS.Text Processing"
//! date="05/12/97"
//! rcsid="$Id: TextFileLine.hh 5240 2005-12-06 17:16:50Z plugger $"

#include "Ravl/String.hh"

namespace RavlN {
  
  //! userlevel=Advanced
  //: Class for holding a single line of text.
  
  class TextFileLineC 
  {
  public:
    TextFileLineC();
    // Default constructor.
    
    TextFileLineC(UIntT lno,StringC str) 
      : lineNo(lno),
      text(str)
      {}
    // Default constructor.
    
    TextFileLineC(const TextFileLineC &Oth) 
    : lineNo(Oth.lineNo),
      text(Oth.text)
      {}
    // Copy constructor.
    
    StringC &Text() { return text; }
    // Access text of line.
    
    const StringC &Text() const { return text; }
    // Access text of line.
    
    void SetLineNo(UIntT no) { lineNo = no; }
    // Set the lineno.
    
    UIntT LineNo() const { return lineNo; }
    // Get the lineno.
    
    void Dump(ostream &strm) const;
    // Dump to stdout.
  protected:
    UIntT lineNo;   // Line number in file.
    StringC text; // Text.
  };
}



#endif

