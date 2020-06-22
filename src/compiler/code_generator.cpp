/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/code_generator.h>
#include <compiler/javascript/javascript_generator.h>

namespace reviser {
namespace compiler {

  CodeGenerator::CodeGenerator() {}

  CodeGenerator::~CodeGenerator() {}

  string CodeGenerator::StmtStruct(Struct* s) {
    return "struct";
  }

  string CodeGenerator::StmtEnum(Enum* e) {
    return "enum";
  }
}; // reviser
}; // compiler
