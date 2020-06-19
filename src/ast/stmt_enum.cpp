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
  // AstEnumProperty
  AstEnumProperty::AstEnumProperty(Token id, AstRightValue value)
    : id(id), value(value) {}

  AstEnumProperty::AstEnumProperty(Token id): id(id) {}

  string AstEnumProperty::generate() {
    return id.text + (value.DataType() != DataTypeNull
      ? (" = " + value.generate())
      : "");
  }

  //
  // AstEnum
  AstEnum::AstEnum(Token id): id(id) {}

  void AstEnum::AddProperty(AstEnumProperty property) {
    properties.push_back(property);
  }

  string AstEnum::generate() {
    string code = "enum " + id.text + " {\n";
    size_t total = properties.size();
    size_t counter = 1;

    for (AstEnumProperty p: properties) {
      code = code + "  " + p.generate() + (counter++ >= total ? "" : ",\n");
    }
    return code + "\n}";
  }

}; // reviser
}; // ast
