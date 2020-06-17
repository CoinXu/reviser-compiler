
/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#include <ast/stmt.h>
#include <message.h>

namespace reviser {
namespace ast {
  std::string Stmt::generate() {
    message::Message message("code");
    std::vector<Stmt>::iterator it;

    for (it = stmts.begin(); it != stmts.end(); it++) {
      message.Info((*it).generate());
    }
  };

  void Stmt::AddStmt(Stmt stmt) {
    stmts.push_back(stmt);
  }
}; // reviser
}; // ast
