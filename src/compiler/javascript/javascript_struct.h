/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_JAVASCRIPT_STRUCT
#define REVISER_COMPILER_JAVASCRIPT_STRUCT

#include <ast/stmt_struct.h>
#include <compiler/javascript/javascript_stmt.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
  class JavaScriptStruct : public JavaScriptStmt {
  public:
    JavaScriptStruct* parent = nullptr;
    Struct* node = nullptr;

    string Generate();
    JavaScriptStruct(Struct* node);
    JavaScriptStruct(Struct* node, JavaScriptStruct* parent);
    ~JavaScriptStruct();
  };

  class JavaScriptStructProperty : public JavaScriptStmt {
  public:
    JavaScriptStruct* parent = nullptr;
    StructProperty* node = nullptr;

    string Generate();
    JavaScriptStructProperty(StructProperty* node, JavaScriptStruct* parent);
    ~JavaScriptStructProperty();
  };

  class JavaScriptDecorater : public JavaScriptStmt {
  public:
    JavaScriptStruct* parent = nullptr;
    Decorater* node = nullptr;

    string Generate();
    JavaScriptDecorater(Decorater* node, JavaScriptStruct* parent);
    ~JavaScriptDecorater();
  };

}; // compiler
}; // reviser

#endif
