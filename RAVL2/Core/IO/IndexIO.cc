// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
// $Id: IndexIO.cc 737 2002-01-31 14:55:49Z craftit $
//! rcsid="$Id: IndexIO.cc 737 2002-01-31 14:55:49Z craftit $"
//! lib=RavlIO
//! file="Ravl/Core/IO/IndexIO.cc"

#include "Ravl/DP/CoreIO.hh"

#include "Ravl/Index2d.hh"
#include "Ravl/Index3d.hh"
#include "Ravl/DP/FileFormatStream.hh" 
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/SArray1d.hh"


namespace RavlN {
  void InitFixedIndexIO()
  {}
  
  static TypeNameC type1(typeid(Index2dC),"Index2dC");
  static TypeNameC type2(typeid(Index3dC),"Index3dC");
  
  static TypeNameC type4(typeid(SArray1dC<Index2dC>),"SArray1dC<Index2dC>");
  static TypeNameC type5(typeid(SArray1dC<Index3dC>),"SArray1dC<Index3dC>");
  
  FileFormatStreamC<Index2dC> FileFormatStream_Index2d;
  FileFormatStreamC<Index3dC> FileFormatStream_Index3d;
  
  FileFormatBinStreamC<Index2dC> FileFormatBinStream_Index2d;
  FileFormatBinStreamC<Index3dC> FileFormatBinStream_Index3d;
  
  // Add some IO for arrays of Indexes.

  FileFormatStreamC<SArray1dC<Index2dC> > FileFormatStream_SArray1dC_Index2d;
  FileFormatStreamC<SArray1dC<Index3dC> > FileFormatStream_SArray1dC_Index3d;
  
  FileFormatBinStreamC<SArray1dC<Index2dC> > FileFormatBinStream_SArray1dC_Index2d;
  FileFormatBinStreamC<SArray1dC<Index3dC> > FileFormatBinStream_SArray1dC_Index3d;

}
