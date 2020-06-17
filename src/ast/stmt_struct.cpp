/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#include <algorithm>
#include <iterator>
#include <sstream>
#include <ast/stmt_struct.h>

using namespace std;

namespace reviser {
namespace ast {
  //
  // Decorater
  Decorater::Decorater(Token id): id(id) {}

  string Decorater::generate() {
    return id.text;
  }

  //
  // StructPrototype
  StructProperty::StructProperty(Declare declare)
    : declare(declare) {}

  void StructProperty::AddDecorater(Decorater decorater) {
    decoraters.push_back(decorater);
  }

  string StructProperty::generate() {
    string code;
    for (Decorater d: decoraters) {
      code = code + " " + d.generate();
    }
    return code + " " + declare.generate();
  }

  //
  // Struct
  Struct::Struct(Token id): id(id) {}

  void Struct::AddProperty(StructProperty property) {
    properties.push_back(property);
  }

  string Struct::generate() {
    string code = "struct " + id.text + "{\n";
    for (StructProperty p: properties) {
      code = code + p.generate() + "\n";
    }
    return code + "}";
  }
}; // reviser
}; // ast
