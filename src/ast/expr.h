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

  class StructValue : public Expr {
  public:
    Token* id;
    Token* value;
    StructValue(Token* id, Token* value);
    ~StructValue();
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
    bool array_type = false;
    Token* id = nullptr;
    Token* eid = nullptr;
    RightValue* dv = nullptr;
    EnumValue* ev = nullptr;
    StructValue* sv = nullptr;
    vector<string> values;

    Declare(DataType type, Token* id, RightValue* dv);
    Declare(DataType type, Token* id, Token* eid, EnumValue* ev);
    Declare(DataType type, Token* id);
    Declare(Token* id, StructValue* sv);
    ~Declare();
  };

}; // compiler
}; // reviser

#endif
