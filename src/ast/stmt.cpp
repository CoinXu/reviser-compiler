
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
  string Stmt::generate() {
    return "";
  }

  //
  // Seq
  void Seq::AddStmt(Stmt stmt) {
    stmts.push_back(stmt);
  }

  string Seq::generate() {
    string code;
    for (Stmt s: stmts) {
      code = code + s.generate();
    }
    return code;
  }

}; // reviser
}; // ast
