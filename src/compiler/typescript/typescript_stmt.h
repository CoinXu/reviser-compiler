/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_TYPESCRIPT_STMT
#define REVISER_TYPESCRIPT_STMT

#include <ast/stmt.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace typescript {
  class TypeScriptStmt {
  public:
    Stmt* node = nullptr;
    Stmt* parent = nullptr;
    bool destroyed = false;

    bool DeclareInGlobalContext() {
      return node->level == 0;
    }

    string AccessName() {
      if (DeclareInGlobalContext()) {
        return node->name;
      }

      return parent->name + "." + node->name;
    }
  };
};
};

#endif
