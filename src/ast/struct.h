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
  class Declare: Expr {
  private:
    string type;
    ExprAssign assign;

  public:
    string generate();
    Declare(string type, ExprAssign assign);
  };

  class StructProperty: Stmt {
  private:
    Declare declare;
    vector<string> decorater;

  public:
    string generate();
    StructProperty(Declare declare);
    void AddDecorater(string decorater);
 };

  class Struct: Stmt {
  private:
    string word;
    string id;
    vector<StructProperty> property;

  public:
    string generate();
    void SetWord(string word);
    void SetID(string id);
    void AddProperty(StructProperty property);
  };

}; // compiler
}; // reviser

#endif
