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
 * File:   BaseClass.cpp
 * Author:
 *
 * Created on January 04, 2021, 01:01 AM
 */
#include <uhdm/BaseClass.h>
#include <uhdm/Serializer.h>

namespace UHDM {
std::string_view BaseClass::VpiFile() const {
  return vpiFile_ ? serializer_->symbolMaker.GetSymbol(vpiFile_) : kEmpty;
}

bool BaseClass::VpiFile(std::string_view data) {
  vpiFile_ = serializer_->symbolMaker.Make(data);
  return true;
}

const BaseClass* BaseClass::GetByVpiName(std::string_view name) const {
  return nullptr;
}

std::tuple<const BaseClass*, UHDM_OBJECT_TYPE,
           const std::vector<const BaseClass*>*>
BaseClass::GetByVpiType(int32_t type) const {
  switch (type) {
    case vpiParent:
      return std::make_tuple(vpiParent_, static_cast<UHDM_OBJECT_TYPE>(0),
                             nullptr);
    default:
      return std::make_tuple(nullptr, static_cast<UHDM_OBJECT_TYPE>(0),
                             nullptr);
  };
}

BaseClass::vpi_property_value_t BaseClass::GetVpiPropertyValue(
    int32_t property) const {
  switch (property) {
    case vpiLineNo:
      return vpi_property_value_t(vpiLineNo_);
    case vpiColumnNo:
      return vpi_property_value_t(vpiColumnNo_);
    case vpiEndLineNo:
      return vpi_property_value_t(vpiEndLineNo_);
    case vpiEndColumnNo:
      return vpi_property_value_t(vpiEndColumnNo_);
    case vpiType:
      return vpi_property_value_t(VpiType());
    case vpiFile: {
      const std::string_view file = VpiFile();
      if (!file.empty()) {
        return vpi_property_value_t(file.data());
      }
    } break;
    case vpiName: {
      const std::string_view name = VpiName();
      if (!name.empty()) {
        return vpi_property_value_t(name.data());
      }
    } break;
    case vpiDefName: {
      const std::string_view defname = VpiDefName();
      if (!defname.empty()) {
        return vpi_property_value_t(defname.data());
      }
    } break;
  }
  return vpi_property_value_t();
}

BaseClass* BaseClass::DeepClone(BaseClass* parent,
                                CloneContext* context) const {
  return nullptr;
}

void BaseClass::DeepCopy(BaseClass* clone, BaseClass* parent,
                         CloneContext* context) const {
  clone->VpiParent(parent);
}

std::string BaseClass::ComputeFullName() const {
  if ((UhdmType() == uhdmmodule_inst) && (VpiParent() != nullptr) &&
      (VpiParent()->UhdmType() == uhdmmodule_inst)) {
    return std::string(VpiDefName());
  }
  std::vector<std::string_view> names;
  const BaseClass* parent = this;
  const BaseClass* child = nullptr;
  bool column = false;
  while (parent != nullptr) {
    const BaseClass* actual_parent = parent->VpiParent();
    UHDM_OBJECT_TYPE parent_type =
        (parent != nullptr) ? parent->UhdmType() : uhdmunsupported_stmt;
    UHDM_OBJECT_TYPE actual_parent_type = (actual_parent != nullptr)
                                              ? actual_parent->UhdmType()
                                              : uhdmunsupported_stmt;
    if (parent_type == uhdmdesign) break;
    if ((parent_type == uhdmpackage) || (parent_type == uhdmclass_defn))
      column = true;
    std::string_view name =
        parent->VpiName().empty() ? parent->VpiDefName() : parent->VpiName();
    bool skip_name = (actual_parent_type == uhdmref_obj) ||
                     (parent_type == uhdmmethod_func_call) ||
                     (parent_type == uhdmmethod_task_call) ||
                     (parent_type == uhdmfunc_call) ||
                     (parent_type == uhdmtask_call) ||
                     (parent_type == uhdmsys_func_call) ||
                     (parent_type == uhdmsys_task_call);
    if (child != nullptr) {
      UHDM_OBJECT_TYPE child_type = child->UhdmType();
      if ((child_type == uhdmbit_select) && (parent_type == uhdmport)) {
        skip_name = true;
      }
      if ((child_type == uhdmref_obj) && (parent_type == uhdmbit_select)) {
        skip_name = true;
      }
      if ((child_type == uhdmref_obj) &&
          (parent_type == uhdmindexed_part_select)) {
        skip_name = true;
      }
      if ((child_type == uhdmref_obj) && (parent_type == uhdmhier_path)) {
        skip_name = true;
      }
    }
    if ((!name.empty()) && (!skip_name)) {
      names.emplace_back(name);
    }
    child = parent;
    parent = parent->VpiParent();
  }
  std::string fullName;
  if (!names.empty()) {
    size_t index = names.size() - 1;
    while (1) {
      fullName += names[index];
      if (index > 0) fullName += column ? "::" : ".";
      if (index == 0) break;
      index--;
    }
  }
  return fullName;
}

int32_t BaseClass::Compare(const BaseClass* const other,
                           CompareContext* context) const {
  int32_t r = 0;

  const thistype_t* const lhs = this;
  const thistype_t* const rhs = other;

  if ((r = VpiType() - rhs->VpiType()) != 0) {
    context->m_failedLhs = lhs;
    context->m_failedRhs = rhs;
    return r;
  }
  if ((r = VpiName().compare(rhs->VpiName())) != 0) {
    context->m_failedLhs = lhs;
    context->m_failedRhs = rhs;
    return r;
  }
  if ((r = VpiDefName().compare(rhs->VpiDefName())) != 0) {
    context->m_failedLhs = lhs;
    context->m_failedRhs = rhs;
    return r;
  }

  return r;
}

}  // namespace UHDM
