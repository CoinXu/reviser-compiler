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
  // AstDecorater
  AstDecorater::AstDecorater(Token id): id(id) {}

  string AstDecorater::generate() {
    return id.text;
  }

  //
  // StructPrototype
  AstStructProperty::AstStructProperty(AstDeclare declare)
    : declare(declare) {}

  void AstStructProperty::AddDecorater(AstDecorater decorater) {
    decoraters.push_back(decorater);
  }

  string AstStructProperty::generate() {
    string code;
    for (AstDecorater d: decoraters) {
      code = code + " " + d.generate();
    }
    return code + " " + declare.generate();
  }

  //
  // AstStruct
  AstStruct::AstStruct(Token id, int level): id(id), level(level) {}

  void AstStruct::AddProperty(AstStructProperty property) {
    contents.push_back({ DeclareProperty, properties.size() });
    properties.push_back(property);
  }

  void AstStruct::AddStruct(AstStruct st) {
    contents.push_back({ DeclareStruct, structs.size() });
    structs.push_back(st);
  }

  void AstStruct::AddEnum(ast::AstEnum en) {
    contents.push_back({ DeclareEnum, enums.size() });
    enums.push_back(en);
  }

  string AstStruct::generate() {
    // string code = "struct " + id.text + " {\n";
    // for (AstStructProperty p: properties) {
    //   code = code + "  " + p.generate() + ";\n";
    // }
    // return code + "}";

    string code = "struct " + id.text + " {\n";

    for (ContentStore p: contents) {
      switch (p.type) {
        case DeclareProperty: {
          AstStructProperty s = properties.at(p.index);
          code = code + " " + s.generate() + ";\n";
          break;
        }

        case DeclareStruct: {
          ast::AstStruct s = structs.at(p.index);
          code = code + " " + s.generate() + "\n";
          break;
        }

        case DeclareEnum: {
          ast::AstEnum s = enums.at(p.index);
          code = code + " " + s.generate() + "\n";
          break;
        }

        default:
          break;
      }
    }

    return code + "}";
  }
}; // reviser
}; // ast
