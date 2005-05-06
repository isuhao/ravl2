# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2004, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#! rcsid="$Id$"
#! file="Ravl/Applications/VGrab/defs.mk"
DESCRIPTION = VGrab - Video Frame Grabber
DONOT_SUPPORT=arm
MAINS = VGrab.cc

PROGLIBS=CSPDriver  RavlVideoIO RavlImage RavlOSIO RavlDV.opt RavlImgIOV4L.opt RavlExtImgIO.opt RavlImageIO RavlMPEG2.opt RavlURLIO.opt

#PROGLIBS = RavlCore RavlOS RavlVideoIO RavlImage RavlOSIO \
#RavlDV.opt RavlImgIOV4L.opt RavlExtImgIO.opt \
#RavlDPDisplay \
# RavlImageIO RavlMPEG2.opt CSPDriver.opt \
#RavlURLIO.opt
#EHT = Ravl.Applications.VGrab.html 
#USESLIBS = 
