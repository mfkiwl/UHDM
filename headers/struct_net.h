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
 * File:   struct_net.h
 * Author:
 *
 * Created on December 14, 2019, 10:03 PM
 */

#ifndef STRUCT_NET_H
#define STRUCT_NET_H

namespace UHDM {

  class struct_net : public net {
  public:
    // Implicit constructor used to initialize all members,
    // comment: struct_net();
    ~struct_net() final {}
    
    BaseClass* get_vpiParent() const { return vpiParent_; }

    bool set_vpiParent(BaseClass* data) { vpiParent_ = data; return true;}

    unsigned int get_uhdmParentType() const { return uhdmParentType_; }

    bool set_uhdmParentType(unsigned int data) { uhdmParentType_ = data; return true;}

    std::string get_vpiFile() const { return SymbolFactory::getSymbol(vpiFile_); }

    bool set_vpiFile(std::string data) { vpiFile_ = SymbolFactory::make(data); return true; }

    unsigned int get_vpiLineNo() const { return vpiLineNo_; }

    bool set_vpiLineNo(unsigned int data) { vpiLineNo_ = data; return true;}

    bool get_vpiPackedArrayMember() const { return vpiPackedArrayMember_; }

    bool set_vpiPackedArrayMember(bool data) { vpiPackedArrayMember_ = data; return true;}

    VectorOfnets* get_nets() const { return nets_; }

    bool set_nets(VectorOfnets* data) { nets_ = data; return true;}

    VectorOfexpr* get_expr() const { return expr_; }

    bool set_expr(VectorOfexpr* data) { expr_ = data; return true;}

    unsigned int get_vpiType() { return vpiStructNet; }

    virtual unsigned int getUhdmType() { return uhdmstruct_net; }   
  private:
    
    BaseClass* vpiParent_;

    unsigned int uhdmParentType_;

    unsigned int vpiFile_;

    unsigned int vpiLineNo_;

    bool vpiPackedArrayMember_;

    VectorOfnets* nets_;

    VectorOfexpr* expr_;

  };

  class struct_netFactory {
  friend Serializer;
  public:
  static struct_net* make() {
    struct_net* obj = new struct_net();
    objects_.push_back(obj);
    return obj;
  }
  private:
    static std::vector<struct_net*> objects_;
  };
 	      
  class VectorOfstruct_netFactory {
  friend Serializer;
  public:
  static std::vector<struct_net*>* make() {
    std::vector<struct_net*>* obj = new std::vector<struct_net*>();
    objects_.push_back(obj);
    return obj;
  }
  private:
  static std::vector<std::vector<struct_net*>*> objects_;
  };

};

#endif

