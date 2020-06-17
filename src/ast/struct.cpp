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
  // ExprDeclare
  ExprDeclare::ExprDeclare(string type, ExprAssign assign)
    : type(type), assign(assign) {}

  string ExprDeclare::generate() {
    return type + " " + assign.generate();
  }

  // StmtStmtStructProperty
  StmtStmtStructProperty::StmtStmtStructProperty(ExprDeclare declare)
    : declare(declare) {}

  void StmtStmtStructProperty::AddDecorater(string decorater_) {
    decorater.push_back(decorater_);
  }

  string StmtStmtStructProperty::generate() {
    const char* const delim = ", ";
    ostringstream imploded;
    copy(
      decorater.begin(), decorater.end(),
      ostream_iterator<string>(imploded, delim)
    );

    return imploded.str() + declare.generate() + ";";
  }

  // StmtStruct
  void StmtStruct::SetID(string id_) {
    id = id_;
  }

  void StmtStruct::SetWord(string word_) {
    word = word_;
  }

  void StmtStruct::AddProperty(StmtStmtStructProperty property_) {
    property.push_back(property_);
  }

  string StmtStruct::generate() {
    string p = "";
    vector<StmtStmtStructProperty>::iterator it;

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
