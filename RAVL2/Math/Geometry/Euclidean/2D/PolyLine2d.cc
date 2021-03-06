// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: PolyLine2d.cc 5420 2006-03-20 16:00:37Z craftit $"
//! lib=RavlMath

#include "Ravl/PolyLine2d.hh"
#include "Ravl/LinePP2d.hh"

namespace RavlN {

   bool PolyLine2dC::IsSelfIntersecting() const {
     DLIterC<Point2dC> ft(*this);
     if(!ft) return false;
     while(1) {
       LinePP2dC l1(ft.Data(), ft.NextData());
       ft++;
       DLIterC<Point2dC> it2 = ft;
       if (!it2) break;
       for (; it2; it2++) {
         LinePP2dC l2(it2.Data(), it2.NextData());
         if (l1.HasInnerIntersection(l2))
           return true;
       }
     }
     return false;
   }

  //: Measure the length of the poly line in euclidean space.
  
  RealT PolyLine2dC::Length() const {
    DLIterC<Point2dC> ft(*this);
    if(!ft) return 0.0;
    Point2dC last = *ft;
    RealT len = 0;
    for(ft++;ft;ft++) {
      len += last.EuclidDistance(*ft);
      last = *ft;
    }
    return len;
  }

}
