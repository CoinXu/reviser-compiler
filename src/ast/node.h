/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_NODE
#define REVISER_COMPILER_AST_NODE

#include <string>

namespace reviser {
namespace compiler {
  class Node {
  public:
    std::string to_string();
  };
}; // compiler
}; // reviser

#endif
