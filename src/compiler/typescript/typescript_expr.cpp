/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/typescript/typescript_expr.h>
#include <compiler/typescript/typescript_common.h>

namespace reviser {
namespace typescript {
  //
  // TypeScriptRightValue
  TypeScriptRightValue::TypeScriptRightValue(RightValue* node): node(node) {}

  TypeScriptRightValue::~TypeScriptRightValue() {
  }

  string TypeScriptRightValue::Generate() {
    if (node->array_type) {
      switch (node->type) {
        case TYPE_ENUM: {
          vector<string> values;
          for (EnumValue* v : node->evs) {
            values.push_back(TypeScriptEnumValue(v).Generate());
          }
          return "[" + TypeScriptCommon::JoinVector(values, ", ") + "]";
        }

        case TYPE_STRUCT:
          return TypeScriptStructValue(node->sv).Generate();

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
          return "[" + TypeScriptCommon::JoinVector(values, ", ") + "]";
        }

        case TYPE_STRING: {
          vector<string> values;
          for (Token* t : node->dvs) {
            values.push_back("\"" + t->text + "\"");
          }
          return "[" + TypeScriptCommon::JoinVector(values, ", ") + "]";
        }

        default:
          return "";
      }
    }

    switch (node->type) {
      case TYPE_ENUM:
        return TypeScriptEnumValue(node->ev).Generate();

      case TYPE_STRUCT:
        return TypeScriptStructValue(node->sv).Generate();

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
  // TypeScriptStructValue
  TypeScriptStructValue::TypeScriptStructValue(StructValue* node): node(node) {}

  TypeScriptStructValue::~TypeScriptStructValue() {}

  string TypeScriptStructValue::Generate() {
    if (node->value) {
      return "[]";
    }

    return "null";
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
  //   string value;

  //   // TODO support initial values
  //   if (node->array_type) {
  //     value = "[]";
  //   } else if (node->type == TYPE_ENUM) {
  //     TypeScriptEnumValue ev(node->ev);
  //     value = ev.Generate();
  //   } else if (node->type == TYPE_STRUCT) {
  //     value = node->sv->value ? node->sv->value->text : ReservedWordMap[RESERVED_NULL];
  //   } else {
  //     TypeScriptRightValue rv(node->dv);
  //     value = rv.Generate();
  //   }

    string type;

    switch (node->type) {
      case TYPE_ENUM:
        type = node->ev->id->text;
        break;

      case TYPE_STRUCT:
        type = node->sv->id->text;
        break;

      case TYPE_BOOL:
      case TYPE_FLOAT:
      case TYPE_DOUBLE:
      case TYPE_INT32:
      case TYPE_INT64:
      case TYPE_UINT32:
      case TYPE_UINT64:
      case TYPE_STRING:
        type = TypeScriptBuildInDataTypeMap[node->type];
        break;

      default:
        type = "any";
    }

    if (node->array_type) {
      type = type + "[]";
    }

    return "public "
      + node->id->text
      + ": " + type + " = "
      + TypeScriptRightValue(node->rv).Generate();
  }
}; // reviser
}; // compiler
