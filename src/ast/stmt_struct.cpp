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

  string Decorater::Generate() {
    return id.text;
  }

  //
  // StructPrototype
  StructProperty::StructProperty(Declare declare)
    : declare(declare) {}

  void StructProperty::AddDecorater(Decorater decorater) {
    decoraters.push_back(decorater);
  }

  string StructProperty::Generate() {
    string code;
    for (Decorater d: decoraters) {
      code = code + " " + d.Generate();
    }
    return code + " " + declare.Generate();
  }

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

  string Struct::Generate() {
    // string code = "struct " + id.text + " {\n";
    // for (StructProperty p: properties) {
    //   code = code + "  " + p.Generate() + ";\n";
    // }
    // return code + "}";

    string code = "struct " + id.text + " {\n";

    for (ContentStore p: contents) {
      switch (p.type) {
        case DeclareProperty: {
          StructProperty s = properties.at(p.index);
          code = code + " " + s.Generate() + ";\n";
          break;
        }

        case DeclareStruct: {
          Struct s = structs.at(p.index);
          code = code + " " + s.Generate() + "\n";
          break;
        }

        case DeclareEnum: {
          Enum s = enums.at(p.index);
          code = code + " " + s.Generate() + "\n";
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
