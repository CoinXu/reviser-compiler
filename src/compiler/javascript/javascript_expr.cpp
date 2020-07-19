/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_expr.h>
#include <compiler/javascript/javascript_common.h>

namespace reviser {
namespace javascript {
  //
  // JavaScriptRightValue
  JavaScriptRightValue::JavaScriptRightValue(RightValue* node): node(node) {}

  JavaScriptRightValue::~JavaScriptRightValue() {
  }

  string JavaScriptRightValue::Generate() {
    if (node->array_type) {
      switch (node->type) {
        case TYPE_ENUM: {
          vector<string> values;
          for (EnumValue* v : node->evs) {
            values.push_back(JavaScriptEnumValue(v).Generate());
          }
          return "[" + JavaScriptCommon::JoinVector(values, ", ") + "]";
        }

        case TYPE_STRUCT:
          return JavaScriptStructValue(node->sv).Generate();

        case TYPE_BOOL:
        case TYPE_FLOAT:
        case TYPE_DOUBLE:
        case TYPE_INT32:
        case TYPE_INT64:
        case TYPE_UINT32:
        case TYPE_UINT64: {
          vector<string> values;
          for (Token* t : node->dvs) {
            values.push_back(t->text);
          }
          return "[" + JavaScriptCommon::JoinVector(values, ", ") + "]";
        }

        case TYPE_STRING: {
          vector<string> values;
          for (Token* t : node->dvs) {
            values.push_back("\"" + t->text + "\"");
          }
          return "[" + JavaScriptCommon::JoinVector(values, ", ") + "]";
        }

        default:
          return "";
      }
    }

    switch (node->type) {
      case TYPE_ENUM:
        return JavaScriptEnumValue(node->ev).Generate();

      case TYPE_STRUCT:
        return JavaScriptStructValue(node->sv).Generate();

      case TYPE_BOOL:
      case TYPE_FLOAT:
      case TYPE_DOUBLE:
      case TYPE_INT32:
      case TYPE_INT64:
      case TYPE_UINT32:
      case TYPE_UINT64:
        return node->id->text;

      case TYPE_STRING:
        return "\"" + node->id->text + "\"";

      default:
        return "";
    }
  }

  //
  // JavaScriptStructValue
  JavaScriptStructValue::JavaScriptStructValue(StructValue* node): node(node) {}

  JavaScriptStructValue::~JavaScriptStructValue() {}

  string JavaScriptStructValue::Generate() {
    if (node->value) {
      return "[]";
    }

    return "null";
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
}; // javascript 
}; // reviser 
