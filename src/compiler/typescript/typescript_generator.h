/**
 * @date 2020-06-23
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_TYPESCRIPT_GENERATOR
#define REVISER_COMPILER_TYPESCRIPT_GENERATOR

#include <compiler/code_generator.h>

namespace reviser {
namespace compiler {
  class TypeScriptGenerator : public CodeGenerator {
  public:
    string StmtStruct(Struct*);
    string StmtEnum(Enum*);

    TypeScriptGenerator();
    ~TypeScriptGenerator();
  };
}; // compiler
}; // reviser

#endif
