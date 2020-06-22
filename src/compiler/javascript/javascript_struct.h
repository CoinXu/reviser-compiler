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
    JavaScriptStmt* parent = NULL;
    Struct* node;

    string Generate();
    JavaScriptStruct(Struct* node);
    JavaScriptStruct(Struct* node, JavaScriptStmt* parent);
    ~JavaScriptStruct();
  };

  class JavaScriptStructProperty : public JavaScriptStmt {
  public:
    JavaScriptStruct* parent = NULL;
    StructProperty* node;

    string Generate();
    JavaScriptStructProperty(StructProperty* node, JavaScriptStruct* parent);
    ~JavaScriptStructProperty();
  };

  class JavaScriptDecorater : public JavaScriptStmt {
  public:
    JavaScriptStruct* parent = NULL;
    Decorater* node;

    string Generate();
    JavaScriptDecorater(Decorater* node, JavaScriptStruct* parent);
    ~JavaScriptDecorater();
  };

}; // compiler
}; // reviser

#endif
