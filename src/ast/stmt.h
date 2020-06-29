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

using namespace std;

namespace reviser {
namespace ast {
  class Stmt: public Node {
  public:
    int level = 0;
    string name = "";

    virtual ~Stmt();
  };

  class Seq: public Stmt {
  public:
    vector<Stmt> stmts;
  };

}; // compiler
}; // reviser

#endif
