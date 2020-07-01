/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_generator.h>
#include <compiler/javascript/javascript_common.h>
#include <compiler/javascript/javascript_enum.h>
#include <compiler/javascript/javascript_struct.h>

namespace reviser {
namespace compiler {

  JavaScriptGenerator::JavaScriptGenerator(): CodeGenerator() {}

  JavaScriptGenerator::~JavaScriptGenerator() {}

  string JavaScriptGenerator::StmtStruct(Struct* s) {
    JavaScriptStruct g(s);
    return g.Generate();
  }

  string JavaScriptGenerator::StmtEnum(Enum* e) {
    JavaScriptEnum g(e);
    return g.Generate();
  }

  string JavaScriptGenerator::Generate() {
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

    for (auto s : structures) {
      // delete s;
    }
    structures.clear();

    for (auto e : enums) {
      // delete e;
    }
    enums.clear();

    return code;
  }

}; // javascript
}; // compiler
