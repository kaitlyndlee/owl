// ======================================================================== //
// Copyright 2019 Ingo Wald                                                 //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include "Group.h"
#include "Context.h"

namespace owl {

  void Group::buildAccel()
  {
    lloGroupAccelBuild(context->llo,this->ID);
  }

  void GeomGroup::setChild(int childID, Geom::SP child)
  {
    assert(childID >= 0);
    assert(childID < geometries.size());
    geometries[childID] = child;
    lloGeomGroupSetChild(context->llo,this->ID,childID,child->ID);
  }

  GeomGroup::GeomGroup(Context *const context,
                       size_t numChildren)
    : Group(context,context->groups),
      geometries(numChildren)
  {}
  
  InstanceGroup::InstanceGroup(Context *const context,
                               size_t numChildren)
    : Group(context,context->groups),
      children(numChildren)
  {}
  
  TrianglesGroup::TrianglesGroup(Context *const context,
                                 size_t numChildren)
    : GeomGroup(context,numChildren)
  {
    lloTrianglesGeomGroupCreate(context->llo,this->ID,
                                nullptr,numChildren);
  }
  
} // ::owl