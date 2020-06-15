/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_EXPR
#define REVISER_COMPILER_AST_EXPR

#include <string>
#include <ast/node.h>

namespace reviser {
namespace ast {
  class Expr: Node {
  public:
    std::string generate();
  };

  class ExprAssign: Expr {
  private:
    std::string id;
    std::string value;

  public:
    std::string generate();
    ExprAssign(std::string id, std::string value);
  };
}; // compiler
}; // reviser

#endif
