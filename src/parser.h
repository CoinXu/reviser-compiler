/**
 * @date 2020-06-15
 * @author duanxian0605@163.com
 * @description 词法分析，词法参考grammer.md
 */

#ifndef REVISER_COMPILER_PARSER
#define REVISER_COMPILER_PARSER

#include <string>
#include <tokenizer.h>
#include <message.h>
#include <ast/stmt.h>

using namespace reviser;

namespace reviser {
namespace compiler {
  class Parser {
  private:
    Tokenizer tokenizer;
    message::Message message;
    ast::Stmt stmt;
    ast::Stmt current;

    bool Accept(TokenType type);
    void Expect(TokenType type);

    bool LookAt(std::string expect);
    TokenType Type();
    std::string Text();

    void DefStruct();
    void DefStructProperty();
    void DefDecorater();
    void DefDeclare();
    void DefStructDataTypeDeclare();
    void DefStructEnumDeclare();
    void DefEnum();
    void DefEnumProperty();
    void DefStmt();

  public:
    Parser(Tokenizer tokenizer);
    ~Parser();
    void Program();
  };
} // reviser
} // compiler

#endif
