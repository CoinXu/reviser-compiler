/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#include <algorithm>
#include <iterator>
#include <sstream>
#include <ast/struct.h>

using namespace std;

namespace reviser {
namespace ast {
  // Declare
  Declare::Declare(string type, ExprAssign assign): type(type), assign(assign) {}

  string Declare::generate() {
    return type + " " + assign.generate();
  }

  // StructProperty
  StructProperty::StructProperty(Declare declare): declare(declare) {}

  void StructProperty::AddDecorater(string decorater_) {
    decorater.push_back(decorater_);
  }

  string StructProperty::generate() {
    const char* const delim = ", ";
    ostringstream imploded;
    copy(
      decorater.begin(), decorater.end(),
      ostream_iterator<string>(imploded, delim)
    );

    return imploded.str() + declare.generate() + ";";
  }

  // Struct
  void Struct::SetID(string id_) {
    id = id_;
  }

  void Struct::SetWord(string word_) {
    word = word_;
  }

  void Struct::AddProperty(StructProperty property_) {
    property.push_back(property_);
  }

  string Struct::generate() {
    string p = "";
    vector<StructProperty>::iterator it;

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
