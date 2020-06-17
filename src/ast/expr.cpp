
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

  void ExprAssign::SetId(std::string id_) {
    id = id_;
  }

  void ExprAssign::SetValue(std::string value_) {
    value = value_;
  }

  std::string ExprAssign::generate() {
    return id + " = " + value;
  }
}; // reviser
}; // ast
