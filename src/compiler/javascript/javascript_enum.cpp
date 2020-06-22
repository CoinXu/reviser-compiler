/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_enum.h>
#include <compiler/javascript/javascript_common.h>

using namespace std;

namespace reviser {
namespace compiler {
  //
  // JavaScriptEnum
  JavaScriptEnum::JavaScriptEnum(Enum* node): node(node) {}
  JavaScriptEnum::JavaScriptEnum(Enum* node, JavaScriptStmt* parent)
    : node(node), parent(parent) {}

  JavaScriptEnum::~JavaScriptEnum() {}

  string JavaScriptEnum::Generate() {
    string code;

    if (parent != NULL) {
      code = JavaScriptCommon::Indent(parent->node->level + 1)
        + "static " + node->id.text + " = {\n";
    } else {
      code = JavaScriptCommon::Indent(node->level) + "var " + node->id.text
        + " = {\n";
    }

    size_t counter = 0;
    size_t total = node->properties.size();

    for (EnumProperty p: node->properties) {
      JavaScriptEnumProperty property(&p, this);
      counter++;
      code  = code + property.Generate(counter) + (counter >= total ? "" : ",\n");
    }

    return code + "\n};";
  }

  //
  // JavaScriptEnumProperty
  JavaScriptEnumProperty::JavaScriptEnumProperty(EnumProperty* node, JavaScriptEnum* parent)
    : node(node), parent(parent) {}

  JavaScriptEnumProperty::~JavaScriptEnumProperty() {}

  string JavaScriptEnumProperty::Generate(int index) {
    return JavaScriptCommon::Indent(parent->node->level + 1)+ node->id.text + " = "
      + (node->value.type == TYPE_NULL ? to_string(index) : node->value.id.text);
  }

};
};
