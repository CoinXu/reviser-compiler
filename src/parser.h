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
#include <ast/expr.h>
#include <ast/stmt.h>
#include <ast/stmt_struct.h>
#include <ast/stmt_enum.h>

using namespace std;
using namespace reviser;

namespace reviser {
namespace compiler {
  class Parser {
  private:
    Tokenizer tokenizer;
    message::Message message;
    ast::Seq seq;
    Token token;

    bool Accept(TokenType type);
    void Expect(TokenType type);
    void Next();
    bool LookAt(string expect);
    bool LookAtTokenType(TokenType expect);
    Token CloneCurrentToken();

    TokenType CurrentType();
    TokenType PreviousType();
    string CurrentText();
    string PreviousText();

    // stmt -> struct
    ast::AstStruct AstStruct();
    ast::AstStructProperty AstStructProperty();
    ast::AstDecorater AstDecorater();

    // expr
    ast::AstRightValue AstRightValue();
    ast::AstEnumValue AstEnumValue();
    ast::AstAssign AstAssign();
    ast::AstDeclare AstDeclare();
    ast::AstDeclare DataTypeDeclare();
    ast::AstDeclare EnumDeclare();

    // stmt -> enum
    ast::AstEnumProperty AstEnumProperty();
    ast::AstEnum AstEnum();

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
