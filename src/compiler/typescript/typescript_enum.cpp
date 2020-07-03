/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/typescript/typescript_enum.h>
#include <compiler/typescript/typescript_common.h>

using namespace std;

namespace reviser {
namespace compiler {
  //
  // TypeScriptEnum
  TypeScriptEnum::TypeScriptEnum(Enum* node): node(node) {
    node->level = 0;
  }

  TypeScriptEnum::TypeScriptEnum(Enum* node, TypeScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  TypeScriptEnum::~TypeScriptEnum() {
    if (!destroyed) {
      destroyed = true;
    }
  }

  string TypeScriptEnum::Generate() {
    string code;

    code = TypeScriptCommon::Indent(node->level)
      + "enum " + node->id->text + " {\n";

    size_t counter = 0;
    size_t total = node->properties.size();

    for (EnumProperty* p: node->properties) {
      TypeScriptEnumProperty property(p, this);
      counter++;
      code  = code + property.Generate(counter) + (counter >= total ? "\n" : ",\n");
    }

    return code + TypeScriptCommon::Indent(node->level) + "};";
  }

  //
  // TypeScriptEnumProperty
  TypeScriptEnumProperty::TypeScriptEnumProperty(EnumProperty* node, TypeScriptEnum* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  TypeScriptEnumProperty::~TypeScriptEnumProperty() {
    if (!destroyed) {
      destroyed = true;
    }
  }

  string TypeScriptEnumProperty::Generate(int index) {
    string indent = TypeScriptCommon::Indent(node->level);
    string value = !node->value ? "" : (" = " + node->value->id->text);

    return indent + node->id->text + value;
  }

};
};
