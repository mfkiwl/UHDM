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
 * File:   Serializer_save.cpp
 * Author:
 *
 * Created on December 14, 2019, 10:03 PM
 */
#include <uhdm/Serializer.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#if defined(_MSC_VER)
  #include <io.h>
  #define S_IRWXU (_S_IREAD | _S_IWRITE)
  #pragma warning(push)
  #pragma warning(disable : 4267)  // 'var' : conversion from 'size_t' to 'type', possible loss of data
#else
  #include <unistd.h>
  #if !(defined(__MINGW32__) || defined(__CYGWIN__))
    #define O_BINARY 0
  #endif
#endif

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <capnp/message.h>
#include <capnp/serialize-packed.h>

#include "UHDM.capnp.h"
#include <uhdm/containers.h>
#include <uhdm/uhdm.h>
#include <uhdm/uhdm_types.h>


namespace UHDM {
template <typename T, typename>
void Serializer::SetSaveId_(FactoryT<T> *const factory) {
  unsigned long index = 0;
  for (auto obj : factory->objects_) {
    SetId(obj, ++index);
  }
}

template<typename U>
struct Serializer::AnySaveAdapter<BaseClass, U> {
  void operator()(const BaseClass *const obj, Serializer *serializer, U builder) const {
    builder.setVpiParent(serializer->GetId(obj->VpiParent()));
    builder.setUhdmParentType(obj->UhdmParentType());
    builder.setVpiFile(obj->GetSerializer()->symbolMaker.Make(obj->VpiFile().string()));
    builder.setVpiLineNo(obj->VpiLineNo());
    builder.setVpiColumnNo(obj->VpiColumnNo());
    builder.setVpiEndLineNo(obj->VpiEndLineNo());
    builder.setVpiEndColumnNo(obj->VpiEndColumnNo());
    builder.setUhdmId(obj->UhdmId());
  }
};

<CAPNP_SAVE_ADAPTERS>

template<typename T, typename U>
struct Serializer::VectorOfanySaveAdapter<T, U> {
  void operator()(const std::vector<T*> &objects, Serializer *serializer, typename ::capnp::List<U>::Builder builder) const {
    unsigned long index = 0;
    for (const T* obj : objects)
      AnySaveAdapter<T, typename U::Builder>()(obj, serializer, builder[index++]);
  }
};

void Serializer::Save(const std::string& file) {
  unsigned long index = 0;

<CAPNP_ID>

  const int fileid = open(file.c_str(), O_CREAT | O_WRONLY | O_BINARY, S_IRWXU);
  ::capnp::MallocMessageBuilder message;
  UhdmRoot::Builder cap_root = message.initRoot<UhdmRoot>();

  ::capnp::List<Design>::Builder designs = cap_root.initDesigns(designMaker.objects_.size());
  index = 0;
  for (auto design : designMaker.objects_) {
    designs[index].setVpiName(design->GetSerializer()->symbolMaker.Make(design->VpiName()));
    index++;
  }

<CAPNP_SAVE>

  // Save the symbols after all save function have been invoked, some symbols are made doing so (VpiFullName)
  // This is not ideal.
  // Ideally, the save should not include the hierarchical nets that can be recreated on the fly.
  // Something broke this mechanism that saved a lot of memory/disk space.
  // Until that is repaired we go for the more disk-hungry and memory hungry method which gives correct results.
  ::capnp::List<::capnp::Text>::Builder symbols = cap_root.initSymbols(symbolMaker.id2SymbolMap_.size());
  index = 0;
  std::vector<char*> dups; 
  for (auto symbol : symbolMaker.id2SymbolMap_) {
    char* dup = strdup(symbol.c_str());
    dups.push_back(dup);
    symbols.set(index,dup);
    index++;
  }

  writePackedMessageToFd(fileid, message);
  close(fileid);
  for (auto dup : dups) {
    free(dup);
  }  
}

#if (defined(_MSC_VER) || defined(__MINGW32__) || defined(__CYGWIN__))
  #pragma warning(pop)
#endif
}  // namespace UHDM
