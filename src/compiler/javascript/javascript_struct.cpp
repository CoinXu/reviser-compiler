/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_struct.h>
#include <compiler/javascript/javascript_expr.h>
#include <compiler/javascript/javascript_enum.h>
#include <compiler/javascript/javascript_common.h>

namespace reviser {
namespace compiler {
  //
  // JavaScriptStruct
  JavaScriptStruct::JavaScriptStruct(Struct* node): node(node) {
    node->level = 0;
  }

  JavaScriptStruct::JavaScriptStruct(Struct* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
      node->level = parent->node->level + 1;
    }

  JavaScriptStruct::~JavaScriptStruct() {}

  string JavaScriptStruct::Generate() {
    string code;

    if (parent) {
      code = JavaScriptCommon::Indent(node->level)
        + "static class " + node->id.text + " \{\n";
    } else {
      code = JavaScriptCommon::Indent(node->level)
        + "class " + node->id.text + " \{\n";
    }

    for (Struct::ContentStore& p: node->contents) {

      const string new_line = &p == &node->contents.back() ? "\n" : "\n\n";

      switch (p.type) {
        case DeclareProperty: {
          JavaScriptStructProperty g(&(node->properties.at(p.index)), this);
          code = code + g.Generate() + new_line;
          break;
        }

        case DeclareStruct: {
          JavaScriptStruct g(&(node->structs.at(p.index)), this);
          code = code + g.Generate() + new_line;
          break;
        }

        case DeclareEnum: {
          JavaScriptEnum g(&(node->enums.at(p.index)), this);
          code = code + g.Generate() + new_line;
          break;
        }

        default:
          break;
      }
    }

    return code + JavaScriptCommon::Indent(node->level) + "};\n";
  }

  //
  // JavaScriptStructProperty
  JavaScriptStructProperty::JavaScriptStructProperty(StructProperty* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
      node->level = parent->node->level + 1;
    }

  JavaScriptStructProperty::~JavaScriptStructProperty() {}

  string JavaScriptStructProperty::Generate() {
    string code;

    for (Decorater d: node->decoraters) {
      JavaScriptDecorater decorater(&d, parent);
      code = code + decorater.Generate();
    }

    JavaScriptDeclare declare(&node->declare);
    return code + JavaScriptCommon::Indent(node->level)
      + declare.Generate() + ";";
  }

  //
  // JavaScriptDecorater
  JavaScriptDecorater::JavaScriptDecorater(Decorater* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
      node->level = parent->node->level + 1;
    }

  JavaScriptDecorater::~JavaScriptDecorater() {}

  string JavaScriptDecorater::Generate() {
    return JavaScriptCommon::Indent(node->level)
      + "@" + node->id.text + "\n";
  }

}; // reviser
}; // compiler
