# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2002, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"

PACKAGE=Ravl/PatternRec

HEADERS=FuncLinearCoeff.hh FuncLinear.hh FuncQuadratic.hh FuncOrthPolynomial.hh \
 DesignFuncLSQ.hh

SOURCES=FuncLinearCoeff.cc FuncLinear.cc FuncQuadratic.cc FuncOrthPolynomial.cc \
 DesignFuncLSQ.cc

PLIB=RavlPatternRec

LIBDEPS=RavlPatternRecModelBasic.def

USESLIBS=RavlPatternRec
