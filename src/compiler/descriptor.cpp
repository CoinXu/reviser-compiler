//
//  @date 2020-06-23
//  @author duanxian0605@163.com
//  @description 定义.reviser文件内容标记，词法定义参考syntax.md
//

#include <compiler/descriptor.h>

namespace reviser {
namespace compiler {
  template<typename T> bool VectorIncludeItem(vector<T>* v, const T* item) {
    for (auto it: *v) {
      if (it == *item) {
        return true;
      }
    }
    return false;
  }

  void Descriptor::PushNewContext() {
    context.push_back(vector<ContextVariable>({}));
  }

  void Descriptor::PopBackContext() {
    context.pop_back();
  }

  void Descriptor::PushContextVariable(Enum* e) {
    VariableAst node;
    node.e = e;
    context.back().push_back({ e->id->text, DECLARE_ENUM, node });
  }

  void Descriptor::PushContextVariable(Struct* s) {
    VariableAst node;
    node.s = s;
    context.back().push_back({ s->id->text, DECLARE_STRUCT, node });
  }

  bool Descriptor::EnumInlcudeProperty(Enum* e, string name) {
    if (!e) {
      return false;
    }

    for (auto item : e->properties) {
      if (item->id->text == name) {
        return true;
      }
    }

    return false;
  }

  Enum* Descriptor::FindEnumContextById(string id) {
    ContextVariable* variable = FindContextVariableById(id);

    if (!variable) {
      return nullptr;
    }

    if (variable->type == DECLARE_ENUM) {
      return variable->node.e;
    }

    return nullptr;
  }

  Struct* Descriptor::FindStructContextById(string id) {
    ContextVariable* variable = FindContextVariableById(id);

    if (!variable) {
      return nullptr;
    }

    if (variable->type == DECLARE_STRUCT) {
      return variable->node.s;
    }

    return nullptr;
  }

  bool Descriptor::FindContextVariableEnumProperty(string id, string property) {
    ContextVariable* variable = FindContextVariableById(id);

    if (!variable) {
      return false;
    }

    if (variable->type != DECLARE_ENUM) {
      return false;
    }

    return EnumInlcudeProperty(variable->node.e, property);
  }

  Descriptor::ContextVariable* Descriptor::FindContextVariableById(string id) {
    if (context.size() < 1) {
      return nullptr;
    }

    for (int i = context.size() - 1; i >= 0; i--) {
      vector<ContextVariable> v = context.at(i);

      if (v.size() < 1) {
        continue;
      }

      for (int j = v.size() - 1; j >= 0; j--) {
        if (v.at(j).id == id) {
          return &v.at(j);
        }
      }
    }
    return nullptr;
  }

  DeclareType Descriptor::FindContextVariableTypeById(string id) {
    ContextVariable* variable = FindContextVariableById(id);

    if (!variable) {
      return DECLARE_UNDEFINED;
    }

    return variable->type;
  }

  Descriptor::Descriptor() {}

  Descriptor::~Descriptor() {}

  vector<string> Descriptor::Decorators() {
    return decorators_;
  }

  vector<Descriptor::VariableDeclare> Descriptor::GlobalVariables() {
    return global_variables_;
  }

  vector<DataType> Descriptor::DataTypes() {
    return data_types_;
  }

  void Descriptor::AddDecorator(string decorator) {
    if (!VectorIncludeItem<string>(&decorators_, &decorator)) {
      decorators_.push_back(decorator);
    }
  }

  void Descriptor::AddGlobalVariable(string variable, DeclareType type) {
    for (auto it: global_variables_) {
      if (it.id == variable) {
        return;
      }
    }
    global_variables_.push_back({ variable, type });
  }

  void Descriptor::AddDataTypes(DataType type) {
    if (!VectorIncludeItem<DataType>(&data_types_, &type)) {
      data_types_.push_back(type);
    }
  }

}; // reviser
}; // compiler
