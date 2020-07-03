/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_TYPESCRIPT_GENERATOR
#define REVISER_COMPILER_TYPESCRIPT_GENERATOR

#include <compiler/code_generator.h>

using namespace reviser::message;

namespace reviser {
namespace compiler {

  class TypeScriptGenerator : public CodeGenerator {
  private:
    string Import();
    string Export();
    Message message;

  public:
    string StmtStruct(Struct*);
    string StmtEnum(Enum*);
    string Generate();

    TypeScriptGenerator();
    ~TypeScriptGenerator();
  };
}; // compiler
}; // reviser

#endif
