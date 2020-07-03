/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_TYPESCRIPT_STMT
#define REVISER_COMPILER_TYPESCRIPT_STMT

#include <ast/stmt.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
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
