/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_STMT
#define REVISER_COMPILER_AST_STMT

#include <string>
#include <vector>
#include <ast/node.h>

namespace reviser {
namespace ast {
  class Stmt: public Node {
  public:
    std::string Generate();
  };

  class Seq: public Stmt {
  private:
    std::vector<Stmt> stmts;

  public:
    std::string Generate();
    void AddStmt(Stmt stmt);
  };

}; // compiler
}; // reviser

#endif
