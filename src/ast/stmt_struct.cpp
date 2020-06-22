/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#include <iterator>
#include <sstream>
#include <ast/stmt_struct.h>

using namespace std;

namespace reviser {
namespace ast {
  //
  // Decorater
  Decorater::Decorater(Token id): id(id) {}

  //
  // StructPrototype
  StructProperty::StructProperty(Declare declare)
    : declare(declare) {}

  //
  // Struct
  Struct::Struct(Token id, int level): id(id), level(level) {}

  void Struct::AddProperty(StructProperty property) {
    contents.push_back({ DeclareProperty, properties.size() });
    properties.push_back(property);
  }

  void Struct::AddStruct(Struct st) {
    contents.push_back({ DeclareStruct, structs.size() });
    structs.push_back(st);
  }

  void Struct::AddEnum(Enum en) {
    contents.push_back({ DeclareEnum, enums.size() });
    enums.push_back(en);
  }
}; // reviser
}; // ast
