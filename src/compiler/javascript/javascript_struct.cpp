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

  JavaScriptStruct::~JavaScriptStruct() {
    // delete node;
    // delete parent;
  }

  string JavaScriptStruct::Generate() {
    string indent = JavaScriptCommon::Indent(node->level);
    string indent_next = JavaScriptCommon::Indent(node->level + 1);

    vector<string> properties;
    vector<string> structures;
    vector<string> enums;

    for (Struct::ContentStore& p: node->contents) {
      const string new_line = &p == &node->contents.back() ? "\n" : "\n\n";

      switch (p.type) {
        case DeclareProperty: {
          JavaScriptStructProperty g(node->properties.at(p.index), this);
          properties.push_back(g.Generate() + new_line);
          break;
        }

        case DeclareStruct: {
          JavaScriptStruct g(node->structs.at(p.index), this);
          structures.push_back(g.Generate() + new_line);
          break;
        }

        case DeclareEnum: {
          JavaScriptEnum g(node->enums.at(p.index), this);
          enums.push_back(g.Generate() + new_line);
          break;
        }

        default:
          break;
      }
    }

    string code = indent + "var " + node->id->text + " = (function() {\n";

    for (string en: enums) {
      code = code + en;
    }

    for (string s: structures) {
      code = code + s;
    }

    code = code + indent_next + "class " + node->id->text + " {\n";

    for (string p: properties) {
      code = code + p;
    }

    code = code + indent_next + "}\n";

    return code
      + indent_next + "return " + node->id->text + ";\n"
      + indent + "})();\n";
  }

  //
  // JavaScriptStructProperty
  JavaScriptStructProperty::JavaScriptStructProperty(StructProperty* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  JavaScriptStructProperty::~JavaScriptStructProperty() {
    // delete node;
    // delete parent;
  }

  string JavaScriptStructProperty::Generate() {
    string code;

    for (Decorater* d: node->decoraters) {
      JavaScriptDecorater decorater(d, parent);
      code = code + decorater.Generate();
    }

    JavaScriptDeclare declare(node->declare);
    return code + JavaScriptCommon::Indent(node->level + 1)
      + declare.Generate() + ";";
  }

  //
  // JavaScriptDecorater
  JavaScriptDecorater::JavaScriptDecorater(Decorater* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  JavaScriptDecorater::~JavaScriptDecorater() {
    // delete node;
    // delete parent;
  }

  string JavaScriptDecorater::Generate() {
    return JavaScriptCommon::Indent(node->level + 1)
      + "@" + node->id->text + "\n";
  }

}; // reviser
}; // compiler
