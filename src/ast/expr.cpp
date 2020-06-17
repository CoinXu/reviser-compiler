
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
  // Expr
  string Expr::generate() {
    return "";
  }

  // DataValue
  DataValue::DataValue(DataValueType type, Token id)
    : type(type), id(id) {}

  string DataValue::generate() {
    return id.text;
  }

  //
  // EnumValue
  EnumValue::EnumValue(Token id, Token property)
    : id(id), property(property) {}

  string EnumValue::generate() {
    return id.text + "." + property.text;
  }

  // Assign
  Assign::Assign(Token id, DataValue value): id(id), value(value) {}

  string Assign::generate() {
    // TODO check value by data type
    return id.text + " = " + value.generate();
  }

  // Declare
  Token DefaultToken;
  EnumValue DefaultEnumValue(DefaultToken, DefaultToken);
  DataValue DefaultDataValue(DataTypeBoolean, DefaultToken);

  Declare::Declare(DataValueType type, Token id, DataValue dv)
    : type(type), id(id), eid(DefaultToken), dv(dv), ev(DefaultEnumValue) {}

  Declare::Declare(DataValueType type, Token id, Token eid, EnumValue ev)
    : type(type), id(id), eid(eid), dv(DefaultDataValue), ev(ev) {}


  string Declare::generate() {
    string name;

    switch (type) {
      case DataTypeBoolean:
        name = ReservedWordMap[ReservedWordTypeBoolean];
        break;

      case DataTypeFloat:
        name = ReservedWordMap[ReservedWordTypeFloat];
        break;

      case DataTypeDouble:
        name = ReservedWordMap[ReservedWordTypeDouble];
        break;

      case DataTypeInt32:
        name = ReservedWordMap[ReservedWordTypeInt32];
        break;

      case DataTypeInt64:
        name = ReservedWordMap[ReservedWordTypeInt64];
        break;

      case DataTypeUint32:
        name = ReservedWordMap[ReservedWordTypeUint32];
        break;

      case DataTypeUint64:
        name = ReservedWordMap[ReservedWordTypeUint64];
        break;

      case DataTypeEnum:
        name = eid.text;
        break;

      default:
        name = "";
    }

    return name + " " + id.text + " "
      + (type == DataTypeEnum ?  ev.generate() : dv.generate());
  }

}; // reviser
}; // ast
