// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICSTATEORITER_HEADER
#define RAVLLOGICSTATEORITER_HEADER 1
////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic

#include "Ravl/Logic/LiteralIter.hh"
#include "Ravl/Logic/And.hh"
#include "Ravl/Logic/State.hh"
#include "Ravl/Stack.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Backtrack point for StateAndIterC.
  // For use in StateAndIterBodyC only!
  
  class StateAndBackTrackPointC {
    public:
    StateAndBackTrackPointC()
      {}
    //: Default constructor.
    
    StateAndBackTrackPointC(BindMarkT &bm,int ntermNo,const LiteralIterC &niter)
      : mark(bm),
      termNo(ntermNo),
      iter(niter)
      {}
    
    BindMarkT mark;
    int termNo;
    LiteralIterC iter;
  };
  
  //! userlevel=Develop
  //: Iterate through possible solutions in a state for a 'or' condition.
  // NB. Solutions may be repeated if two or more terms in the or condtion
  // unify with the same literal..
  
  class StateAndIterBodyC
    : public LiteralIterBodyC 
  {
  public:
    StateAndIterBodyC(const StateC &nstate,const AndC &nand,const BindSetC &bs);
    //: Constructor.
    
    virtual bool Next();
    //: Goto next data element.
    // returns true if next element is valid.
    
    virtual bool First();
    //: Goto first data element.
    // returns true if next element is valid.
    
    virtual bool IsElm() const;
    //: At a valid element ?
    // returns true if iterator is at a valid
    // element.
    
    virtual LiteralC Data();
    //: Get current literal.
    
    virtual BindSetC &Binds();
    //: Access binds associated with solution.
    
    virtual const BindSetC &Binds() const;
    //: Access binds associated with solution.
    
  protected:    
    bool NextValid();
    //: Goto next valid solution.
    // return false if not found.
    
    StateC state;
    AndC lAnd;
    BindSetC binds;
    BindMarkT initalBm;
    StackC<StateAndBackTrackPointC> stack;
    LiteralIterC solIt; // Solutions within the state.
  };

  //! userlevel=Nandmal
  //: Iterate through possible solutions in a state for a 'or' condition.
  // NB. Solutions may be repeated if two or more terms in the or condtion
  // unify with the same literal..
  
  class StateAndIterC
    : public LiteralIterC 
  {
  public:
    StateAndIterC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
    StateAndIterC(const StateC &nstate,const AndC &nand,const BindSetC &bs)
      : LiteralIterC(*new StateAndIterBodyC(nstate,nand,bs))
      {}
    //: 
    
  };
}


#endif


