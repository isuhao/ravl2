// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! author="Charles Galambos"
//! rcsid="$Id: DataConv.cc 3073 2003-06-13 07:18:32Z craftit $"
//! lib=RavlIO
//! file="Ravl/Core/IO/DataConv.cc"

#include "Ravl/DP/DataConv.hh"
#include "Ravl/DP/TypeConverter.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Test if conversion is possible.
  
  bool DPCanConvert(const type_info &from,const type_info &to) 
  { return SystemTypeConverter().CanConvert(from,to); }
  
  //! userlevel=Normal
  //: Do conversion through abstract handles.
  
  RCAbstractC DPDoConversion(const RCAbstractC &dat,const type_info &from,const type_info &to) {
    return SystemTypeConverter().DoConversion(dat,from,to);
  }
  
  
}
