// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2008, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here

#include "Ravl/FuncStream.hh"
#include <cstring>

namespace RavlN {
  
  void FuncOStreamBufC::Flush() {
    //std::cerr << "Overflow called. \n";
    RavlAssert(pptr() >= pbase());
    SizeT len = pptr() - pbase();
    if(len > 0) {
      const char *buff = pbase();
      m_write.Call(buff,len);
      // Reset buffer.
      setp(m_buffer,&m_buffer[m_bufferSize-1]);
    }
  }
  

  FuncOStreamBufC::int_type FuncOStreamBufC::overflow(FuncOStreamBufC::int_type c) {
    if(c != EOF) {
      *pptr() = c;
      pbump(1);
    }
    Flush();
    return 0;
  }
  
  //: Sync stream.
  
  int FuncOStreamBufC::sync() {
    Flush();
    return 0;
  }
  
  
  // ---------------------------------------------
  
  //: Constructor.
  
  FuncIStreamBufC::FuncIStreamBufC(const CallFunc2C<char *,SizeT,SizeT> &readCall) 
    : m_read(readCall)
  { setg(m_buffer+4,m_buffer+4,m_buffer+4); }
    
  //: Underflow.
  
  FuncIStreamBufC::int_type FuncIStreamBufC::underflow() {
    if(gptr() < egptr())
      return traits_type::to_int_type(*gptr());
    int nPutback;
    nPutback = gptr() - eback();
    if(nPutback > 4)
      nPutback = 4;
    memmove(m_buffer+(4-nPutback),gptr() - nPutback,nPutback); // removed std:: for gcc 4.3
    char *buf = m_buffer+4;
    SizeT rnum = m_bufferSize-4;
    SizeT num = m_read.Call(buf,rnum);
    RavlAssert(num <= rnum);
    if(num == 0)
      return EOF;
    setg(m_buffer+(4-nPutback),m_buffer+4,m_buffer+4+num);
    return traits_type::to_int_type(*gptr());
  }
}