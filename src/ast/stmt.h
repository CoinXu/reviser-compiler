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
  class AstStmt: public AstNode {
  public:
    std::string generate();
  };

  class Seq: public AstStmt {
  private:
    std::vector<AstStmt> stmts;

  public:
    std::string generate();
    void AddStmt(AstStmt stmt);
  };

}; // compiler
}; // reviser

#endif
