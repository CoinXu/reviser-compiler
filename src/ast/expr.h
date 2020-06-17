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
  class Expr: public Node {
  public:
    string generate();
  };

  //
  // DataValue
  // 0
  // "foo"
  class DataValue: public Expr {
  private:
    DataValueType type;
    Token id;

  public:
    DataValue(DataValueType type, Token id);
    string generate();
  };

  //
  // Foo.Bar
  class EnumValue: public Expr {
  private:
    Token id;
    Token property;

  public:
    EnumValue(Token id, Token property);
    string generate();
  };

  //
  // Assign
  // foo = bar
  class Assign: public Expr {
  private:
    Token id;
    DataValue value;

  public:
    Assign(Token id, DataValue value);
    string generate();
  };

  //
  // Declare
  // int32 foo = 1
  // Color bar = Color.Red;
  class Declare: public Expr {
  private:
    DataValueType type;
    Token id;
    Token eid;
    DataValue dv;
    EnumValue ev;

  public:
    Declare(DataValueType type, Token id, DataValue dv);
    Declare(DataValueType type, Token id, Token eid, EnumValue ev);
    string generate();
  };

}; // compiler
}; // reviser

#endif
