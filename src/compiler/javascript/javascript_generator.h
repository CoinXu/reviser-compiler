/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_JAVASCRIPT_GENERATOR
#define REVISER_COMPILER_JAVASCRIPT_GENERATOR

#include <compiler/code_generator.h>

namespace reviser {
namespace compiler {
  class JavaScriptGenerator : public CodeGenerator {
  public:
    string StmtStruct(Struct*);
    string StmtEnum(Enum*);

    JavaScriptGenerator();
    ~JavaScriptGenerator();
  };
}; // javascript
}; // reviser

#endif
