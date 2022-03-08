/*
 Do not modify, auto-generated by model_gen.tcl

 Copyright 2019-2020 Alain Dargelas

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
 * File:   clone_tree.cpp
 * Author:
 *
 * Created on December 14, 2019, 10:03 PM
 */
#include <uhdm/ElaboratorListener.h>
#include <uhdm/ExprEval.h>
#include <uhdm/clone_tree.h>
#include <uhdm/uhdm.h>

using namespace UHDM;

namespace UHDM {

BaseClass* clone_tree(const BaseClass* root, Serializer& s,
                      ElaboratorListener* elaborator) {
  return root ? root->DeepClone(&s, elaborator, nullptr) : nullptr;
}

tf_call* sys_func_call::DeepClone(Serializer* serializer,
                                  ElaboratorListener* elaborator,
                                  BaseClass* parent) const {
  sys_func_call* const clone = serializer->MakeSys_func_call();
  const unsigned long id = clone->UhdmId();
  *clone = *this;
  clone->UhdmId(id);
  clone->VpiParent(parent);
  if (auto obj = User_systf())
    clone->User_systf(obj->DeepClone(serializer, elaborator, clone));
  if (auto obj = Scope())
    clone->Scope(obj->DeepClone(serializer, elaborator, clone));
  if (auto vec = Tf_call_args()) {
    auto clone_vec = serializer->MakeAnyVec();
    clone->Tf_call_args(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto obj = Typespec())
    clone->Typespec(obj->DeepClone(serializer, elaborator, clone));

  return clone;
}

tf_call* sys_task_call::DeepClone(Serializer* serializer,
                                  ElaboratorListener* elaborator,
                                  BaseClass* parent) const {
  sys_task_call* const clone = serializer->MakeSys_task_call();
  const unsigned long id = clone->UhdmId();
  *clone = *this;
  clone->UhdmId(id);
  clone->VpiParent(parent);
  if (auto obj = User_systf())
    clone->User_systf(obj->DeepClone(serializer, elaborator, clone));
  if (auto obj = Scope())
    clone->Scope(obj->DeepClone(serializer, elaborator, clone));
  if (auto vec = Tf_call_args()) {
    auto clone_vec = serializer->MakeAnyVec();
    clone->Tf_call_args(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto obj = Typespec())
    clone->Typespec(obj->DeepClone(serializer, elaborator, clone));

  return clone;
}

tf_call* method_func_call::DeepClone(Serializer* serializer,
                                     ElaboratorListener* elaborator,
                                     BaseClass* parent) const {
  const expr* prefix = Prefix();
  if (prefix) {
    prefix = prefix->DeepClone(serializer, elaborator, (BaseClass*)this);
  }
  bool is_function = elaborator->isFunctionCall(VpiName(), prefix);
  tf_call* the_clone = nullptr;
  if (is_function) {
    method_func_call* const clone = serializer->MakeMethod_func_call();
    the_clone = clone;
    const unsigned long id = clone->UhdmId();
    *clone = *this;
    clone->UhdmId(id);
    clone->VpiParent(parent);
    if (auto obj = Prefix())
      clone->Prefix(obj->DeepClone(serializer, elaborator, clone));
    const ref_obj* ref = any_cast<const ref_obj*>(clone->Prefix());
    const class_var* prefix = nullptr;
    if (ref) prefix = any_cast<const class_var*>(ref->Actual_group());
    if (function* f =
            any_cast<function*>(elaborator->bindTaskFunc(VpiName(), prefix))) {
      clone->Function(f);
    }
    if (auto obj = With())
      clone->With(obj->DeepClone(serializer, elaborator, clone));
    if (auto obj = Scope())
      clone->Scope(obj->DeepClone(serializer, elaborator, clone));
    if (auto vec = Tf_call_args()) {
      auto clone_vec = serializer->MakeAnyVec();
      clone->Tf_call_args(clone_vec);
      for (auto obj : *vec) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      }
    }
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
  } else {
    method_task_call* const clone = serializer->MakeMethod_task_call();
    the_clone = clone;
    const unsigned long id = clone->UhdmId();
    //*clone = *this;
    clone->VpiName(VpiName());
    clone->Tf_call_args(Tf_call_args());
    clone->UhdmId(id);
    clone->VpiParent(parent);
    clone->VpiFile(VpiFile());
    clone->VpiLineNo(VpiLineNo());
    clone->VpiColumnNo(VpiColumnNo());
    clone->VpiEndLineNo(VpiEndLineNo());
    clone->VpiEndColumnNo(VpiEndColumnNo());
    if (auto obj = Prefix())
      clone->Prefix(obj->DeepClone(serializer, elaborator, clone));
    const ref_obj* ref = any_cast<const ref_obj*>(clone->Prefix());
    const class_var* prefix = nullptr;
    if (ref) prefix = any_cast<const class_var*>(ref->Actual_group());
    if (task* f =
            any_cast<task*>(elaborator->bindTaskFunc(VpiName(), prefix))) {
      clone->Task(f);
    }
    if (auto obj = With())
      clone->With(obj->DeepClone(serializer, elaborator, clone));
    if (auto obj = Scope())
      clone->Scope(obj->DeepClone(serializer, elaborator, clone));
    if (auto vec = Tf_call_args()) {
      auto clone_vec = serializer->MakeAnyVec();
      clone->Tf_call_args(clone_vec);
      for (auto obj : *vec) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      }
    }
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
  }
  return the_clone;
}

constant* constant::DeepClone(Serializer* serializer,
                              ElaboratorListener* elaborator,
                              BaseClass* parent) const {
  if (elaborator->uniquifyTypespec()) {
    constant* const clone = serializer->MakeConstant();
    const unsigned long id = clone->UhdmId();
    *clone = *this;
    clone->UhdmId(id);
    clone->VpiParent(parent);
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
    return clone;
  } else {
    return (constant*)this;
  }
}

tagged_pattern* tagged_pattern::DeepClone(Serializer* serializer,
                                          ElaboratorListener* elaborator,
                                          BaseClass* parent) const {
  if (elaborator->uniquifyTypespec()) {
    tagged_pattern* const clone = serializer->MakeTagged_pattern();
    const unsigned long id = clone->UhdmId();
    *clone = *this;
    clone->UhdmId(id);
    clone->VpiParent(parent);
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
    if (auto obj = Pattern())
      clone->Pattern(obj->DeepClone(serializer, elaborator, clone));
    return clone;
  } else {
    return (tagged_pattern*)this;
  }
}

tf_call* method_task_call::DeepClone(Serializer* serializer,
                                     ElaboratorListener* elaborator,
                                     BaseClass* parent) const {
  const expr* prefix = Prefix();
  if (prefix) {
    prefix = prefix->DeepClone(serializer, elaborator, (BaseClass*)this);
  }
  bool is_task = elaborator->isTaskCall(VpiName(), prefix);
  tf_call* the_clone = nullptr;
  if (is_task) {
    method_task_call* const clone = serializer->MakeMethod_task_call();
    the_clone = clone;
    const unsigned long id = clone->UhdmId();
    *clone = *this;
    clone->UhdmId(id);
    clone->VpiParent(parent);
    if (auto obj = Prefix())
      clone->Prefix(obj->DeepClone(serializer, elaborator, clone));
    const ref_obj* ref = any_cast<const ref_obj*>(clone->Prefix());
    const class_var* prefix = nullptr;
    if (ref) prefix = any_cast<const class_var*>(ref->Actual_group());
    if (task* t =
            any_cast<task*>(elaborator->bindTaskFunc(VpiName(), prefix))) {
      clone->Task(t);
    }
    if (auto obj = With())
      clone->With(obj->DeepClone(serializer, elaborator, clone));
    if (auto obj = Scope())
      clone->Scope(obj->DeepClone(serializer, elaborator, clone));
    if (auto vec = Tf_call_args()) {
      auto clone_vec = serializer->MakeAnyVec();
      clone->Tf_call_args(clone_vec);
      for (auto obj : *vec) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      }
    }
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
  } else {
    method_func_call* const clone = serializer->MakeMethod_func_call();
    the_clone = clone;
    const unsigned long id = clone->UhdmId();
    //*clone = *this;
    clone->VpiName(VpiName());
    clone->Tf_call_args(Tf_call_args());
    clone->UhdmId(id);
    clone->VpiParent(parent);
    clone->VpiFile(VpiFile());
    clone->VpiLineNo(VpiLineNo());
    clone->VpiColumnNo(VpiColumnNo());
    clone->VpiEndLineNo(VpiEndLineNo());
    clone->VpiEndColumnNo(VpiEndColumnNo());
    if (auto obj = Prefix())
      clone->Prefix(obj->DeepClone(serializer, elaborator, clone));
    const ref_obj* ref = any_cast<const ref_obj*>(clone->Prefix());
    const class_var* prefix = nullptr;
    if (ref) prefix = any_cast<const class_var*>(ref->Actual_group());
    if (function* t =
            any_cast<function*>(elaborator->bindTaskFunc(VpiName(), prefix))) {
      clone->Function(t);
    }
    if (auto obj = With())
      clone->With(obj->DeepClone(serializer, elaborator, clone));
    if (auto obj = Scope())
      clone->Scope(obj->DeepClone(serializer, elaborator, clone));
    if (auto vec = Tf_call_args()) {
      auto clone_vec = serializer->MakeAnyVec();
      clone->Tf_call_args(clone_vec);
      for (auto obj : *vec) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      }
    }
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
  }
  return the_clone;
}

