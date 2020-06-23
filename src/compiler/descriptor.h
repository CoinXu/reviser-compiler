//
//  @date 2020-06-23
//  @author duanxian0605@163.com
//  @description 定义.reviser文件内容标记，词法定义参考syntax.md
//

#ifndef REVISER_COMPILER_DESCRIPTOR
#define REVISER_COMPILER_DESCRIPTOR

#include<vector>
#include<string>

using namespace std;

namespace reviser {
namespace compiler {
  class Descriptor {
  private:
    vector<string> decorators_;
    vector<string> global_variables_;

  public:
    vector<string> decorators();
    vector<string> global_variables();

    void add_decorator(string decorator);
    void add_global_variable(string variable);
  };
}; // reviser
}; // compiler

#endif
