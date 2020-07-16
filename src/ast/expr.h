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
  // Foo.Bar
  class EnumValue : public Expr {
  public:
    Token* id;
    Token* property;

    EnumValue(Token* id, Token* property);
    ~EnumValue();
  };

  //
  // Foo foo = null
  // Foo foo = []
  // id -> type
  class StructValue : public Expr {
  public:
    Token* id;
    Token* value;
    StructValue(Token* id, Token* value);
    ~StructValue();
  };

  //
  // RightValue
  // 0
  // 0.123
  // "foo"
  // [123, 0.456]
  // [Color.A, Color.B]
  // null
  class RightValue : public Expr {
  public:
    DataType type;
    Token* id;
    bool array_type = false;
    vector<Token*> dvs;
    vector<EnumValue*> evs;
    StructValue* sv;
    EnumValue* ev;

    RightValue(DataType type, Token* id, bool array_type = false);
    RightValue(StructValue*, bool = false);
    RightValue(EnumValue*, bool = false);
    ~RightValue();
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
    RightValue* rv = nullptr;
    EnumValue* ev = nullptr;
    StructValue* sv = nullptr;
    vector<string> values;

    Declare(DataType type, Token* id, RightValue* rv, bool array_type = false);
    Declare(Token* id, StructValue* sv, bool array_type = false);
    Declare(Token* id, EnumValue* ev, bool array_type = false);

    ~Declare();
  };

}; // compiler
}; // reviser

#endif
