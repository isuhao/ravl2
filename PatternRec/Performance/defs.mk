# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/PatternRec/Classify/defs.mk"

DESCRIPTION = Pattern Recognition Performance

PACKAGE = Ravl/PatternRec

HEADERS=Error.hh

SOURCES= Error.cc

PLIB = RavlPatternRec

LIBDEPS = RavlPatternRecPerformance.def

TESTEXES=

USESLIBS=Auto

EHT = 

EXAMPLES=  
