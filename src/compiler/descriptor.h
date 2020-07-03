//
//  @date 2020-06-23
//  @author duanxian0605@163.com
//  @description 定义.reviser文件内容标记，词法定义参考syntax.md
//

#ifndef REVISER_COMPILER_DESCRIPTOR
#define REVISER_COMPILER_DESCRIPTOR

#include<vector>
#include<string>
#include<tokenizer.h>

using namespace std;

namespace reviser {
namespace compiler {
  class Descriptor {
  private:
    vector<string> decorators_;
    vector<string> global_variables_;
    vector<DataType> data_types_;

  public:
    vector<string> Decorators();
    vector<string> GlobalVariables();
    vector<DataType> DataTypes();

    void AddDataTypes(DataType type);
    void AddDecorator(string decorator);
    void AddGlobalVariable(string variable);

    Descriptor();
    ~Descriptor();
  };
}; // reviser
}; // compiler

#endif
