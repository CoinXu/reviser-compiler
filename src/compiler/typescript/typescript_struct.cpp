/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/typescript/typescript_struct.h>
#include <compiler/typescript/typescript_expr.h>
#include <compiler/typescript/typescript_enum.h>
#include <compiler/typescript/typescript_common.h>

namespace reviser {
namespace compiler {
  //
  // TypeScriptStruct
  TypeScriptStruct::TypeScriptStruct(Struct* node): node(node) {
    node->level = 0;
  }

  TypeScriptStruct::TypeScriptStruct(Struct* node, TypeScriptStruct* parent)
    : node(node), parent(parent) {
      node->level = parent->node->level + 1;
    }

  TypeScriptStruct::~TypeScriptStruct() {
  }

  string TypeScriptStruct::Generate() {
    string indent = TypeScriptCommon::Indent(node->level);
    string indent_next = TypeScriptCommon::Indent(node->level + 1);

    vector<string> properties;
    vector<string> structures;
    vector<string> enums;

    for (Struct::ContentStore& p: node->contents) {
      const string new_line = &p == &node->contents.back() ? "\n" : "\n\n";

      switch (p.type) {
        case DeclareProperty: {
          TypeScriptStructProperty g(node->properties.at(p.index), this);
          properties.push_back(g.Generate() + new_line);
          break;
        }

        case DeclareStruct: {
          TypeScriptStruct g(node->structs.at(p.index), this);
          structures.push_back(g.Generate() + new_line);
          break;
        }

        case DeclareEnum: {
          TypeScriptEnum g(node->enums.at(p.index), this);
          enums.push_back(g.Generate() + new_line);
          break;
        }

        default:
          break;
      }
    }

    string code = indent + "const " + node->id->text + " = (function() {\n";

    for (string en: enums) {
      code = code + en;
    }

    for (string s: structures) {
      code = code + s;
    }

    code = code + indent_next + "class " + node->id->text + " extends Reviser {\n";

    for (string p: properties) {
      code = code + p;
    }

    code = code + indent_next + "}\n";

    return code
      + indent_next + "return " + node->id->text + ";\n"
      + indent + "})();\n";
  }

  //
  // TypeScriptStructProperty
  TypeScriptStructProperty::TypeScriptStructProperty(StructProperty* node, TypeScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  TypeScriptStructProperty::~TypeScriptStructProperty() {
  }

  string TypeScriptStructProperty::Generate() {
    string code;

    for (Decorater* d: node->decoraters) {
      TypeScriptDecorater decorater(d, parent);
      code = code + decorater.Generate();
    }

    string type;
    if (TypeScriptDataTypeDecoraterNameMap.find(node->declare->type) != TypeScriptDataTypeDecoraterNameMap.end()) {
      type += TypeScriptCommon::Indent(node->level + 1) + "@" + TypeScriptDataTypeDecoraterNameMap.at(node->declare->type) + "\n";
    }

    TypeScriptDeclare declare(node->declare);
    return code + type + TypeScriptCommon::Indent(node->level + 1) + declare.Generate() + ";";
  }

  //
  // TypeScriptDecorater
  TypeScriptDecorater::TypeScriptDecorater(Decorater* node, TypeScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  TypeScriptDecorater::~TypeScriptDecorater() {
  }

  string TypeScriptDecorater::Generate() {
    if (TypeScriptDecoraterNameMap.find(node->id->text) == TypeScriptDecoraterNameMap.end()) {
      return "";
    }

    return TypeScriptCommon::Indent(node->level + 1)
      + "@" + TypeScriptDecoraterNameMap.at(node->id->text) + "\n";
  }

}; // reviser
}; // compiler
