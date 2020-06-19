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
  class Node {
  public:
    virtual std::string Generate() = 0;
  };
}; // compiler
}; // reviser

#endif
