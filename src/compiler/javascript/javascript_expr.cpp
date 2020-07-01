/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_expr.h>

namespace reviser {
namespace compiler {
  //
  // JavaScriptRightValue
  JavaScriptRightValue::JavaScriptRightValue(RightValue* node): node(node) {}

  JavaScriptRightValue::~JavaScriptRightValue() {
    // delete node;
  }

  string JavaScriptRightValue::Generate() {
    return node->id->text;
  }

  //
  // JavaScriptEnumValue
  JavaScriptEnumValue::JavaScriptEnumValue(EnumValue* node): node(node) {};

  JavaScriptEnumValue::~JavaScriptEnumValue() {
    // delete node;
  }

  string JavaScriptEnumValue::Generate() {
    return node->id->text + "." + node->property->text;
  }

  //
  // JavaScriptAssign
  JavaScriptAssign::JavaScriptAssign(Assign* node): node(node) {}

  JavaScriptAssign::~JavaScriptAssign() {
    // delete node;
  }

  string JavaScriptAssign::Generate() {
    JavaScriptRightValue rv(node->value);
    return node->id->text + " = " + rv.Generate();
  }

  //
  // JavaScriptDeclare
  JavaScriptDeclare::JavaScriptDeclare(Declare* node): node(node) {}

  JavaScriptDeclare::~JavaScriptDeclare() {
    // delete node;
  }

  string JavaScriptDeclare::Generate() {
    string value;

    if (node->type == TYPE_ENUM) {
      JavaScriptEnumValue ev(node->ev);
      value = ev.Generate();
    } else {
      JavaScriptRightValue rv(node->dv);
      value = rv.Generate();
    }

    return node->id->text + " = " + value;
  }
}; // reviser
}; // compiler
