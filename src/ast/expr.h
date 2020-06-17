/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_EXPR
#define REVISER_COMPILER_AST_EXPR

#include <string>
#include <ast/node.h>

using namespace std;

namespace reviser {
namespace ast {
  class Expr: Node {
  public:
    string generate();
  };

  class ExprAssign: Expr {
  private:
    string id;
    string value;

  public:
    string generate();
    void SetId(string id);
    void SetValue(string value);
  };
}; // compiler
}; // reviser

#endif
