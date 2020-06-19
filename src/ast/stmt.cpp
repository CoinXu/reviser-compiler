
/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#include <ast/stmt.h>

using namespace std;

namespace reviser {
namespace ast {
  //
  //Stmt
  string Stmt::Generate() {
    return "";
  }

  //
  // Seq
  void Seq::AddStmt(Stmt stmt) {
    stmts.push_back(stmt);
  }

  string Seq::Generate() {
    string code;
    for (Stmt s: stmts) {
      code = code + s.Generate();
    }
    return code;
  }

}; // reviser
}; // ast
