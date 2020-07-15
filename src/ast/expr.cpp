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
  RightValue::RightValue(DataType type, Token* id)
    : type(type), id(id) {}

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
  Declare::Declare(DataType type, Token* id, RightValue* dv)
    : type(type), id(id), eid(nullptr), dv(dv), ev(nullptr) {}

  Declare::Declare(DataType type, Token* id, Token* eid, EnumValue* ev)
    : type(type), id(id), eid(eid), dv(nullptr), ev(ev) {}

  Declare::Declare(DataType type, Token* id)
    : type(type), id(id), array_type(true) {}

  Declare::Declare(Token* id, StructValue* sv): id(id), type(TYPE_STRUCT), sv(sv) {}

  Declare::~Declare() {
  }

}; // reviser
}; // ast
