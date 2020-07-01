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
    Token* id;

    RightValue(DataType type, Token* id);
    ~RightValue();
  };

  //
  // Foo.Bar
  class EnumValue : public Expr {
  public:
    Token* id;
    Token* property;

    EnumValue(Token* id, Token* property);
    ~EnumValue();
  };

  //
  // Assign
  // foo = bar
  class Assign : public Expr {
  public:
    Token* id;
    RightValue* value;

    Assign(Token* id, RightValue* value);
    ~Assign();
  };

  //
  // Declare
  // int32 foo = 1
  // Color bar = Color.Red;
  class Declare : public Expr {
  public:
    DataType type;
    Token* id = NULL;
    Token* eid = NULL;
    RightValue* dv = NULL;
    EnumValue* ev = NULL;

    Declare(DataType type, Token* id, RightValue* dv);
    Declare(DataType type, Token* id, Token* eid, EnumValue* ev);
    ~Declare();
  };

}; // compiler
}; // reviser

#endif
