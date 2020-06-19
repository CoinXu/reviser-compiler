
/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#include <ast/expr.h>
#include <tokenizer.h>

using namespace std;

namespace reviser {
namespace ast {
  // AstExpr
  string AstExpr::generate() {
    return "";
  }

  // AstRightValue
  AstRightValue::AstRightValue(DataValueType type, Token id)
    : type(type), id(id) {}

  DataValueType AstRightValue::DataType() {
    return type;
  }

  string AstRightValue::generate() {
    return id.text;
  }

  //
  // AstEnumValue
  AstEnumValue::AstEnumValue(Token id, Token property)
    : id(id), property(property) {}

  string AstEnumValue::generate() {
    return id.text + "." + property.text;
  }

  // AstAssign
  AstAssign::AstAssign(Token id, AstRightValue value): id(id), value(value) {}

  string AstAssign::generate() {
    // TODO check value by data type
    return id.text + " = " + value.generate();
  }

  // AstDeclare
  AstDeclare::AstDeclare(DataValueType type, Token id, AstRightValue dv)
    : type(type), id(id), eid(EmptyToken), dv(dv) {}

  AstDeclare::AstDeclare(DataValueType type, Token id, Token eid, AstEnumValue ev)
    : type(type), id(id), eid(eid), ev(ev) {}


  string AstDeclare::generate() {
    string type_name;

    switch (type) {
      case DataTypeBoolean:
        type_name = ReservedWordMap[ReservedWordTypeBoolean];
        break;

      case DataTypeFloat:
        type_name = ReservedWordMap[ReservedWordTypeFloat];
        break;

      case DataTypeDouble:
        type_name = ReservedWordMap[ReservedWordTypeDouble];
        break;

      case DataTypeInt32:
        type_name = ReservedWordMap[ReservedWordTypeInt32];
        break;

      case DataTypeInt64:
        type_name = ReservedWordMap[ReservedWordTypeInt64];
        break;

      case DataTypeUint32:
        type_name = ReservedWordMap[ReservedWordTypeUint32];
        break;

      case DataTypeUint64:
        type_name = ReservedWordMap[ReservedWordTypeUint64];
        break;

      case DataTypeString:
        type_name = ReservedWordMap[ReservedWordTypeString];
        break;

      case DataTypeEnum:
        type_name = eid.text;
        break;

      default:
        type_name = "";
    }

    return type_name + " " + id.text + " = "
      + (type == DataTypeEnum ?  ev.generate() : dv.generate());
  }

}; // reviser
}; // ast
