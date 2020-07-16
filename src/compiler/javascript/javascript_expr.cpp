/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_expr.h>

namespace reviser {
namespace javascript {
  //
  // JavaScriptRightValue
  JavaScriptRightValue::JavaScriptRightValue(RightValue* node): node(node) {}

  JavaScriptRightValue::~JavaScriptRightValue() {
  }

  string JavaScriptRightValue::Generate() {
    return node->id->text;
  }

  //
  // JavaScriptEnumValue
  JavaScriptEnumValue::JavaScriptEnumValue(EnumValue* node): node(node) {};

  JavaScriptEnumValue::~JavaScriptEnumValue() {
  }

  string JavaScriptEnumValue::Generate() {
    return node->id->text + "." + node->property->text;
  }

  //
  // JavaScriptAssign
  JavaScriptAssign::JavaScriptAssign(Assign* node): node(node) {}

  JavaScriptAssign::~JavaScriptAssign() {
  }

  string JavaScriptAssign::Generate() {
    JavaScriptRightValue rv(node->value);
    return node->id->text + " = " + rv.Generate();
  }

  //
  // JavaScriptDeclare
  JavaScriptDeclare::JavaScriptDeclare(Declare* node): node(node) {}

  JavaScriptDeclare::~JavaScriptDeclare() {
  }

  string JavaScriptDeclare::Generate() {
    return node->id->text + " = " + JavaScriptRightValue(node->rv).Generate();
  }
}; // reviser
}; // compiler
