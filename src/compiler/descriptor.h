//
//  @date 2020-06-23
//  @author duanxian0605@163.com
//  @description 定义.reviser文件内容标记，词法定义参考syntax.md
//

#ifndef REVISER_COMPILER_DESCRIPTOR
#define REVISER_COMPILER_DESCRIPTOR

#include <string>
#include <stack>
#include <tokenizer.h>
#include <ast/stmt_enum.h>
#include <ast/stmt_struct.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
  enum DeclareType {
    DECLARE_ENUM,
    DECLARE_STRUCT,
    DECLARE_UNDEFINED
  };

  class Descriptor {
  public:
    struct VariableDeclare {
      string id;
      DeclareType type;
    };

    union VariableAst {
      Enum* e;
      Struct* s;
    };

    struct ContextVariable {
      string id;
      DeclareType type;
      VariableAst node;
    };

  private:
    vector<string> decorators_;
    vector<VariableDeclare> global_variables_;
    vector<DataType> data_types_;

  public:
    // 使用一个二维数组来存储作用域与作用域已声明的变量
    // 其中，一维元素代表一个作用域
    // 二维元素存储该作用域声明的变量
    vector<vector<ContextVariable>> context;
    bool include_type_array = false;
    bool include_struct_array = false;
    bool include_enum_array = false;

    // 压入一个新的上下文，添加一个新的数组到context中
    void PushNewContext();
    // 退出当前上下文，删除context最后一个数组
    void PopBackContext();
    // 在当前上下文中添Enum声明
    void PushContextVariable(Enum*);
    // 在当前上下文中添Struct声明
    void PushContextVariable(Struct*);

    // 作用域内通过id找已定义的声明，从当前开始一直找到最顶层
    ContextVariable* FindContextVariableById(string);
    // 当前作用域内通过id找已定义的声明，只找一层
    ContextVariable* FindCurrentContextVariableById(string);
    // 查找在当前作用域有效的声明的类型，从低往上找，以第一个找到的声明为准
    DeclareType FindContextVariableTypeById(string);

    // 通过id在作用域内找Enum声明
    Enum* FindEnumContextVariableById(string);
    // Enum是否已声明string标记的属性
    bool EnumInlcudeProperty(Enum*, string);

    // 同enum
    Struct* FindStructContextVariableById(string);
    bool StructIncludeProperty(Struct*, string);

    vector<string> Decorators();
    vector<VariableDeclare> GlobalVariables();
    vector<DataType> DataTypes();

    void AddDataTypesOnce(DataType type);
    void AddDecoratorOnce(string decorator);
    void AddGlobalVariableOnce(string variable, DeclareType type);

    Descriptor();
    ~Descriptor();
  };
}; // reviser
}; // compiler

#endif
