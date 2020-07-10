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
  }

  string JavaScriptStruct::Generate() {
    string indent = JavaScriptCommon::Indent(node->level);
    string indent_next = JavaScriptCommon::Indent(node->level + 1);

    vector<string> properties;
    vector<string> structures;
    vector<string> enums;

    for (vector<Struct::ContentStore>::iterator it = begin(node->contents);
      it != end(node->contents); it++) {
      const string new_line = next(it) == end(node->contents) ? "\n" : "\n\n";

      switch ((*it).type) {
        case DeclareProperty: {
          JavaScriptStructProperty g(node->properties.at((*it).index), this);
          properties.push_back(g.Generate() + new_line);
          break;
        }

        case DeclareStruct: {
          JavaScriptStruct g(node->structs.at((*it).index), this);
          structures.push_back(g.Generate() + new_line);
          break;
        }

        case DeclareEnum: {
          JavaScriptEnum g(node->enums.at((*it).index), this);
          enums.push_back(g.Generate() + new_line);
          break;
        }

        default:
          break;
      }
    }

    string ns =  indent + "namespace Class" + node->id->text + " {\n";
    for (string en: enums) {
      ns = ns + en;
    }

    for (string s: structures) {
      ns = ns + s;
    }
    ns += "\n}";

    string code = indent + "class " + node->id->text + " extends Reviser {\n";
    for (string p: properties) {
      code = code + p;
    }
    code = code + indent + "}\n";

    return ns + "\n\n" + code + "\n";
  }

  //
  // JavaScriptStructProperty
  JavaScriptStructProperty::JavaScriptStructProperty(StructProperty* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  JavaScriptStructProperty::~JavaScriptStructProperty() {
  }

  string JavaScriptStructProperty::Generate() {
    string code;

    for (Decorater* d: node->decoraters) {
      JavaScriptDecorater decorater(d, parent);
      code = code + decorater.Generate();
    }

    string type;
    if (JavaScriptDataTypeDecoraterNameMap.find(node->declare->type) != JavaScriptDataTypeDecoraterNameMap.end()) {
      type += JavaScriptCommon::Indent(node->level + 1) + "@" + JavaScriptDataTypeDecoraterNameMap.at(node->declare->type) + "\n";
    }

    JavaScriptDeclare declare(node->declare);
    return code + type + JavaScriptCommon::Indent(node->level + 1) + declare.Generate() + ";";
  }

  //
  // JavaScriptDecorater
  JavaScriptDecorater::JavaScriptDecorater(Decorater* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  JavaScriptDecorater::~JavaScriptDecorater() {
  }

  string JavaScriptDecorater::Generate() {
    if (JavaScriptDecoraterNameMap.find(node->id->text) == JavaScriptDecoraterNameMap.end()) {
      return "";
    }

    return JavaScriptCommon::Indent(node->level + 1)
      + "@" + JavaScriptDecoraterNameMap.at(node->id->text) + "\n";
  }

}; // reviser
}; // compiler
