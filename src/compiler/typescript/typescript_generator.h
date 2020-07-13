/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_TYPESCRIPT_GENERATOR
#define REVISER_TYPESCRIPT_GENERATOR

#include <compiler/code_generator.h>

using namespace reviser::message;
using namespace reviser::compiler;

namespace reviser {
namespace typescript {

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
