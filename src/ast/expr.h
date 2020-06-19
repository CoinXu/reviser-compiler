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
  // AstExpr
  class AstExpr: public AstNode {
  public:
    string generate();
  };

  //
  // AstRightValue
  // 0
  // "foo"
  class AstRightValue: public AstExpr {
  private:
    DataValueType type;
    Token id;

  public:
    AstRightValue(DataValueType type, Token id);
    DataValueType DataType();
    string generate();
  };

  static const AstRightValue EmpytDataValue(DataTypeNull, EmptyToken);

  //
  // Foo.Bar
  class AstEnumValue: public AstExpr {
  private:
    Token id;
    Token property;

  public:
    AstEnumValue(Token id, Token property);
    string generate();
  };

  static const AstEnumValue EmptyEnumValue(EmptyToken, EmptyToken);

  //
  // AstAssign
  // foo = bar
  class AstAssign: public AstExpr {
  private:
    Token id;
    AstRightValue value;

  public:
    AstAssign(Token id, AstRightValue value);
    string generate();
  };

  //
  // AstDeclare
  // int32 foo = 1
  // Color bar = Color.Red;
  class AstDeclare: public AstExpr {
  private:
    DataValueType type;
    Token id;
    Token eid;
    AstRightValue dv = EmpytDataValue;
    AstEnumValue ev = EmptyEnumValue;

  public:
    AstDeclare(DataValueType type, Token id, AstRightValue dv);
    AstDeclare(DataValueType type, Token id, Token eid, AstEnumValue ev);
    string generate();
  };

}; // compiler
}; // reviser

#endif
