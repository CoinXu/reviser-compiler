/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_STRUCT
#define REVISER_COMPILER_AST_STRUCT

#include <string>
#include <ast/stmt.h>
#include <ast/expr.h>
#include <vector>

using namespace std;

namespace reviser {
namespace ast {
  class ExprDeclare: Expr {
  private:
    string type;
    ExprAssign assign;

  public:
    string generate();
    ExprDeclare(string type, ExprAssign assign);
  };

  class StmtStmtStructProperty: Stmt {
  private:
    ExprDeclare declare;
    vector<string> decorater;

  public:
    string generate();
    StmtStmtStructProperty(ExprDeclare declare);
    void AddDecorater(string decorater);
 };

  class StmtStruct: Stmt {
  private:
    string word;
    string id;
    vector<StmtStmtStructProperty> property;

  public:
    string generate();
    void SetWord(string word);
    void SetID(string id);
    void AddProperty(StmtStmtStructProperty property);
  };

}; // compiler
}; // reviser

#endif
