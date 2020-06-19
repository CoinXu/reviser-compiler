
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
  //AstStmt
  string AstStmt::generate() {
    return "";
  }

  //
  // Seq
  void Seq::AddStmt(AstStmt stmt) {
    stmts.push_back(stmt);
  }

  string Seq::generate() {
    string code;
    for (AstStmt s: stmts) {
      code = code + s.generate();
    }
    return code;
  }

}; // reviser
}; // ast
