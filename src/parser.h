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
using namespace reviser::message;
using namespace reviser::ast;

namespace reviser {
namespace compiler {
  class Parser {
  private:
    Tokenizer tokenizer;
    Message message;
    Seq seq;
    Token token;

    bool Accept(TokenType type);
    void Expect(TokenType type);
    void Next();
    bool LookAt(string expect);
    bool LookAtType(TokenType expect);

    TokenType CurrentType();
    TokenType PreviousType();
    string CurrentText();
    string PreviousText();

    // stmt -> struct
    Struct ConsumeStruct();
    StructProperty ConsumeStructProperty();
    Decorater ConsumeDecorater();

    // expr
    RightValue ConsumeRightValue();
    EnumValue ConsumeEnumValue();
    Assign ConsumeAssign();
    Declare ConsumeDeclare();
    Declare ConsumeDataTypeDeclare();
    Declare ConsumeEnumDeclare();

    // stmt -> enum
    EnumProperty ConsumeEnumProperty();
    Enum ConsumeEnum();

  public:
    Parser(Tokenizer tokenizer);
    ~Parser();
    void Program();
  };
} // reviser
} // compiler

#endif
