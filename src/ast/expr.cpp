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
    // delete id;
  }

  // EnumValue
  EnumValue::EnumValue(Token* id, Token* property)
    : id(id), property(property) {}

  EnumValue::~EnumValue() {
    // delete id;
    // delete property;
  }

  // Assign
  Assign::Assign(Token* id, RightValue* value): id(id), value(value) {}

  Assign::~Assign() {
    // delete id;
    // delete value;
  }

  // Declare
  Declare::Declare(DataType type, Token* id, RightValue* dv)
    : type(type), id(id), eid(NULL), dv(dv), ev(NULL) {}

  Declare::Declare(DataType type, Token* id, Token* eid, EnumValue* ev)
    : type(type), id(id), eid(eid), dv(NULL), ev(ev) {}

  Declare::~Declare() {
    // delete id;
    // delete eid;
    // delete dv;
    // delete ev;
  }

}; // reviser
}; // ast
