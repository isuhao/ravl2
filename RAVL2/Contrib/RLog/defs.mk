
DONOT_SUPPORT=

REQUIRES=RLog

PACKAGE=Ravl

HEADERS=RLog.hh StdioDateNode.hh

SOURCES=RLog.cc StdioDateNode.cc

PLIB=RavlRLog

USESLIBS=RavlCore RavlOS RLog

CCPPFLAGS += -DRLOG_COMPONENT=Ravl

EXAMPLE= exRLog.cc
