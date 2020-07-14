/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_JAVASCRIPT_EXPR
#define REVISER_JAVASCRIPT_EXPR

#include <ast/expr.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace javascript {
  class JavaScriptExpr {
  public:
    Expr* node = nullptr;
  };

  //
  // RightValue
  class JavaScriptRightValue : public JavaScriptExpr {
  public:
    RightValue* node = nullptr;

    string Generate();
    JavaScriptRightValue(RightValue* node);
    ~JavaScriptRightValue();
  };

  //
  // EnumValue
  class JavaScriptEnumValue : public JavaScriptExpr {
  public:
    EnumValue* node = nullptr;

    string Generate();
    JavaScriptEnumValue(EnumValue* node);
    ~JavaScriptEnumValue();
  };

  //
  // Assign
  class JavaScriptAssign : public JavaScriptExpr {
  public:
    Assign* node = nullptr;

    string Generate();
    JavaScriptAssign(Assign* node);
    ~JavaScriptAssign();
  };

  //
  // Declare
  class JavaScriptDeclare : public JavaScriptExpr {
  public:
    Declare* node = nullptr;

    string Generate();
    JavaScriptDeclare(Declare* node);
    ~JavaScriptDeclare();
  };

}; // compiler
}; // reviser

#endif
