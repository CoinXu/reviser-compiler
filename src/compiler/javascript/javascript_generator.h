/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_JAVASCRIPT_GENERATOR
#define REVISER_JAVASCRIPT_GENERATOR

#include <compiler/code_generator.h>

using namespace reviser::message;
using namespace reviser::compiler;

namespace reviser {
namespace javascript {

  class JavaScriptGenerator : public CodeGenerator {
  private:
    string Import();
    string Export();
    Message message; 

  public:
    string StmtStruct(Struct*);
    string StmtEnum(Enum*);
    string Generate();

    JavaScriptGenerator();
    ~JavaScriptGenerator();
  };
}; // compiler
}; // reviser

#endif
