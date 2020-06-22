/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_EXPR
#define REVISER_COMPILER_AST_EXPR

#include <string>
#include <tokenizer.h>
#include <ast/node.h>

using namespace std;
using namespace reviser::compiler;

namespace reviser {
namespace ast {
  // Expr
  class Expr : public Node {

  };

  //
  // RightValue
  // 0
  // "foo"
  class RightValue : public Expr {
  public:
    DataType type;
    Token id;

    RightValue(DataType type, Token id);
  };

  static const RightValue EmptyRightValue(TYPE_NULL, EmptyToken);

  //
  // Foo.Bar
  class EnumValue : public Expr {
  public:
    Token id;
    Token property;

    EnumValue(Token id, Token property);
  };

  static const EnumValue EmptyEnumValue(EmptyToken, EmptyToken);

  //
  // Assign
  // foo = bar
  class Assign : public Expr {
  public:
    Token id;
    RightValue value;

    Assign(Token id, RightValue value);
  };

  //
  // Declare
  // int32 foo = 1
  // Color bar = Color.Red;
  class Declare : public Expr {
  public:
    DataType type;
    Token id;
    Token eid;
    RightValue dv = EmptyRightValue;
    EnumValue ev = EmptyEnumValue;

    Declare(DataType type, Token id, RightValue dv);
    Declare(DataType type, Token id, Token eid, EnumValue ev);
  };

}; // compiler
}; // reviser

#endif
