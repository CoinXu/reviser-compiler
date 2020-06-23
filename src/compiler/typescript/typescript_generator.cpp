/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/typescript/typescript_generator.h>

namespace reviser {
namespace compiler {

  TypeScriptGenerator::TypeScriptGenerator() {}

  TypeScriptGenerator::~TypeScriptGenerator() {}

  string TypeScriptGenerator::StmtStruct(Struct* s) {
    return "typescript struct";
  }

  string TypeScriptGenerator::StmtEnum(Enum* e) {
    return "typescript enum";
  }

}; // compiler
}; // reviser
