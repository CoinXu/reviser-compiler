/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_CODE_GENERATOR
#define REVISER_COMPILER_CODE_GENERATOR

#include <ast/expr.h>
#include <ast/stmt.h>
#include <ast/stmt_enum.h>
#include <ast/stmt_struct.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
  class CodeGenerator {
  public:
    string StmtStruct(Struct*);
    string StmtEnum(Enum*);

    CodeGenerator();
    ~CodeGenerator();
  };
};
};

#endif
