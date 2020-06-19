/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_Ast_STMT
#define REVISER_COMPILER_Ast_STMT

#include <string>
#include <vector>
#include <ast/node.h>

namespace reviser {
namespace ast {
  class Stmt: public Node {
  public:
    std::string generate();
  };

  class Seq: public Stmt {
  private:
    std::vector<Stmt> stmts;

  public:
    std::string generate();
    void AddStmt(Stmt stmt);
  };

}; // compiler
}; // reviser

#endif
