// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_PTHREADSMUTEX_HEADER
#define RAVL_PTHREADSMUTEX_HEADER 1
//////////////////////////////////////////////////////////////
//! author="Charles Galambos"
//! docentry="Ravl.OS.Threads"
//! file="Ravl/OS/Threads/Posix/Mutex.hh"
//! lib=RavlThreads
//! rcsid="$Id$"
//! userlevel=Normal
//! date="02/07/1999"

#include "Ravl/config.h"

#if RAVL_OS_SOLARIS
#include <sys/signal.h>
#endif
#if !RAVL_OS_OSF
#include <signal.h>
#endif

#include <pthread.h>
#include <errno.h>
#include "Ravl/Types.hh"
#include "Ravl/Assert.hh"

#define RAVL_USE_INLINEMUTEXCALLS 0
// Enable/Disable the inlining of mutex calls.

namespace RavlN
{
  //! userlevel=Normal
  //: Mutual Exclusion lock.
  // SMALL OBJECT
  
  class MutexC {
  public:
    MutexC(bool recursive = false);
    //: Constructor.
    // Recursive mutex's allow the same thread to recusively enter the locked region, however it
    // is slower than an normal lock.
    // If this type of mutex is unavailable an ExceptionOperationFailedC will be thrown.
    // Currently recursive mutex's are known to be available under Linux, Solaris and IRIX.
    
    ~MutexC(void);
    //: Destructor.
    
#if RAVL_USE_INLINEMUTEXCALLS
    inline bool Lock(void) {
      int rc;
      if((rc = pthread_mutex_lock(&mutex)) == 0)
	return true;
      Error("Lock failed",errno,rc);
      return false;
    }
    //: Lock mutex.
    
    inline bool TryLock(void) {
      int rc;
      if((rc = pthread_mutex_trylock(&mutex)) == 0)
	return true;
      if(errno != EPERM && errno != EBUSY && errno != EINTR && 
	 rc != EBUSY && errno != EAGAIN && rc !=  EDEADLK)
	Error("Trylock failed for unexpected reason.",errno,rc);
      return false;
    }
    //: Try and lock mutex.
    
    inline bool Unlock(void) {
      RavlAssertMsg(!TryLock(),"MutexC::Unlock() called on an unlocked mutex.");
      int rc;
      if((rc = pthread_mutex_unlock(&mutex)) == 0)
	return true;
      Error("Unlock failed.",errno,rc);
      return false;
    }
    //: Unlock mutex.
#else
    bool Lock(void);
    //: Lock mutex.
    
    bool TryLock(void);
    //: Try and lock mutex.
    
    bool Unlock(void);
    //: Unlock mutex.
#endif    
  protected:
    pthread_mutex_t mutex;
    
    void Error(const char *msg);  
    //: Report an error.
    
    void Error(const char *msg,int anerrno,int rc);  
    //: Report an error, with an error number.
    
  private:
    MutexC &operator=(const MutexC &) { 
      RavlAssert(0); 
      return *this;
    }
    //: Make sure there's no assignment.
    
    MutexC(const MutexC &)
    { RavlAssert(0); }
    //: Make sure there's no attempt to use the copy constructor.
  };
  
  //! userlevel=Normal
  //: Exception safe MutexC locking class.
  // SMALL OBJECT <p>
  // The destructor of this object removed the lock if
  // it is held.   This ensures whenever the lock goes
  // out of scope, either by returning from the function
  // or if an exception is held, that the lock will be
  // released properly. <p>  
  // It is the users responsability
  // to ensure that the MutexC remains valid for the 
  // lifetime of any MutexLockC instance. 
  
  class MutexLockC {
  public:
    MutexLockC(MutexC &m)
    : mutex(m),
      locked(true)
    { mutex.Lock(); }
    //: Create a lock on a mutex.
    
    MutexLockC(const MutexC &m)
      : mutex(const_cast<MutexC &>(m)),
	locked(true)
    { mutex.Lock(); }
    //: Create a lock on a mutex.
    // This may not seem like a good idea,
    // but it allows otherwise constant functions to
    // lock out other accesses to data without undue
    // faffing.
    
    MutexLockC(const MutexC &m,bool tryLock)
      : mutex(const_cast<MutexC &>(m)),
	locked(false)
    { 
      if(tryLock)
	locked = mutex.TryLock(); 
      else {
	mutex.Lock();
	locked = true;
      }
    }
    //: Try and create a lock on a mutex.
    // This may not seem like a good idea,
    // but it allows otherwise constant functions to
    // lock out other accesses to data without undue
    // faffing.
    
    ~MutexLockC() { 
      if(locked)
	mutex.Unlock(); 
    }
    //: Create a lock on a mutex.
    
    void Unlock() {
      RavlAssert(locked);
      mutex.Unlock();
      locked = false;
    }
    //: Unlock the mutex.
    
    void Lock() {
      RavlAssert(!locked);
      mutex.Lock();
      locked = true;
    }
    //: re Lock the mutex.
    
    bool IsLocked() const
    { return locked; }
    //: Is it locked ?
    
    MutexC &Mutex()
    { return mutex; }
    //: Access mutex we're locking.
    
  protected:
    MutexC &mutex;
    bool locked;
    
  private:
    MutexLockC(const MutexLockC &x)
      : mutex(x.mutex)
    { RavlAssert(0); }
    //: Dissable copy constructor.
    
    MutexLockC &operator=(const MutexLockC &) { 
      RavlAssert(0); 
      return *this;
    }
    //: Make sure there's no assignment.
  };
  
}


#endif
