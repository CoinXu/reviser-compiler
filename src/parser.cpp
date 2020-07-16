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
    : token(EmptyToken),
      message("parser"),
      tokenizer(tokenizer),
      generator(generator),
      printer(printer) {}

  Parser::~Parser() {}

  void Parser::Program() {
    Accept(TOKEN_CODE_START);
    generator->descriptor->PushNewContext();

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

    generator->descriptor->PopBackContext();
    printer->Print(generator->Generate());
  }

  Token* Parser::CloneToken(const Token& t) {
    return new Token {
      t.type,
      t.text,
      t.start_line,
      t.end_line,
      t.column_start,
      t.column_start,
      t.pos_start,
      t.pos_end
    };
  }

  //
  // private
  bool Parser::Accept(TokenType type) {
    token = tokenizer->Current();

    if (token.type == type) {
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
        "expect token [" + TokenTypeNameMap[type] + "] but receive ["
        + TokenTypeNameMap[token.type] + "]"
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
    generator->descriptor->PushContextVariable(s);
    generator->descriptor->PushNewContext();

    Expect(TOKEN_LEFT_BRACE);

    while (!Accept(TOKEN_RIGHT_BRACE)) {
      if (LookAtType(TOKEN_STRUCT)) {
        s->AddStruct(ConsumeStruct());
      } else if (LookAtType(TOKEN_ENUM)) {
        s->AddEnum(ConsumeEnum());
      } else {
        s->AddProperty(ConsumeStructProperty());
      }
    }

    generator->descriptor->PopBackContext();
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
    generator->descriptor->AddDecorator(token.text);
    return d;
  }

  // expr
  Declare* Parser::ConsumeDeclare() {
    if (Accept(TOKEN_DATA_TYPE)) {
      const string type = PreviousText();
      if (Accept(TOKEN_LEFT_BRACKET)) {
        return ConsumeDataTypeArrayDeclare(type);
      }
      return ConsumeDataTypeDeclare();
    }

    if (Accept(TOKEN_ID)) {
      // TODO support struct array type
      const Token& type_id = tokenizer->Previous();
      const string id = type_id.text;
      DeclareType type = generator->descriptor->FindContextVariableTypeById(id);

      if (Accept(TOKEN_LEFT_BRACKET)) {
        if (type == DECLARE_STRUCT) {
          return ConsumeStructArrayDeclare(type_id);
        }

        if (type == DECLARE_ENUM) {
          return ConsumeEnumArrayDeclare(type_id);
        }

        RuntimeError("unknow array type [" + id + "]");
      }

      if (type == DECLARE_STRUCT) {
        return ConsumeStructDeclare();
      }

      if (type == DECLARE_ENUM) {
        return ConsumeEnumDeclare();
      }

      if (type == DECLARE_UNDEFINED) {
        RuntimeError("undefined type [" + id + "]");
      }

      RuntimeError("unknow type [" + id + "]");
    }

    RuntimeError("unexpected token");
    return nullptr;
  }

  // int32[] foo = []
  Declare* Parser::ConsumeDataTypeArrayDeclare(string type_string) {
    Expect(TOKEN_RIGHT_BRACKET);

    if (DataTypeValue.find(type_string) == DataTypeValue.end()) {
      RuntimeError("unknow data type: " + type_string);
    }

    Expect(TOKEN_ID);
    const Token id = token;

    Expect(TOKEN_ASSIGN);
    Expect(TOKEN_LEFT_BRACKET);
    // TODO support initial values
    Expect(TOKEN_RIGHT_BRACKET);

    generator->descriptor->AddDataTypes(TYPE_ARRAY);
    generator->descriptor->AddDataTypes(DataTypeValue[type_string]);

    return new Declare(DataTypeValue[type_string], CloneToken(id));
  }

  Declare* Parser::ConsumeDataTypeDeclare() {
    Token* id = CloneToken(tokenizer->Current());
    string type = PreviousText();

    Expect(TOKEN_ID);

    // TODO
    // value optional support
    Expect(TOKEN_ASSIGN);

    Token* dvt = CloneToken(tokenizer->Current());
    string value = CurrentText();
    DataType data_type = DataTypeValue.at(type);

    switch (data_type) {
      case TYPE_BOOL:
        if (value != ReservedWordMap[RESERVED_FALSE] && value != ReservedWordMap[RESERVED_TRUE]) {
          RuntimeError("expect true or false");
        } else {
          generator->descriptor->AddDataTypes(TYPE_BOOL);
          Next();
        }
        break;

      case TYPE_FLOAT:
      case TYPE_DOUBLE:
      case TYPE_INT32:
      case TYPE_INT64:
      case TYPE_UINT32:
      case TYPE_UINT64:
        generator->descriptor->AddDataTypes(TYPE_FLOAT);
        Expect(TOKEN_DIGIT);
        break;

      case TYPE_STRING:
        generator->descriptor->AddDataTypes(TYPE_STRING);
        Expect(TOKEN_LETTER);
        break;

      default:
        RuntimeError("unknow data type [" + type + "]");
        break;
    }

    RightValue* dv = new RightValue(data_type, dvt);
    Declare* declare = new Declare(data_type, id, dv);
    return declare;
  }

  // Foo foo = null
  Declare* Parser::ConsumeStructDeclare() {
    Token* sid = CloneToken(tokenizer->Previous());

    // struct type id
    if (!generator->descriptor->FindStructContextById(sid->text)) {
      RuntimeError("undefined struct [" + sid->text + "] in current scope");
    }

    Expect(TOKEN_ID);
    Token* id = CloneToken(token);
    StructValue* sv;

    // struct only allow null to default value
    if (Accept(TOKEN_ASSIGN)) {
      Expect(TOKEN_DATA_TYPE);
      sv = new StructValue(sid, CloneToken(token));
      if (token.text != ReservedWordMap[RESERVED_NULL]) {
        RuntimeError("struct only allow null to default value");
      }
    } else {
      sv = new StructValue(sid, nullptr);
    }

    generator->descriptor->AddDataTypes(TYPE_STRUCT);
    Declare* declare = new Declare(sid, sv);
    return declare;
  }

  Declare* Parser::ConsumeEnumDeclare() {
    Token* eid = CloneToken(tokenizer->Previous());

    // enum type id
    if (!generator->descriptor->FindEnumContextById(eid->text)) {
      RuntimeError("undefined enum [" + eid->text + "] in current scope");
    }

    Expect(TOKEN_ID);
    Token* id = CloneToken(token);
    Expect(TOKEN_ASSIGN);
    Expect(TOKEN_ID);
    Token* ei = CloneToken(token);

    // value must match type
    if (eid->text != ei->text) {
      RuntimeError("enum type [" + eid->text + "] not match value [" + ei->text + "]");
    }

    // enum variable id
    if (!generator->descriptor->FindEnumContextById(ei->text)) {
      RuntimeError("undefined enum [" + ei->text + "] in current scope");
    }

    Expect(TOKEN_CONNECTION);
    Expect(TOKEN_ID);
    Token* ep = CloneToken(token);

    if (!generator->descriptor->EnumInlcudeProperty(generator->descriptor->FindEnumContextById(ei->text), ep->text)) {
      RuntimeError("undefined property [" + ep->text + "] in enum [" + ei->text + "]");
    }

    EnumValue* v = new EnumValue(ei, ep);
    Declare* declare = new Declare(TYPE_ENUM, id, eid, v);
    return declare;
  }

  // Foo[] foo = [];
  // Foo foo;
  Declare* Parser::ConsumeStructArrayDeclare(const Token& struct_id) {
    Expect(TOKEN_RIGHT_BRACKET);
    Expect(TOKEN_ID);
    Token* sid = CloneToken(struct_id);
    Token* id = CloneToken(token);
    StructValue* sv;

    if (Accept(TOKEN_ASSIGN)) {
      if (Accept(TOKEN_LEFT_BRACKET)) {
        Expect(TOKEN_RIGHT_BRACKET);
        // TODO make TYPE_EMPTY_ARRAY type for data type
        sv = new StructValue(sid, CloneToken(token));
      } else {
        delete sid;
        delete id;
        RuntimeError("unknow struct array default value");
      }
    } else {
      sv = new StructValue(sid, nullptr);
    }

    return new Declare(id, sv, true);
  }

  // Color[] color = [];
  // Color[] color;
  Declare* Parser::ConsumeEnumArrayDeclare(const Token& enum_id) {
    Expect(TOKEN_RIGHT_BRACKET);
    Expect(TOKEN_ID);

    Token* eid = CloneToken(enum_id);
    Token* id = CloneToken(token);

    return nullptr;
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
    generator->descriptor->PushContextVariable(e);

    do {
      e->properties.push_back(ConsumeEnumProperty());
    } while (Accept(TOKEN_COMMA));

    Expect(TOKEN_RIGHT_BRACE);

    return e;
  }
}; // compiler
}; // reviser
