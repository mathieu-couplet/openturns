// SWIG file ResourceMap.i

%{
#include "openturns/ResourceMap.hxx"
%}

%include ResourceMap_doc.i

%template(StringStringMap) std::map<OT::String, OT::String>;

%nodefaultctor ResourceMap;

%include openturns/ResourceMap.hxx

namespace OT {

%extend ResourceMap {

UnsignedInteger __len__() const
{
  return OT::ResourceMap::GetSize();
}

} // ResourceMap

} // OT
