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

using namespace std;
using namespace reviser::message;
using namespace reviser::ast;

namespace reviser {
namespace compiler {
  class Parser {
  private:
    Tokenizer* tokenizer;
    CodeGenerator* generator;
    Descriptor* descriptor;

    Message message;
    Seq seq;
    Token token;
    CodeGeneratorType generator_type;

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

    template<typename T> void ProgramByGenerator(T* generator);

  public:
    Parser(Tokenizer*, CodeGenerator*, Descriptor*, CodeGeneratorType);
    ~Parser();
    void Program();
  };
} // reviser
} // compiler

#endif
