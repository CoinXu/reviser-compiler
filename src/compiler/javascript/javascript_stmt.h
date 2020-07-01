/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_JAVASCRIPT_STMT
#define REVISER_COMPILER_JAVASCRIPT_STMT

#include <ast/stmt.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
  class JavaScriptStmt {
  public:
    Stmt* node;
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
