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
    vector<vector<ContextVariable>> context;
    bool include_type_array = false;
    bool include_struct_array = false;
    bool include_enum_array = false;

    void PushNewContext();
    void PopBackContext();
    void PushContextVariable(Enum*);
    void PushContextVariable(Struct*);

    ContextVariable* FindContextVariableById(string);
    ContextVariable* FindCurrentContextVariableById(string);
    DeclareType FindContextVariableTypeById(string);

    Enum* FindEnumContextVariableById(string);
    bool EnumInlcudeProperty(Enum*, string);
    bool FindContextVariableEnumProperty(string, string);

    Struct* FindStructContextVariableById(string);
    bool StructIncludeProperty(Struct*, string);
    bool FindContextVariableStructProperty(string, string);

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
