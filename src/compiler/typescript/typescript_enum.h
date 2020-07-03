/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_TYPESCRIPT_ENUM
#define REVISER_COMPILER_TYPESCRIPT_ENUM

#include <compiler/typescript/typescript_stmt.h>
#include <compiler/typescript/typescript_struct.h>
#include <ast/stmt_enum.h>

using namespace reviser::ast;
using namespace reviser::message;
using namespace std;

namespace reviser {
namespace compiler {
  class TypeScriptEnum : public TypeScriptStmt {
  public:
    TypeScriptStruct* parent = nullptr;
    Enum* node = nullptr;

    string Generate();
    TypeScriptEnum(Enum* node);
    TypeScriptEnum(Enum* node, TypeScriptStruct* parent);
    ~TypeScriptEnum();
  };

  class TypeScriptEnumProperty : public TypeScriptStmt {
  public:
    TypeScriptEnum* parent = nullptr;
    EnumProperty* node = nullptr;

    string Generate(int index = 0);
    TypeScriptEnumProperty(EnumProperty* node, TypeScriptEnum* parent);
    ~TypeScriptEnumProperty();
  };
};
};

#endif
