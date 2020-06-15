/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_STRUCT
#define REVISER_COMPILER_AST_STRUCT

#include <string>
#include <ast/stmt.h>
#include <ast/expr.h>
#include <vector>

namespace reviser {
namespace ast {
  class Declare: Expr {
  private:
    std::string type;
    ExprAssign assign;

  public:
    std::string generate();
    Declare(std::string type, ExprAssign assign);
  };

  class StructProperty: Stmt {
  private:
    Declare declare;
    std::vector<std::string> decorater;

  public:
    std::string generate();
    StructProperty(Declare declare);
    void AddDecorater(std::string decorater);
 };

  class Struct: Stmt {
  private:
    std::string word;
    std::string id;
    std::vector<StructProperty> property;

  public:
    std::string generate();
    Struct(std::string word, std::string id);
    void AddProperty(StructProperty property);
  };

}; // compiler
}; // reviser

#endif
