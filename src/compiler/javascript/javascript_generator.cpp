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

  JavaScriptGenerator::JavaScriptGenerator() {}

  JavaScriptGenerator::~JavaScriptGenerator() {}

  string JavaScriptGenerator::StmtStruct(Struct* s) {
    JavaScriptStruct g(s);
    return g.Generate();
  }

  string JavaScriptGenerator::StmtEnum(Enum* e) {
    JavaScriptEnum g(e);
    return g.Generate();
  }

}; // javascript
}; // compiler
