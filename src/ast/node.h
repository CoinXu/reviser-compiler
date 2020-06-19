/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_NODE
#define REVISER_COMPILER_AST_NODE

#include <string>

namespace reviser {
namespace ast {
  class AstNode {
  public:
    virtual std::string generate() = 0;
  };
}; // compiler
}; // reviser

#endif
