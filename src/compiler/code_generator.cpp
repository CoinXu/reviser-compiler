/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/code_generator.h>

namespace reviser {
namespace compiler {

  CodeGenerator::CodeGenerator(): descriptor(new Descriptor()) {}

  CodeGenerator::~CodeGenerator() {
    delete descriptor;
  }

  void CodeGenerator::AddStmtEnum(Enum* stmt) {
    seq.push_back({ STMT_TYPE_ENUM, enums.size() });
    enums.push_back(stmt);
  }

  void CodeGenerator::AddStmtStruct(Struct* stmt) {
    seq.push_back({ STMT_TYPE_STRUCT, structures.size() });
    structures.push_back(stmt);
  }

  string CodeGenerator::Generate() {
    string code;

    for (StmtSeqItem it: seq) {
      switch(it.type) {
        case STMT_TYPE_STRUCT:
          code += StmtStruct(structures.at(it.index));
          break;

        case STMT_TYPE_ENUM:
          code += StmtEnum(enums.at(it.index));
          break;

        default:
          break;
      }
    }

    return code;
  }

  string CodeGenerator::StmtStruct(Struct* s) {
    delete s;
    return "struct";
  }

  string CodeGenerator::StmtEnum(Enum* e) {
    delete e;
    return "enum";
  }
}; // reviser
}; // compiler