tf_call* func_call::DeepClone(Serializer* serializer,
                              ElaboratorListener* elaborator,
                              BaseClass* parent) const {
  bool is_function = elaborator->isFunctionCall(VpiName(), nullptr);
  tf_call* the_clone = nullptr;
  if (is_function) {
    func_call* const clone = serializer->MakeFunc_call();
    the_clone = clone;
    const unsigned long id = clone->UhdmId();
    *clone = *this;
    clone->UhdmId(id);
    clone->VpiParent(parent);
    if (function* f =
            any_cast<function*>(elaborator->bindTaskFunc(VpiName()))) {
      clone->Function(f);
    } else {
      elaborator->scheduleTaskFuncBinding(clone);
    }
    if (auto obj = Scope())
      clone->Scope(obj->DeepClone(serializer, elaborator, clone));
    if (auto vec = Tf_call_args()) {
      auto clone_vec = serializer->MakeAnyVec();
      clone->Tf_call_args(clone_vec);
      for (auto obj : *vec) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      }
    }
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
  } else {
    task_call* const clone = serializer->MakeTask_call();
    the_clone = clone;
    const unsigned long id = clone->UhdmId();
    //*clone = *this;
    clone->VpiName(VpiName());
    clone->Tf_call_args(Tf_call_args());
    clone->UhdmId(id);
    clone->VpiParent(parent);
    clone->VpiFile(VpiFile());
    clone->VpiLineNo(VpiLineNo());
    clone->VpiColumnNo(VpiColumnNo());
    clone->VpiEndLineNo(VpiEndLineNo());
    clone->VpiEndColumnNo(VpiEndColumnNo());
    if (task* f = any_cast<task*>(elaborator->bindTaskFunc(VpiName()))) {
      clone->Task(f);
    }
    if (auto obj = Scope())
      clone->Scope(obj->DeepClone(serializer, elaborator, clone));
    if (auto vec = Tf_call_args()) {
      auto clone_vec = serializer->MakeAnyVec();
      clone->Tf_call_args(clone_vec);
      for (auto obj : *vec) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      }
    }
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
  }

  return the_clone;
}

