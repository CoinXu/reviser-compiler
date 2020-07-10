/**
 * @date 2020-06-17
 * @author duanxian0605@163.com
 * @description
 */

#include <parser.h>

using namespace std;
using namespace reviser;

namespace reviser {
namespace compiler {
  //
  // public
  Parser::Parser(Tokenizer* tokenizer, CodeGenerator* generator, Printer* printer)
    : token(nullptr),
      message("parser"),
      tokenizer(tokenizer),
      generator(generator),
      printer(printer) {}

  Parser::~Parser() {}

  void Parser::Program() {
    Accept(TOKEN_CODE_START);

    do {
      if (LookAtType(TOKEN_STRUCT)) {
        Struct* s = ConsumeStruct();
        generator->descriptor->AddGlobalVariable(s->id->text, DECLARE_STRUCT);
        generator->AddStmtStruct(s);
      } else if (LookAtType(TOKEN_ENUM)) {
        Enum* s = ConsumeEnum();
        generator->descriptor->AddGlobalVariable(s->id->text, DECLARE_ENUM);
        generator->AddStmtEnum(s);
      } else {
        Next();
      }
    } while (!Accept(TOKEN_CODE_END));

    printer->Print(generator->Generate());
  }

  Token* Parser::CloneToken(const Token* t) {
    return new Token {
      t->type,
      t->text,
      t->start_line,
      t->end_line,
      t->column_start,
      t->column_start,
      t->pos_start,
      t->pos_end
    };
  }

  //
  // private
  bool Parser::Accept(TokenType type) {
    const Token& t = tokenizer->Current();

    if (token) {
      delete token;
    }

    token = CloneToken(&t);

    if (token->type == type) {
      tokenizer->Next();
      return true;
    }

    return false;
  }

  void Parser::RuntimeError(string msg = "syntax error") {
    message.SetLine(tokenizer->Current().start_line);
    message.SetColumn(tokenizer->Current().column_start);
    message.Runtime(msg + ": " + tokenizer->Current().text);
  }

  void Parser::Expect(TokenType type) {
    if (!Accept(type)) {
      RuntimeError(
        "expect token ["
        + TokenTypeNameMap[type] + "] but receive ["
        + TokenTypeNameMap[token->type] + "]"
      );
    }
  }

  void Parser::Next() {
    tokenizer->Next();
  }

  bool Parser::LookAt(string expect) {
    return CurrentText() == expect;
  }

  bool Parser::LookAtType(TokenType expect) {
    return CurrentType() == expect;
  }

  TokenType Parser::CurrentType() {
    return tokenizer->Current().type;
  }

  TokenType Parser::PreviousType() {
    return tokenizer->Previous().type;
  }

  string Parser::CurrentText() {
    return tokenizer->Current().text;
  }

  string Parser::PreviousText() {
    return tokenizer->Previous().text;
  }

  // stmt -> struct
  Struct* Parser::ConsumeStruct() {
    Expect(TOKEN_STRUCT);
    Expect(TOKEN_ID);
    Struct* s = new Struct(CloneToken(token));
    Expect(TOKEN_LEFT_BRACE);

    do {
      if (LookAtType(TOKEN_RIGHT_BRACE)) {
        continue;
      } else if (LookAtType(TOKEN_STRUCT)) {
        s->AddStruct(ConsumeStruct());
      } else if (LookAtType(TOKEN_ENUM)) {
        s->AddEnum(ConsumeEnum());
      } else {
        s->AddProperty(ConsumeStructProperty());
      }
    } while (!Accept(TOKEN_RIGHT_BRACE));

    return s;
  }

  StructProperty* Parser::ConsumeStructProperty() {
    vector<Decorater*> v;

    if (Accept(TOKEN_DECORATER)) {
      do {
        v.push_back(ConsumeDecorater());
      } while (Accept(TOKEN_DECORATER));
    }

    Declare* declare = ConsumeDeclare();
    StructProperty* property = new StructProperty(declare);

    Expect(TOKEN_SEMICOLON);

    for (Decorater* d : v) {
      property->decoraters.push_back(d);
    }

    return property;
  }

  Decorater* Parser::ConsumeDecorater() {
    Decorater* d = new Decorater(CloneToken(token));
    generator->descriptor->AddDecorator(token->text);
    return d;
  }

