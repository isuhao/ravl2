# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Math/Geometry/Euclidean/Boundary/defs.mk"

PACKAGE=Ravl

HEADERS=CrackCode.hh BVertex.hh Edge.hh Boundary.hh

SOURCES=CrackCode.cc BVertex.cc Edge.cc Boundary.cc ConvexHull.cc

PLIB=RavlMath

TESTEXES= testBoundry.cc

LIBDEPS=RavlMathBoundry.def

USESLIBS=RavlMath

