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
    ast::Struct Struct();
    ast::StructProperty StructProperty();
    ast::Decorater Decorater();

    // expr
    ast::DataValue DataValue();
    ast::EnumValue EnumValue();
    ast::Assign Assign();
    ast::Declare Declare();
    ast::Declare DataTypeDeclare();
    ast::Declare EnumDeclare();

    // stmt -> enum
    ast::EnumProperty EnumProperty();
    ast::Enum Enum();

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
