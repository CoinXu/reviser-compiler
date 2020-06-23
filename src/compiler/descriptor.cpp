//
//  @date 2020-06-23
//  @author duanxian0605@163.com
//  @description 定义.reviser文件内容标记，词法定义参考syntax.md
//

#include <compiler/descriptor.h>

namespace reviser {
namespace compiler {
  vector<string> Descriptor::decorators() {
    return decorators_;
  }

  vector<string> Descriptor::global_variables() {
    return global_variables_;
  }

  void Descriptor::add_decorator(string decorator) {
    decorators_.push_back(decorator);
  }

  void Descriptor::add_global_variable(string variable) {
    global_variables_.push_back(variable);
  }
}; // reviser
}; // compiler
