/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_generator.h>
#include <compiler/javascript/javascript_common.h>
#include <compiler/javascript/javascript_enum.h>

namespace reviser {
namespace compiler {

  JavaScriptGenerator::JavaScriptGenerator() {}

  JavaScriptGenerator::~JavaScriptGenerator() {}

  string JavaScriptGenerator::StmtStruct(Struct* s) {
    return "";
  }

  string JavaScriptGenerator::StmtEnum(Enum* e) {
    JavaScriptEnum je(e);
    return je.Generate();
  }

}; // javascript
}; // compiler
