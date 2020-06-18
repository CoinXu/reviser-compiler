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
#include <ast/stmt.h>
#include <ast/expr.h>

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

  //
  // Struct
  class Struct: public Stmt {
  private:
    Token id;
    vector<StructProperty> properties;

  public:
    string generate();
    Struct(Token id);
    void AddProperty(StructProperty property);
  };

}; // compiler
}; // reviser

#endif
