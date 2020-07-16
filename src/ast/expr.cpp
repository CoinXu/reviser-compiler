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

  // RightValue
  RightValue::RightValue(DataType type, Token* id, bool array_type)
    : type(type), id(id), array_type(array_type) {}

  RightValue::RightValue(StructValue* sv, bool array_type)
    : sv(sv), type(TYPE_STRUCT), array_type(array_type) {}

  RightValue::RightValue(EnumValue* ev, bool array_type)
    : ev(ev), type(TYPE_ENUM), array_type(array_type) {}

  RightValue::~RightValue() {
  }

  // StructValue
  StructValue::StructValue(Token* id, Token* value): id(id), value(value) {}
  StructValue::~StructValue() {
  }

  // EnumValue
  EnumValue::EnumValue(Token* id, Token* property)
    : id(id), property(property) {}

  EnumValue::~EnumValue() {
  }

  // Assign
  Assign::Assign(Token* id, RightValue* value): id(id), value(value) {}

  Assign::~Assign() {
  }

  // Declare
  Declare::Declare(DataType type, Token* id, RightValue* rv, bool array_type)
    : type(type), id(id), rv(rv), array_type(array_type) {}

  Declare::Declare(DataType type, Token* id, Token* type_id, RightValue* rv, bool array_type)
    : type(type), id(id), type_id(type_id), rv(rv), array_type(array_type) {}

  Declare::~Declare() {
  }

}; // reviser
}; // ast
