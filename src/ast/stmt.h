/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_STMT
#define REVISER_COMPILER_AST_STMT

#include <string>
#include <ast/node.h>

namespace reviser {
namespace ast {
  class Stmt: Node {
  public:
    std::string generate();
  };
}; // compiler
}; // reviser

#endif
