/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/typescript/typescript_expr.h>
#include <compiler/typescript/typescript_common.h>

namespace reviser {
namespace compiler {
  //
  // TypeScriptRightValue
  TypeScriptRightValue::TypeScriptRightValue(RightValue* node): node(node) {}

  TypeScriptRightValue::~TypeScriptRightValue() {
  }

  string TypeScriptRightValue::Generate() {
    return node->id->text;
  }

  //
  // TypeScriptEnumValue
  TypeScriptEnumValue::TypeScriptEnumValue(EnumValue* node): node(node) {};

  TypeScriptEnumValue::~TypeScriptEnumValue() {
  }

  string TypeScriptEnumValue::Generate() {
    return node->id->text + "." + node->property->text;
  }

  //
  // TypeScriptAssign
  TypeScriptAssign::TypeScriptAssign(Assign* node): node(node) {}

  TypeScriptAssign::~TypeScriptAssign() {
  }

  string TypeScriptAssign::Generate() {
    TypeScriptRightValue rv(node->value);
    return node->id->text + " = " + rv.Generate();
  }

  //
  // TypeScriptDeclare
  TypeScriptDeclare::TypeScriptDeclare(Declare* node): node(node) {}

  TypeScriptDeclare::~TypeScriptDeclare() {
  }

  string TypeScriptDeclare::Generate() {
    string value;

    if (node->type == TYPE_ENUM) {
      TypeScriptEnumValue ev(node->ev);
      value = ev.Generate();
    } else {
      TypeScriptRightValue rv(node->dv);
      value = rv.Generate();
    }

    string type;
    if (node->type == TYPE_ENUM) {
      type = node->ev->id->text;
    } else if (TypeScriptDataTypeMap.find(node->type) != TypeScriptDataTypeMap.end()) {
      type = TypeScriptDataTypeMap[node->type];
    } else {
      type = "any";
    }

    return "public " + node->id->text + ": " + type + " = " + value;
  }
}; // reviser
}; // compiler
