/**
 * @date 2020-06-18
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_STMT_ENUM
#define REVISER_COMPILER_AST_STMT_ENUM

#include <string>
#include <tokenizer.h>
#include <ast/stmt.h>
#include <ast/expr.h>

using namespace std;
using namespace reviser::compiler;

namespace reviser {
namespace ast {
  //
  // EnumProperty
  class EnumProperty: public Stmt {
  public:
    Token* id;
    RightValue* value = NULL;

    EnumProperty(Token* id, RightValue* value);
    EnumProperty(Token* id);

    ~EnumProperty();
  };

  //
  // Enum
  class Enum: public Stmt {
  public:
    Token* id;
    vector<EnumProperty*> properties;

    Enum(Token* id);
    ~Enum();
  };

}; // reviser
}; // ast

#endif

