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
  EnumProperty::EnumProperty(Token id, RightValue value)
    : id(id), value(value) {}

  EnumProperty::EnumProperty(Token id): id(id) {}

  string EnumProperty::generate() {
    return id.text + (value.TOKEN_DATA_TYPE() != TYPE_NULL
      ? (" = " + value.generate())
      : "");
  }

  //
  // Enum
  Enum::Enum(Token id): id(id) {}

  void Enum::AddProperty(EnumProperty property) {
    properties.push_back(property);
  }

  string Enum::generate() {
    string code = "enum " + id.text + " {\n";
    size_t total = properties.size();
    size_t counter = 1;

    for (EnumProperty p: properties) {
      code = code + "  " + p.generate() + (counter++ >= total ? "" : ",\n");
    }
    return code + "\n}";
  }

}; // reviser
}; // ast
