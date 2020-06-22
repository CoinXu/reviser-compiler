/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_struct.h>
#include <compiler/javascript/javascript_enum.h>
#include <compiler/javascript/javascript_common.h>

namespace reviser {
namespace compiler {
  //
  // JavaScriptStruct
  JavaScriptStruct::JavaScriptStruct(Struct* node): node(node) {}
  JavaScriptStruct::JavaScriptStruct(Struct* node, JavaScriptStmt* parent)
    : node(node), parent(parent) {}

  string JavaScriptStruct::Generate() {
    string code;

    if (parent != NULL) {
      code = JavaScriptCommon::Indent(parent->node->level + 1)
        + "static class " + node->id.text + " \{\n";
    } else {
      code = JavaScriptCommon::Indent(node->level)
        + "class " + node->id.text + " \{\n";
    }

    for (Struct::ContentStore p: node->contents) {
      switch (p.type) {
        case DeclareProperty: {
          JavaScriptStructProperty g(&(node->properties.at(p.index)), this);
          code = code + g.Generate();
          break;
        }

        case DeclareStruct: {
          JavaScriptStruct g(&(node->structs.at(p.index)), this);
          code = code + g.Generate();
          break;
        }

        case DeclareEnum: {
          JavaScriptEnum g(&(node->enums.at(p.index)), this);
          code = code + g.Generate();
          break;
        }

        default:
          break;
      }
    }

    return code + "\n};"
  }
}; // reviser
}; // compiler
