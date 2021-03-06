/**
 * @date 2020-06-18
 * @author duanxian0605@163.com
 * @description
 */

#include <ast/stmt_enum.h>

using namespace std;
using namespace reviser::compiler;

namespace reviser {
namespace ast {
  //
  // EnumProperty
  EnumProperty::EnumProperty(Token* id, RightValue* value)
    : id(id), value(value) {}

  EnumProperty::EnumProperty(Token* id): id(id) {}

  EnumProperty::~EnumProperty() {
    if (!destroyed) {
      destroyed = true;
    }
  }

  //
  // Enum
  Enum::Enum(Token* id): id(id) {}

  Enum::~Enum() {
    if (!destroyed) {
      destroyed = true;
    }
  }

}; // reviser
}; // ast
