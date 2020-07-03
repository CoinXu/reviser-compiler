/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_AST_STMT_STRUCT
#define REVISER_COMPILER_AST_STMT_STRUCT

#include <string>
#include <vector>
#include <tokenizer.h>
#include <ast/expr.h>
#include <ast/stmt.h>
#include <ast/stmt_enum.h>

using namespace std;
using namespace reviser::compiler;

namespace reviser {
namespace ast {
  //
  // Decorater
  // required | optional
  class Decorater: public Stmt {
  public:
    Token* id = nullptr;

    Decorater(Token* id);
    ~Decorater();
  };

  //
  // SructPrototype
  class StructProperty: public Stmt {
  public:
    vector<Decorater*> decoraters;
    Declare* declare = nullptr;

    StructProperty(Declare* declare);
    ~StructProperty();
  };

  enum StructBlockContentType {
    DeclareProperty,
    DeclareStruct,
    DeclareEnum
  };

  //
  // Struct
  class Struct: public Stmt {
  public:
    struct ContentStore {
      StructBlockContentType type;
      size_t index;
    };

    Token* id = nullptr;
    vector<StructProperty*> properties;
    vector<Struct*> structs;
    vector<Enum*> enums;
    vector<ContentStore> contents;
    int level = 0;

    Struct(Token* id, int level = 0);
    ~Struct();
    void AddProperty(StructProperty* property);
    void AddStruct(Struct* st);
    void AddEnum(Enum* en);
  };

}; // compiler
}; // reviser

#endif
