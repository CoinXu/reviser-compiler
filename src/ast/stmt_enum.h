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
  // AstEnumProperty
  class AstEnumProperty: public AstStmt {
  private:
    Token id;
    AstRightValue value = EmpytDataValue;

  public:
    string generate();
    AstEnumProperty(Token id, AstRightValue value);
    AstEnumProperty(Token id);
  };

  //
  // AstEnum
  class AstEnum: public AstStmt {
  private:
    Token id;
    vector<AstEnumProperty> properties;

  public:
    string generate();
    AstEnum(Token id);
    void AddProperty(AstEnumProperty property);
  };

}; // reviser
}; // ast

#endif

