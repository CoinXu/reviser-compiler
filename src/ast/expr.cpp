
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

  DataValueType DataValue::DataType() {
    return type;
  }

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
  Declare::Declare(DataValueType type, Token id, DataValue dv)
    : type(type), id(id), eid(EmptyToken), dv(dv) {}

  Declare::Declare(DataValueType type, Token id, Token eid, EnumValue ev)
    : type(type), id(id), eid(eid), ev(ev) {}


  string Declare::generate() {
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
