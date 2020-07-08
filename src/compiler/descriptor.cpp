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
