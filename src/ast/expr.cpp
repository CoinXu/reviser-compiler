
/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#include <ast/expr.h>

namespace reviser {
namespace ast {
  std::string Expr::generate() {
    return "";
  }

  ExprAssign::ExprAssign(std::string id, std::string value): id(id), value(value) {}

  std::string ExprAssign::generate() {
    return id + " = " + value;
  }
}; // reviser
}; // ast
