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
    return "struct";
  }

  string CodeGenerator::StmtEnum(Enum* e) {
    return "enum";
  }

  bool CodeGenerator::IncludeArrayType() {
    vector<Struct*> structs(structures.begin(), structures.end());

    for (Struct* s: structs) {
      for (StructProperty* p: s->properties) {
        if (p->declare->array_type) {
          return true;
        }
      }

      if (s->structs.size() > 0) {
        structs.insert(structs.end(), s->structs.begin(), s->structs.end());
      }
    }

    return false;
  }
}; // reviser
}; // compiler