tf_call* task_call::DeepClone(Serializer* serializer,
                              ElaboratorListener* elaborator,
                              BaseClass* parent) const {
  bool is_task = elaborator->isTaskCall(VpiName(), nullptr);
  tf_call* the_clone = nullptr;
  if (is_task) {
    task_call* const clone = serializer->MakeTask_call();
    the_clone = clone;
    const unsigned long id = clone->UhdmId();
    *clone = *this;
    clone->UhdmId(id);
    clone->VpiParent(parent);
    if (task* t = any_cast<task*>(elaborator->bindTaskFunc(VpiName()))) {
      clone->Task(t);
    }
    if (auto obj = Scope())
      clone->Scope(obj->DeepClone(serializer, elaborator, clone));
    if (auto vec = Tf_call_args()) {
      auto clone_vec = serializer->MakeAnyVec();
      clone->Tf_call_args(clone_vec);
      for (auto obj : *vec) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      }
    }
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
  } else {
    func_call* const clone = serializer->MakeFunc_call();
    the_clone = clone;
    const unsigned long id = clone->UhdmId();
    //*clone = *this;
    clone->VpiName(VpiName());
    clone->VpiFile(VpiFile());
    clone->VpiLineNo(VpiLineNo());
    clone->VpiColumnNo(VpiColumnNo());
    clone->VpiEndLineNo(VpiEndLineNo());
    clone->VpiEndColumnNo(VpiEndColumnNo());
    clone->Tf_call_args(Tf_call_args());
    clone->UhdmId(id);
    clone->VpiParent(parent);
    if (function* t =
            any_cast<function*>(elaborator->bindTaskFunc(VpiName()))) {
      clone->Function(t);
    }
    if (auto obj = Scope())
      clone->Scope(obj->DeepClone(serializer, elaborator, clone));
    if (auto vec = Tf_call_args()) {
      auto clone_vec = serializer->MakeAnyVec();
      clone->Tf_call_args(clone_vec);
      for (auto obj : *vec) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      }
    }
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
  }
  return the_clone;
}

