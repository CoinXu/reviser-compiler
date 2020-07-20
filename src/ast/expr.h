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
  class StructValue : public Expr {
  public:
    // 即struct的类型，在grammery中，struct的id出现在类型位置处时，即表示声明类型为该struct
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
    // 如果类型是基本数据类型数组，则将值存在dvs中
    vector<Token*> dvs;
    // 如果类型是enum数组，则将值存在evs中
    vector<EnumValue*> evs;
    StructValue* sv;
    EnumValue* ev;

    RightValue(DataType type, Token* id, bool = false);
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
    Token* type_id = nullptr;
    RightValue* rv = nullptr;

    Declare(DataType type, Token* id, RightValue* rv, bool array_type = false);
    Declare(DataType type, Token* id, Token* type_id, RightValue* rv, bool array_type = false);

    ~Declare();
  };

}; // compiler
}; // reviser

#endif
