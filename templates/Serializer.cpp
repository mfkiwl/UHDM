/*
 Do not modify, auto-generated by model_gen.tcl

 Copyright 2019 Alain Dargelas

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

/*
 * File:   Serializer.cpp
 * Author:
 *
 * Created on October 4, 2021, 10:53 PM
 */
#include <uhdm/Serializer.h>
#include <uhdm/VpiListener.h>
#include <uhdm/vpi_visitor.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <uhdm/uhdm.h>

#if defined(_MSC_VER)
  #pragma warning(push)
  #pragma warning(disable : 4267)  // 'var' : conversion from 'size_t' to 'type', possible loss of data
#endif

namespace UHDM {

class MarkKeepers final : public VpiListener {
 public:
  MarkKeepers(Serializer* serializer) : serializer_(serializer){}
  void enterAny(const any* object, vpiHandle handle) override {
    serializer_->MarkKeeper(object);
    serializer_->MarkKeeper(object->VpiParent()); // Need to be removed after fixing out-of-tree back pointers
  }
 private:
  
  Serializer* serializer_ = nullptr;
};

template <typename T, typename>
void Serializer::GC_(FactoryT<T>* const factory) {
  bool change = true;
  while (change) {
    change = false;
    for (auto p = factory->objects_.begin();
         p != factory->objects_.end(); ++p) {
      if (keepers_.find((*p)) == keepers_.end()) {
        delete (*p);
        factory->objects_.erase(p);
        change = true;
        break;
      }
    }
  }
}

void Serializer::GarbageCollect() {
  // Only keep objects that belong to a design
  // Mark the objects
  MarkKeepers* marker = new MarkKeepers(this);
  std::vector<vpiHandle> designs;
  for (auto p : designMaker.objects_) {
    designs.push_back(
        reinterpret_cast<vpiHandle>(new uhdm_handle(uhdmdesign, p)));
  }
  marker->listenDesigns(designs);

  // Mark the transitive cone including the object parents and their children to cover
  // relations that still point to out-of-tree objects
  std::set<const any*> topset;
  topset = keepers_;
  // This is very inneficient implementation.
  // This step can be removed when we can remove the out-of-tree back pointer dependance in MarkKeepers
  for (auto p : topset) {
    if (p) {
      vpiHandle h = reinterpret_cast<vpiHandle>(new uhdm_handle(p->UhdmType(), p));
      marker->listenAny(h);
      delete h;
    }
  }
  delete marker;

  // Delete the ones that are not required
<FACTORY_GC>

  // Clear keeper
  keepers_.clear();
}

void DefaultErrorHandler(ErrorType errType, const std::string& errorMsg, const any* object1, const any* object2) {
  std::cerr << errorMsg << std::endl;
}

void Serializer::SetId(const BaseClass* p, uint32_t id) {
  allIds_.emplace(p, id);
}

uint32_t Serializer::GetId(const BaseClass* p) {
  auto inserted = allIds_.emplace(p, incrId_);
  if (inserted.second) {
    ++incrId_;
  }
  return inserted.first->second;
}

<UHDM_NAME_MAP>

// From uhdm_types.h
std::string VpiTypeName(vpiHandle h) {
  uhdm_handle* handle = (uhdm_handle*) h;
  BaseClass* obj = (BaseClass*) handle->object;
  return UhdmName(obj->UhdmType());
}

static constexpr uint32_t badIndex = static_cast<uint32_t>(-1);

BaseClass* Serializer::GetObject(uint32_t objectType, uint32_t index) {
  if (index == badIndex)
    return nullptr;

  switch (objectType) {
<FACTORY_OBJECT_TYPE_MAP>
  default: return nullptr;
  }
}

std::map<std::string, uint32_t, std::less<>> Serializer::ObjectStats() const {
  std::map<std::string, uint32_t, std::less<>> stats;
<FACTORY_STATS>
  return stats;
}

void Serializer::PrintStats(std::ostream& strm,
                            std::string_view infoText) const {
  strm << "=== UHDM Object Stats Begin (" << infoText << ") ===" << std::endl;
  auto stats = ObjectStats();
  std::vector<std::string_view> names;
  names.reserve(stats.size());
  std::transform(stats.begin(), stats.end(), std::back_inserter(names),
                 [](decltype(stats)::value_type const& pair) {
                   return std::string_view(pair.first);
                 });
  std::sort(names.begin(), names.end());
  for (std::string_view name : names) {
    auto it = stats.find(name);
    if (it->second > 0) {
      // The longest model name is
      // "enum_struct_union_packed_array_typespec_group"
      strm << std::setw(48) << std::left << name << std::setw(8) << std::right
           << it->second << std::endl;
    }
  }
  strm << "=== UHDM Object Stats End ===" << std::endl;
}

Serializer::~Serializer() {
  Purge();
}

void Serializer::Purge() {
  allIds_.clear();
  anyVectMaker.Purge();
  symbolMaker.Purge();
  uhdm_handleMaker.Purge();
<FACTORY_PURGE>
}
}  // namespace UHDM

#if defined(_MSC_VER)
  #pragma warning(pop)
#endif
