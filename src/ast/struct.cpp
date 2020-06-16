/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#include <algorithm>
#include <iterator>
#include <sstream>
#include <ast/struct.h>

namespace reviser {
namespace ast {
  // Declare
  Declare::Declare(std::string type, ExprAssign assign): type(type), assign(assign) {}

  std::string Declare::generate() {
    return type + " " + assign.generate();
  }

  // StructProperty
  StructProperty::StructProperty(Declare declare): declare(declare) {}

  void StructProperty::AddDecorater(std::string decorater_) {
    decorater.push_back(decorater_);
  }

  std::string StructProperty::generate() {
    const char* const delim = ", ";
    std::ostringstream imploded;
    std::copy(
      decorater.begin(), decorater.end(),
      std::ostream_iterator<std::string>(imploded, delim)
    );

    return imploded.str() + declare.generate() + ";";
  }

  // Struct
  Struct::Struct(std::string word, std::string id): word(word), id(id) {}

  void Struct::AddProperty(StructProperty property_) {
    property.push_back(property_);
  }

  std::string Struct::generate() {
    std::string p = "";
    std::vector<StructProperty>::iterator it;

    for (it = property.begin(); it != property.end(); it++) {
      p = p + (*it).generate() + ";\n";
    }

    return word + " " + id + "{\n"
      + "  " + p
      + "\n"
      + "}";
  }

}; // reviser
}; // ast
