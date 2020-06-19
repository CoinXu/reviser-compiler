/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_Ast_STMT_STRUCT
#define REVISER_COMPILER_Ast_STMT_STRUCT

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
  private:
    Token id;

  public:
    string generate();
    Decorater(Token id);
  };

  //
  // SructPrototype
  class StructProperty: public Stmt {
  private:
    vector<Decorater> decoraters;
    Declare declare;

  public:
    string generate();
    StructProperty(Declare declare);
    void AddDecorater(Decorater decorater);
  };

  enum StructBlockContentType {
    DeclareProperty,
    DeclareStruct,
    DeclareEnum
  };

  //
  // Struct
  class Struct: public Stmt {
  private:
    struct ContentStore {
      StructBlockContentType type;
      size_t index;
    };
    Token id;
    vector<StructProperty> properties;
    vector<Struct> structs;
    vector<Enum> enums;
    vector<ContentStore> contents;
    int level;

  public:
    string generate();
    Struct(Token id, int level = 0);
    void AddProperty(StructProperty property);
    void AddStruct(Struct st);
    void AddEnum(Enum en);
  };

}; // compiler
}; // reviser

#endif