gen_scope_array* gen_scope_array::DeepClone(Serializer* serializer,
                                            ElaboratorListener* elaborator,
                                            BaseClass* parent) const {
  gen_scope_array* const clone = serializer->MakeGen_scope_array();
  const unsigned long id = clone->UhdmId();
  *clone = *this;
  clone->UhdmId(id);
  clone->VpiParent(parent);
  if (auto obj = Gen_var())
    clone->Gen_var(obj->DeepClone(serializer, elaborator, clone));
  if (auto vec = Gen_scopes()) {
    auto clone_vec = serializer->MakeGen_scopeVec();
    clone->Gen_scopes(clone_vec);
    for (auto obj : *vec) {
      elaborator->enterGen_scope(obj, parent, nullptr, nullptr);
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      elaborator->leaveGen_scope(obj, parent, nullptr, nullptr);
    }
  }
  if (auto obj = VpiInstance())
    clone->VpiInstance(obj->DeepClone(serializer, elaborator, clone));

  return clone;
}

function* function::DeepClone(Serializer* serializer,
                              ElaboratorListener* elaborator,
                              BaseClass* parent) const {
  function* const clone = serializer->MakeFunction();
  const unsigned long id = clone->UhdmId();
  *clone = *this;
  clone->UhdmId(id);
  clone->VpiParent(parent);
  if (auto obj = Left_range())
    clone->Left_range(obj->DeepClone(serializer, elaborator, clone));
  if (auto obj = Right_range())
    clone->Right_range(obj->DeepClone(serializer, elaborator, clone));
  if (auto obj = Return()) clone->Return((variables*)obj);
  if (auto obj = Instance()) clone->Instance((instance*)obj);
  if (instance* inst = any_cast<instance*>(parent)) clone->Instance(inst);
  if (auto obj = Class_defn())
    clone->Class_defn(obj->DeepClone(serializer, elaborator, clone));
  if (auto obj = Ref_obj())
    clone->Ref_obj(obj->DeepClone(serializer, elaborator, clone));
  if (auto vec = Io_decls()) {
    auto clone_vec = serializer->MakeIo_declVec();
    clone->Io_decls(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Variables()) {
    auto clone_vec = serializer->MakeVariablesVec();
    clone->Variables(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Parameters()) {
    auto clone_vec = serializer->MakeAnyVec();
    clone->Parameters(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Scopes()) {
    auto clone_vec = serializer->MakeScopeVec();
    clone->Scopes(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Typespecs()) {
    auto clone_vec = serializer->MakeTypespecVec();
    clone->Typespecs(clone_vec);
    for (auto obj : *vec) {
      if (elaborator->uniquifyTypespec()) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      } else {
        clone_vec->push_back(obj);
      }
    }
  }
  elaborator->enterTask_func(clone, parent, nullptr, nullptr);
  if (auto vec = Concurrent_assertions()) {
    auto clone_vec = serializer->MakeConcurrent_assertionsVec();
    clone->Concurrent_assertions(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Property_decls()) {
    auto clone_vec = serializer->MakeProperty_declVec();
    clone->Property_decls(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Sequence_decls()) {
    auto clone_vec = serializer->MakeSequence_declVec();
    clone->Sequence_decls(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Named_events()) {
    auto clone_vec = serializer->MakeNamed_eventVec();
    clone->Named_events(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Named_event_arrays()) {
    auto clone_vec = serializer->MakeNamed_event_arrayVec();
    clone->Named_event_arrays(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Virtual_interface_vars()) {
    auto clone_vec = serializer->MakeVirtual_interface_varVec();
    clone->Virtual_interface_vars(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Logic_vars()) {
    auto clone_vec = serializer->MakeLogic_varVec();
    clone->Logic_vars(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Array_vars()) {
    auto clone_vec = serializer->MakeArray_varVec();
    clone->Array_vars(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Array_var_mems()) {
    auto clone_vec = serializer->MakeArray_varVec();
    clone->Array_var_mems(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Param_assigns()) {
    auto clone_vec = serializer->MakeParam_assignVec();
    clone->Param_assigns(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Let_decls()) {
    auto clone_vec = serializer->MakeLet_declVec();
    clone->Let_decls(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Attributes()) {
    auto clone_vec = serializer->MakeAttributeVec();
    clone->Attributes(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Instance_items()) {
    auto clone_vec = serializer->MakeAnyVec();
    clone->Instance_items(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto obj = Stmt())
    clone->Stmt(obj->DeepClone(serializer, elaborator, clone));
  elaborator->leaveTask_func(clone, parent, nullptr, nullptr);
  return clone;
}

task* task::DeepClone(Serializer* serializer, ElaboratorListener* elaborator,
                      BaseClass* parent) const {
  task* const clone = serializer->MakeTask();
  const unsigned long id = clone->UhdmId();
  *clone = *this;
  clone->UhdmId(id);
  clone->VpiParent(parent);
  if (auto obj = Left_range())
    clone->Left_range(obj->DeepClone(serializer, elaborator, clone));
  if (auto obj = Right_range())
    clone->Right_range(obj->DeepClone(serializer, elaborator, clone));
  if (auto obj = Return())
    clone->Return(obj->DeepClone(serializer, elaborator, clone));
  if (auto obj = Instance()) clone->Instance((instance*)obj);
  if (instance* inst = any_cast<instance*>(parent)) clone->Instance(inst);
  if (auto obj = Class_defn())
    clone->Class_defn(obj->DeepClone(serializer, elaborator, clone));
  if (auto obj = Ref_obj())
    clone->Ref_obj(obj->DeepClone(serializer, elaborator, clone));
  if (auto vec = Io_decls()) {
    auto clone_vec = serializer->MakeIo_declVec();
    clone->Io_decls(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Variables()) {
    auto clone_vec = serializer->MakeVariablesVec();
    clone->Variables(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Scopes()) {
    auto clone_vec = serializer->MakeScopeVec();
    clone->Scopes(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Typespecs()) {
    auto clone_vec = serializer->MakeTypespecVec();
    clone->Typespecs(clone_vec);
    for (auto obj : *vec) {
      if (elaborator->uniquifyTypespec()) {
        clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
      } else {
        clone_vec->push_back(obj);
      }
    }
  }
  elaborator->enterTask_func(clone, parent, nullptr, nullptr);
  if (auto vec = Concurrent_assertions()) {
    auto clone_vec = serializer->MakeConcurrent_assertionsVec();
    clone->Concurrent_assertions(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Property_decls()) {
    auto clone_vec = serializer->MakeProperty_declVec();
    clone->Property_decls(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Sequence_decls()) {
    auto clone_vec = serializer->MakeSequence_declVec();
    clone->Sequence_decls(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Named_events()) {
    auto clone_vec = serializer->MakeNamed_eventVec();
    clone->Named_events(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Named_event_arrays()) {
    auto clone_vec = serializer->MakeNamed_event_arrayVec();
    clone->Named_event_arrays(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Virtual_interface_vars()) {
    auto clone_vec = serializer->MakeVirtual_interface_varVec();
    clone->Virtual_interface_vars(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Logic_vars()) {
    auto clone_vec = serializer->MakeLogic_varVec();
    clone->Logic_vars(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Array_vars()) {
    auto clone_vec = serializer->MakeArray_varVec();
    clone->Array_vars(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Array_var_mems()) {
    auto clone_vec = serializer->MakeArray_varVec();
    clone->Array_var_mems(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Param_assigns()) {
    auto clone_vec = serializer->MakeParam_assignVec();
    clone->Param_assigns(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Let_decls()) {
    auto clone_vec = serializer->MakeLet_declVec();
    clone->Let_decls(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Attributes()) {
    auto clone_vec = serializer->MakeAttributeVec();
    clone->Attributes(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Parameters()) {
    auto clone_vec = serializer->MakeAnyVec();
    clone->Parameters(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto vec = Instance_items()) {
    auto clone_vec = serializer->MakeAnyVec();
    clone->Instance_items(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (auto obj = Stmt())
    clone->Stmt(obj->DeepClone(serializer, elaborator, clone));
  elaborator->leaveTask_func(clone, parent, nullptr, nullptr);
  return clone;
}

cont_assign* cont_assign::DeepClone(Serializer* serializer,
                                    ElaboratorListener* elaborator,
                                    BaseClass* parent) const {
  cont_assign* const clone = serializer->MakeCont_assign();
  const unsigned long id = clone->UhdmId();
  *clone = *this;
  clone->UhdmId(id);
  clone->VpiParent(parent);
  if (auto obj = Delay())
    clone->Delay(obj->DeepClone(serializer, elaborator, clone));
  expr* lhs = nullptr;
  if (auto obj = Lhs()) {
    lhs = obj->DeepClone(serializer, elaborator, clone);
    clone->Lhs(lhs);
  }
  if (auto obj = Rhs()) {
    expr* rhs = obj->DeepClone(serializer, elaborator, clone);
    clone->Rhs(rhs);
    if (lhs && lhs->UhdmType() == uhdmref_obj) {
      ref_obj* ref = (ref_obj*)lhs;
      const any* actual = ref->Actual_group();
      if (actual) {
        if (actual->UhdmType() == uhdmstruct_var) {
          struct_var* stv = (struct_var*)actual;
          ExprEval eval;
          eval.flattenPatternAssignments(*serializer, stv->Typespec(), rhs);
        }
      }
    }
  }
  if (auto vec = Cont_assign_bits()) {
    auto clone_vec = serializer->MakeCont_assign_bitVec();
    clone->Cont_assign_bits(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }

  return clone;
}

hier_path* hier_path::DeepClone(Serializer* serializer,
                                ElaboratorListener* elaborator,
                                BaseClass* parent) const {
  hier_path* const clone = serializer->MakeHier_path();
  const unsigned long id = clone->UhdmId();
  *clone = *this;
  clone->UhdmId(id);
  clone->VpiParent(parent);
  if (auto vec = Path_elems()) {
    auto clone_vec = serializer->MakeAnyVec();
    clone->Path_elems(clone_vec);
    any* previous = nullptr;
    for (auto obj : *vec) {
      any* current = nullptr;
      current = obj->DeepClone(serializer, elaborator, clone);
      clone_vec->push_back(current);
      bool found = false;
      if (previous) {
        const std::string& name = obj->VpiName();
        if (previous->UhdmType() == uhdmref_obj) {
          ref_obj* ref = (ref_obj*)previous;
          const any* actual = ref->Actual_group();
          if (actual) {
            if (actual->UhdmType() == uhdmstruct_net) {
              struct_typespec* stpt =
                  (struct_typespec*)((struct_net*)actual)->Typespec();
              for (typespec_member* member : *stpt->Members()) {
                if (member->VpiName() == name) {
                  if (current->UhdmType() == uhdmref_obj) {
                    ((ref_obj*)current)->Actual_group(member);
                  } else if (current->UhdmType() == uhdmbit_select) {
                    const any* parent = current->VpiParent();
                    if (parent && (parent->UhdmType() == uhdmref_obj))
                      ((ref_obj*)parent)->Actual_group(member);
                  }
                  previous = member;
                  found = true;
                  break;
                }
              }
            } else if (actual->UhdmType() == uhdminterface) {
              interface* interf = (interface*)actual;
              if (interf->Variables()) {
                for (variables* var : *interf->Variables()) {
                  if (var->VpiName() == name) {
                    if (current->UhdmType() == uhdmref_obj) {
                      ((ref_obj*)current)->Actual_group(var);
                    } else if (current->UhdmType() == uhdmbit_select) {
                      const any* parent = current->VpiParent();
                      if (parent && (parent->UhdmType() == uhdmref_obj))
                        ((ref_obj*)parent)->Actual_group(var);
                    }
                    previous = var;
                    found = true;
                    break;
                  }
                }
              }
            }
          }
        } else if (previous->UhdmType() == uhdmtypespec_member) {
          typespec_member* member = (typespec_member*)previous;
          const typespec* tps = member->Typespec();
          if (tps && (tps->UhdmType() == uhdmstruct_typespec)) {
            struct_typespec* stpt = (struct_typespec*)tps;
            for (typespec_member* member : *stpt->Members()) {
              if (member->VpiName() == name) {
                if (current->UhdmType() == uhdmref_obj) {
                  ((ref_obj*)current)->Actual_group(member);
                  previous = member;
                  found = true;
                  break;
                }
              }
            }
          }
        }
      }
      if (!found) previous = current;
    }
  }
  if (auto vec = VpiUses()) {
    auto clone_vec = serializer->MakeAnyVec();
    clone->VpiUses(clone_vec);
    for (auto obj : *vec) {
      clone_vec->push_back(obj->DeepClone(serializer, elaborator, clone));
    }
  }
  if (elaborator->uniquifyTypespec()) {
    if (auto obj = Typespec())
      clone->Typespec(obj->DeepClone(serializer, elaborator, clone));
  } else {
    if (auto obj = Typespec()) clone->Typespec((typespec*)obj);
  }

  return clone;
}
}  // UHDM namespace

