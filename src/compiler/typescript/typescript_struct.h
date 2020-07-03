/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_TYPESCRIPT_STRUCT
#define REVISER_COMPILER_TYPESCRIPT_STRUCT

#include <ast/stmt_struct.h>
#include <compiler/typescript/typescript_common.h>
#include <compiler/typescript/typescript_stmt.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
  class TypeScriptStruct : public TypeScriptStmt {
  public:
    TypeScriptStruct* parent = nullptr;
    Struct* node = nullptr;

    string Generate();
    TypeScriptStruct(Struct* node);
    TypeScriptStruct(Struct* node, TypeScriptStruct* parent);
    ~TypeScriptStruct();
  };

  class TypeScriptStructProperty : public TypeScriptStmt {
  public:
    TypeScriptStruct* parent = nullptr;
    StructProperty* node = nullptr;

    string Generate();
    TypeScriptStructProperty(StructProperty* node, TypeScriptStruct* parent);
    ~TypeScriptStructProperty();
  };

  class TypeScriptStructInterfaceProperty : public TypeScriptStmt {
  public:
    TypeScriptStruct* parent = nullptr;
    StructProperty* node = nullptr;

    string Generate();
    TypeScriptStructInterfaceProperty(StructProperty* node, TypeScriptStruct* parent);
    ~TypeScriptStructInterfaceProperty();
  };

  class TypeScriptDecorater : public TypeScriptStmt {
  public:
    TypeScriptStruct* parent = nullptr;
    Decorater* node = nullptr;

    string Generate();
    TypeScriptDecorater(Decorater* node, TypeScriptStruct* parent);
    ~TypeScriptDecorater();
  };

}; // compiler
}; // reviser

#endif
