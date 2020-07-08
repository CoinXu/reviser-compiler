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
    string def_interface("interface Struct" + node->id->text + " {\n");

    vector<string> inters;
    vector<string> properties;
    vector<string> structures;
    vector<string> enums;

    for (vector<Struct::ContentStore>::iterator it = begin(node->contents);
      it != end(node->contents); it++) {
      const string new_line = next(it) == end(node->contents) ? "\n" : "\n\n";

      switch ((*it).type) {
        case DeclareProperty: {
          TypeScriptStructProperty g(node->properties.at((*it).index), this);
          properties.push_back(g.Generate() + new_line);

          TypeScriptStructInterfaceProperty i(node->properties.at((*it).index), this);
          inters.push_back(i.Generate() + "\n");
          break;
        }

        case DeclareStruct: {
          TypeScriptStruct g(node->structs.at((*it).index), this);
          structures.push_back(g.Generate() + new_line);
          break;
        }

        case DeclareEnum: {
          TypeScriptEnum g(node->enums.at((*it).index), this);
          enums.push_back(g.Generate() + new_line);
          break;
        }

        default:
          break;
      }
    }

    string code = indent + "interface Struct" + node->id->text + " {\n";
    for (string i : inters) {
      code = code + i;
    }
    code = code + indent + "};\n\n";

    code = code + indent + "const " + node->id->text + " = (function() {\n";
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
    if (TypeScriptDataTypeTranslatorNameMap.find(node->declare->type) != TypeScriptDataTypeTranslatorNameMap.end()) {
      type += TypeScriptCommon::Indent(node->level + 1) + "@" + TypeScriptDataTypeTranslatorNameMap.at(node->declare->type) + "\n";
    }

    if (TypeScriptDataTypeDecoraterNameMap.find(node->declare->type) != TypeScriptDataTypeDecoraterNameMap.end()) {
      type += TypeScriptCommon::Indent(node->level + 1) + "@" + TypeScriptDataTypeDecoraterNameMap.at(node->declare->type) + "\n";
    }

    TypeScriptDeclare declare(node->declare);
    return type + code + TypeScriptCommon::Indent(node->level + 1) + declare.Generate() + ";";
  }

  //
  // TypeScriptStructInterfaceProperty
  TypeScriptStructInterfaceProperty::TypeScriptStructInterfaceProperty(StructProperty* node, TypeScriptStruct* parent)
    : node(node), parent(parent) {
      node->level = parent->node->level + 1;
    }

  TypeScriptStructInterfaceProperty::~TypeScriptStructInterfaceProperty() {}

  string TypeScriptStructInterfaceProperty::Generate() {
    if (node->declare->type == TYPE_ENUM) {
      return TypeScriptCommon::Indent(node->level)
        + node->declare->id->text + ": " + node->declare->eid->text
        + "; /* enum " + node->declare->eid->text + " */";
    }

    string type;
    if (TypeScriptDataTypeMap.find(node->declare->type) == TypeScriptDataTypeMap.end()) {
      type = "any";
    } else {
      type = TypeScriptDataTypeMap.at(node->declare->type);
    }

    return TypeScriptCommon::Indent(node->level)
      + node->declare->id->text + ": " + type
      + "; /* " + DataTypeName.at(node->declare->type) + " */";
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
