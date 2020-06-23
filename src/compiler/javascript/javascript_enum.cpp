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
  JavaScriptEnum::JavaScriptEnum(Enum* node): node(node) {
    node->level = 0;
  }

  JavaScriptEnum::JavaScriptEnum(Enum* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  JavaScriptEnum::~JavaScriptEnum() {}

  string JavaScriptEnum::Generate() {
    string code;

    code = JavaScriptCommon::Indent(node->level)
      + "var " + node->id.text + " = {\n";

    size_t counter = 0;
    size_t total = node->properties.size();

    for (EnumProperty p: node->properties) {
      JavaScriptEnumProperty property(&p, this);
      counter++;
      code  = code + property.Generate(counter) + (counter >= total ? "\n" : ",\n");
    }

    return code + JavaScriptCommon::Indent(node->level) + "};";
  }

  //
  // JavaScriptEnumProperty
  JavaScriptEnumProperty::JavaScriptEnumProperty(EnumProperty* node, JavaScriptEnum* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  JavaScriptEnumProperty::~JavaScriptEnumProperty() {}

  string JavaScriptEnumProperty::Generate(int index) {
    return JavaScriptCommon::Indent(node->level)
      + node->id.text + ": "
      + (node->value.type == TYPE_NULL ? to_string(index) : node->value.id.text);
  }

};
};
