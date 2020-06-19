/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_Ast_EXPR
#define REVISER_COMPILER_Ast_EXPR

#include <string>
#include <tokenizer.h>
#include <ast/node.h>

using namespace std;
using namespace reviser::compiler;

namespace reviser {
namespace ast {
  // Expr
  class Expr: public Node {
  public:
    string Generate();
  };

  //
  // RightValue
  // 0
  // "foo"
  class RightValue: public Expr {
  private:
    DataType type;
    Token id;

  public:
    RightValue(DataType type, Token id);
    DataType Type();
    string Generate();
  };

  static const RightValue EmpytDataValue(TYPE_NULL, EmptyToken);

  //
  // Foo.Bar
  class EnumValue: public Expr {
  private:
    Token id;
    Token property;

  public:
    EnumValue(Token id, Token property);
    string Generate();
  };

  static const EnumValue EmptyEnumValue(EmptyToken, EmptyToken);

  //
  // Assign
  // foo = bar
  class Assign: public Expr {
  private:
    Token id;
    RightValue value;

  public:
    Assign(Token id, RightValue value);
    string Generate();
  };

  //
  // Declare
  // int32 foo = 1
  // Color bar = Color.Red;
  class Declare: public Expr {
  private:
    DataType type;
    Token id;
    Token eid;
    RightValue dv = EmpytDataValue;
    EnumValue ev = EmptyEnumValue;

  public:
    Declare(DataType type, Token id, RightValue dv);
    Declare(DataType type, Token id, Token eid, EnumValue ev);
    string Generate();
  };

}; // compiler
}; // reviser

#endif
