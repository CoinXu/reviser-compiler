/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_TYPESCRIPT_EXPR
#define REVISER_COMPILER_TYPESCRIPT_EXPR

#include <ast/expr.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
  class TypeScriptExpr {
  public:
    Expr* node = nullptr;
  };

  //
  // RightValue
  class TypeScriptRightValue : public TypeScriptExpr {
  public:
    RightValue* node = nullptr;

    string Generate();
    TypeScriptRightValue(RightValue* node);
    ~TypeScriptRightValue();
  };

  //
  // EnumValue
  class TypeScriptEnumValue : public TypeScriptExpr {
  public:
    EnumValue* node = nullptr;

    string Generate();
    TypeScriptEnumValue(EnumValue* node);
    ~TypeScriptEnumValue();
  };

  //
  // Assign
  class TypeScriptAssign : public TypeScriptExpr {
  public:
    Assign* node = nullptr;

    string Generate();
    TypeScriptAssign(Assign* node);
    ~TypeScriptAssign();
  };

  //
  // Declare
  class TypeScriptDeclare : public TypeScriptExpr {
  public:
    Declare* node = nullptr;

    string Generate();
    TypeScriptDeclare(Declare* node);
    ~TypeScriptDeclare();
  };

}; // compiler
}; // reviser

#endif
