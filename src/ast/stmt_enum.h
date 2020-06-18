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
  private:
    Token id;
    DataValue value = EmpytDataValue;

  public:
    string generate();
    EnumProperty(Token id, DataValue value);
    EnumProperty(Token id);
  };

  //
  // Enum
  class Enum: public Stmt {
  private:
    Token id;
    vector<EnumProperty> properties;

  public:
    string generate();
    Enum(Token id);
    void AddProperty(EnumProperty property);
  };

}; // reviser
}; // ast

#endif