  // expr
  Declare* Parser::ConsumeDeclare() {
    if (Accept(TOKEN_DATA_TYPE)) {
      return ConsumeDataTypeDeclare();
    } else if (Accept(TOKEN_ID)) {
      return ConsumeEnumDeclare();
    } else {
      RuntimeError("unexpected token");
      return nullptr;
    }
  }

  Declare* Parser::ConsumeDataTypeDeclare() {
    Token* id = CloneToken(&tokenizer->Current());
    string type = PreviousText();

    Expect(TOKEN_ID);

    // TODO
    // value optional support
    Expect(TOKEN_ASSIGN);

    Token* dvt = CloneToken(&tokenizer->Current());
    string value = CurrentText();
    DataType data_type;

    if (type == ReservedWordMap[RESERVED_BOOL]) {
      data_type = TYPE_BOOL;
      if (value != ReservedWordMap[RESERVED_FALSE]
        && value != ReservedWordMap[RESERVED_TRUE]) {
        RuntimeError("expect true or false");
      } else {
        generator->descriptor->AddDataTypes(TYPE_BOOL);
        Next();
      }
    } else if (type == ReservedWordMap[RESERVED_FLOAT]) {
      data_type = TYPE_FLOAT;
      generator->descriptor->AddDataTypes(TYPE_FLOAT);

      Expect(TOKEN_DIGIT);
    } else if (type == ReservedWordMap[RESERVED_DOUBLE]) {
      data_type = TYPE_DOUBLE;
      generator->descriptor->AddDataTypes(TYPE_DOUBLE);

      Expect(TOKEN_DIGIT);
    } else if (type == ReservedWordMap[RESERVED_INT32]) {
      data_type = TYPE_INT32;
      generator->descriptor->AddDataTypes(TYPE_INT32);

      Expect(TOKEN_DIGIT);
    } else if (type == ReservedWordMap[RESERVED_INT64]) {
      data_type = TYPE_INT64;
      generator->descriptor->AddDataTypes(TYPE_INT64);

      Expect(TOKEN_DIGIT);
    } else if (type == ReservedWordMap[RESERVED_UINT32]) {
      data_type = TYPE_UINT32;
      generator->descriptor->AddDataTypes(TYPE_UINT32);

      Expect(TOKEN_DIGIT);
    } else if (type == ReservedWordMap[RESERVED_UINT64]) {
      data_type = TYPE_UINT64;
      generator->descriptor->AddDataTypes(TYPE_UINT64);

      Expect(TOKEN_DIGIT);
    } else if (type == ReservedWordMap[RESERVED_STRING]) {
      data_type = TYPE_STRING;
      generator->descriptor->AddDataTypes(TYPE_STRING);

      Expect(TOKEN_LETTER);
    }

    RightValue* dv = new RightValue(data_type, dvt);
    Declare* declare = new Declare(data_type, id, dv);
    return declare;
  }

  Declare* Parser::ConsumeEnumDeclare() {
    Token* eid = CloneToken(token);
    Expect(TOKEN_ID);
    Token* id = CloneToken(token);
    Expect(TOKEN_ASSIGN);
    Expect(TOKEN_ID);
    Token* ei = CloneToken(token);
    Expect(TOKEN_CONNECTION);
    Expect(TOKEN_ID);
    Token* ep = CloneToken(token);

    EnumValue* v = new EnumValue(ei, ep);
    Declare* declare = new Declare(TYPE_ENUM, id, eid, v);
    return declare;
  }

  //
  // stmt -> enum
  EnumProperty* Parser::ConsumeEnumProperty() {
    Expect(TOKEN_ID);
    Token* id = CloneToken(token);

    if (Accept(TOKEN_ASSIGN)) {
      Expect(TOKEN_DIGIT);
      RightValue* value = new RightValue(TYPE_INT32, CloneToken(token));
      EnumProperty* property = new EnumProperty(id, value);
      return property;
    }

    EnumProperty* property = new EnumProperty(id);
    return property;
  }

  Enum* Parser::ConsumeEnum () {
    Expect(TOKEN_ENUM);
    Expect(TOKEN_ID);
    Token* id = CloneToken(token);
    Expect(TOKEN_LEFT_BRACE);

    Enum* e = new Enum(id);

    do {
      e->properties.push_back(ConsumeEnumProperty());
    } while (Accept(TOKEN_COMMA));

    Expect(TOKEN_RIGHT_BRACE);

    return e;
  }
}; // compiler
}; // reviser
