/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description 词法分析，词法参考grammer.md
 */

#ifndef REVISER_COMPILER_PARSER
#define REVISER_COMPILER_PARSER

#include <string>
#include <tokenizer.h>

namespace reviser {
namespace compiler {
  class Parser {
  private:
    Token token;

    void Accept(TokenType token);
    void Expect(TokenType token);

    void DefStruct();
    void DefStructProperty();
    void DefEnum();
    void DefEnumProperty();
    void DefDeclare();

    void Stmt();

  public:
    void Program();
  };
} // reviser
} // compiler

#endif
