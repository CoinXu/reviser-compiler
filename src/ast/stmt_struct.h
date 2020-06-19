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
  // AstDecorater
  // required | optional
  class AstDecorater: public AstStmt {
  private:
    Token id;

  public:
    string generate();
    AstDecorater(Token id);
  };

  //
  // SructPrototype
  class AstStructProperty: public AstStmt {
  private:
    vector<AstDecorater> decoraters;
    AstDeclare declare;

  public:
    string generate();
    AstStructProperty(AstDeclare declare);
    void AddDecorater(AstDecorater decorater);
  };

  enum AstStructBlockContentType {
    DeclareProperty,
    DeclareStruct,
    DeclareEnum
  };

  //
  // AstStruct
  class AstStruct: public AstStmt {
  private:
    struct ContentStore {
      AstStructBlockContentType type;
      size_t index;
    };
    Token id;
    vector<AstStructProperty> properties;
    vector<AstStruct> structs;
    vector<AstEnum> enums;
    vector<ContentStore> contents;
    int level;

  public:
    string generate();
    AstStruct(Token id, int level = 0);
    void AddProperty(AstStructProperty property);
    void AddStruct(AstStruct st);
    void AddEnum(ast::AstEnum en);
  };

}; // compiler
}; // reviser

#endif
