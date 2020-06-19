
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
  string Expr::Generate() {
    return "";
  }

  // RightValue
  RightValue::RightValue(DataType type, Token id)
    : type(type), id(id) {}

  DataType RightValue::Type() {
    return type;
  }

  string RightValue::Generate() {
    return id.text;
  }

  //
  // EnumValue
  EnumValue::EnumValue(Token id, Token property)
    : id(id), property(property) {}

  string EnumValue::Generate() {
    return id.text + "." + property.text;
  }

  // Assign
  Assign::Assign(Token id, RightValue value): id(id), value(value) {}

  string Assign::Generate() {
    // TODO check value by data type
    return id.text + " = " + value.Generate();
  }

  // Declare
  Declare::Declare(DataType type, Token id, RightValue dv)
    : type(type), id(id), eid(EmptyToken), dv(dv) {}

  Declare::Declare(DataType type, Token id, Token eid, EnumValue ev)
    : type(type), id(id), eid(eid), ev(ev) {}


  string Declare::Generate() {
    string type_name;

    switch (type) {
      case TYPE_BOOL:
        type_name = ReservedWordMap[RESERVED_BOOL];
        break;

      case TYPE_FLOAT:
        type_name = ReservedWordMap[RESERVED_FLOAT];
        break;

      case TYPE_DOUBLE:
        type_name = ReservedWordMap[RESERVED_DOUBLE];
        break;

      case TYPE_INT32:
        type_name = ReservedWordMap[RESERVED_INT32];
        break;

      case TYPE_INT64:
        type_name = ReservedWordMap[RESERVED_INT64];
        break;

      case TYPE_UINT32:
        type_name = ReservedWordMap[RESERVED_UINT32];
        break;

      case TYPE_UINT64:
        type_name = ReservedWordMap[RESERVED_UINT64];
        break;

      case TYPE_STRING:
        type_name = ReservedWordMap[RESERVED_STRING];
        break;

      case TYPE_ENUM:
        type_name = eid.text;
        break;

      default:
        type_name = "";
    }

    return type_name + " " + id.text + " = "
      + (type == TYPE_ENUM ?  ev.Generate() : dv.Generate());
  }

}; // reviser
}; // ast
