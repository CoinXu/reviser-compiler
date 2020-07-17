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
#include <compiler/code_generator.h>
#include <compiler/javascript/javascript_generator.h>
#include <compiler/typescript/typescript_generator.h>
#include <compiler/descriptor.h>
#include <io/printer.h>

using namespace std;
using namespace reviser::message;
using namespace reviser::ast;
using namespace reviser::io;

namespace reviser {
namespace compiler {
  class Parser {
  private:
    Tokenizer* tokenizer;
    CodeGenerator* generator;
    Token token;
    Printer* printer;

    Message message;

    void RuntimeError(string message);
    bool Accept(TokenType type);
    void Expect(TokenType type);
    void Next();
    bool LookAt(string expect);
    bool LookAtType(TokenType expect);

    Token* CloneToken(const Token& t);
    TokenType CurrentType();
    TokenType PreviousType();
    string CurrentText();
    string PreviousText();

    // stmt -> struct
    Struct* ConsumeStruct();
    StructProperty* ConsumeStructProperty();
    Decorater* ConsumeDecorater();

    // expr
    RightValue* ConsumeRightValue();
    EnumValue* ConsumeEnumValue();
    Assign* ConsumeAssign();
    Declare* ConsumeDeclare();
    Declare* ConsumeDataTypeDeclare();
    Declare* ConsumeDataTypeArrayDeclare(string type);
    Declare* ConsumeEnumDeclare();
    Declare* ConsumeStructDeclare();
    Declare* ConsumeEnumArrayDeclare(const Token& type_id);
    Declare* ConsumeStructArrayDeclare(const Token& type_id);

    // stmt -> enum
    EnumProperty* ConsumeEnumProperty();
    Enum* ConsumeEnum();

  public:
    Parser(Tokenizer*, CodeGenerator*, Printer*);
    ~Parser();
    void Program();
  };
} // reviser
} // compiler

#endif
