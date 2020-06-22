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
  };
};
};

#endif
