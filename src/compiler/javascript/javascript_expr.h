/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_JAVASCRIPT_EXPR
#define REVISER_COMPILER_JAVASCRIPT_EXPR

#include <ast/expr.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
  class JavaScriptExpr {
  public:
    Expr* node;
  };

  //
  // RightValue
  class JavaScriptRightValue : public JavaScriptExpr {
  public:
    RightValue* node;

    string Generate();
    JavaScriptRightValue(RightValue* node);
    ~JavaScriptRightValue();
  };

  //
  // EnumValue
  class JavaScriptEnumValue : public JavaScriptExpr {
  public:
    EnumValue* node;

    string Generate();
    JavaScriptEnumValue(EnumValue* node);
    ~JavaScriptEnumValue();
  };

  //
  // Assign
  class JavaScriptAssign : public JavaScriptExpr {
  public:
    Assign* node;

    string Generate();
    JavaScriptAssign(Assign* node);
    ~JavaScriptAssign();
  };

  //
  // Declare
  class JavaScriptDeclare : public JavaScriptExpr {
  public:
    Declare* node;

    string Generate();
    JavaScriptDeclare(Declare* node);
    ~JavaScriptDeclare();
  };

}; // reviser
}; // compiler

#endif
