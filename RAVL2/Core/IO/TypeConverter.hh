// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TYPECONVERTER_HEADER
#define RAVL_TYPECONVERTER_HEADER 1
/////////////////////////////////////////////////////////////
//! docentry="Ravl.API.Core.IO.Formats" 
//! author="Charles Galambos"
//! rcsid="$Id: TypeConverter.hh 7297 2009-10-09 09:49:31Z craftit $"
//! lib=RavlIO
//! file="Ravl/Core/IO/TypeConverter.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/DP/Converter.hh"
#include "Ravl/Graph.hh"
#include "Ravl/DList.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Type converter body.
  // This class provides a mechanism for handle conversions between
  // two types.  Its main use is converting data held in an abstract
  // handle into a type which a particular piece of code can handle. <p>
  // It holds the set of available conversions as a graph, and searches
  // for the least cost path between two nodes (c++ types) in the graph. <p>
  // The cost function attempts to minimise the sum of the data data losses,
  // the costs a represented as ratio of bits of information given to those
  // sent out.  e.g. The cost of converting a (32 bit) int into a char is 4
  // 32/8.   Strictly speaking the losses should be multiplied, but this gives
  // no preference to shorter conversion paths, so I've chosen to simply add them.
  // If someone comes up with a single example where this crude approximation
  // causes problems I'll put together a more sophisticated scheme, until then
  // it will do.
  
  class TypeConverterBodyC 
    : public RCBodyVC
  {
  public:
    TypeConverterBodyC();
    //: Constructor.
    
    DListC<DPConverterBaseC> FindConversion(const type_info &from,const type_info &to,RealT &finalCost);
    //: Find a conversion.
    // If found the cost of conversion is put into finalCost.
    
    DListC<DPConverterBaseC> FindConversion(const type_info &from,const type_info &to);
    //: Find a conversion.
    
    bool CanConvert(const type_info &from,const type_info &to);
    //: Test if conversion is possible.
    
    RCAbstractC DoConversion(const RCAbstractC &dat,const type_info &from,const type_info &to);
    //: Do conversion through abstract handles.
    
    bool Insert(DPConverterBaseC &tc);
    //: Insert new conversion.
    
    bool Remove(DPConverterBaseC &tc);
    //: Remove old conversion.
    
    GraphC<StringC,DPConverterBaseC> &Graph()
    { return convGraph; }
    //: Access converstion graph.
    
  protected:
    static RealT EdgeEval(const DPConverterBaseC &edge);
    
    GraphC<StringC,DPConverterBaseC> &ConvGraph()
    { return convGraph; }
    //: Access conversion graph.
    
    HashC<StringC,GraphNodeHC<StringC,DPConverterBaseC> > &NodeTab()
    { return nodeTab; }
    //: Type -> Node mapping.
    
    GraphNodeHC<StringC,DPConverterBaseC> GetTypeNode(const type_info &inf);
    //: Get the graph node associated with a type_info.
    
    GraphC<StringC,DPConverterBaseC> convGraph; // Converstion graph.
    HashC<StringC,GraphNodeHC<StringC,DPConverterBaseC> > nodeTab; // Type to node mapping.
  };


  //! userlevel=Advanced
  //: Type converter.
  // This class provides a mechanism for handle conversions between
  // two types.  Its main use is converting data held in an abstract
  // handle into a type which a particular piece of code can handle. <p>
  // It holds the set of available conversions as a graph, and searches
  // for the least cost path between two nodes (c++ types) in the graph. <p>
  // The cost function attempts to minimise the sum of the data data losses,
  // the costs a represented as ratio of bits of information given to those
  // sent out.  e.g. The cost of converting a (32 bit) int into a char is 4
  // 32/8.   Strictly speaking the losses should be multiplied, but this gives
  // no preference to shorter conversion paths, so I've chosen to simply add them.
  // If someone comes up with a single example where this crude approximation
  // causes problems I'll put together a more sophisticated scheme, until then
  // it will do.
  
  class TypeConverterC
    : public RCHandleC<TypeConverterBodyC>
  {
  public:
    TypeConverterC()
    {}
    //: Default constructor.

    TypeConverterC(bool)
      : RCHandleC<TypeConverterBodyC>(*new TypeConverterBodyC())
    {}
    //: Constructor.
    
  public:
    DListC<DPConverterBaseC> FindConversion(const type_info &from,const type_info &to,RealT &finalCost)
    { return Body().FindConversion(from,to,finalCost); }
    //: Find a conversion.
    // If found the cost of conversion is put into finalCost.
    
    DListC<DPConverterBaseC> FindConversion(const type_info &from,const type_info &to)
    { return Body().FindConversion(from,to); }
    //: Find a conversion.
    
    bool CanConvert(const type_info &from,const type_info &to)
    { return Body().CanConvert(from,to); }
    //: Test if conversion is possible.
    
    RCAbstractC DoConversion(const RCAbstractC &dat,const type_info &from,const type_info &to)
    { return Body().DoConversion(dat,from,to); }
    //: Do conversion through abstract handles.
    
    bool Insert(DPConverterBaseC &tc)
    { return Body().Insert(tc); }
    //: Insert new conversion.
    
    bool Remove(DPConverterBaseC &tc)
    { return Body().Remove(tc); }
    //: Remove old conversion.
    
    template<class InT,class OutT>
    bool TypeConvert(const InT &inraw,OutT &outraw) {
      RCAbstractC result = DoConversion(RCWrapC<InT>(inraw).Abstract(),typeid(InT),
					typeid(OutT));
      RCWrapC<OutT> out(result,true);
      if(!out.IsValid())
	return false; // Did conversion succeed ?
      outraw = out.Data();
      return true;
    }
    //: Do a conversion.
    // This is really only for testing, if you know exactly what the
    // types of the objects are you can convert directly.
    
    template<class OutT>
    bool TypeConvert(const RCWrapAbstractC &in,OutT &outraw) {
      RCAbstractC result = DoConversion(const_cast<RCWrapAbstractC &>(in).Abstract(),in.DataType(),
					typeid(OutT));
      RCWrapC<OutT> out(result,true);
      if(!out.IsValid())
	return false; // Did conversion succeed ?
      outraw = out.Data();
      return true;
    }
    //: Do a conversion from an object held in an abstract handle.
    
    GraphC<StringC,DPConverterBaseC> &Graph()
    { return Body().Graph(); }
    //: Access converstion graph.
  };
  
  TypeConverterC &SystemTypeConverter();
  //: Default type converter used by the system.
  
}


#endif
