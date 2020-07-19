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
        generator->descriptor->AddGlobalVariableOnce(s->id->text, DECLARE_STRUCT);
        generator->AddStmtStruct(s);
      } else if (LookAtType(TOKEN_ENUM)) {
        Enum* s = ConsumeEnum();
        generator->descriptor->AddGlobalVariableOnce(s->id->text, DECLARE_ENUM);
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
    message.SetLine(token.start_line);
    message.SetColumn(token.column_start);
    message.Runtime(msg + ": " + token.text);
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
  Struct* Parser::ConsumeStruct(Struct* parent) {
    Expect(TOKEN_STRUCT);
    Expect(TOKEN_ID);

    if (generator->descriptor->FindCurrentContextVariableById(token.text) 
      || (parent && generator->descriptor->StructIncludeProperty(parent, token.text))) {
      RuntimeError("duplicate declare named [" + token.text + "]");
    }

    Struct* s = new Struct(CloneToken(token));

    Expect(TOKEN_LEFT_BRACE);

    generator->descriptor->PushContextVariable(s);
    generator->descriptor->PushNewContext();

    while (!Accept(TOKEN_RIGHT_BRACE)) {
      if (LookAtType(TOKEN_STRUCT)) {
        s->AddStruct(ConsumeStruct(s));
      } else if (LookAtType(TOKEN_ENUM)) {
        s->AddEnum(ConsumeEnum(s));
      } else {
        StructProperty* p = ConsumeStructProperty();
        if (generator->descriptor->StructIncludeProperty(s, p->declare->id->text)) {
          RuntimeError("duplicate declare property named [" + p->declare->id->text + "]");
        }
        if (generator->descriptor->FindCurrentContextVariableById(p->declare->id->text)) {
          RuntimeError("duplicate declare named [" + p->declare->id->text + "]");
        }
        s->AddProperty(p);
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
    generator->descriptor->AddDecoratorOnce(token.text);
    return d;
  }

  // expr
  Declare* Parser::ConsumeDeclare() {
    // data type & data type array
    if (Accept(TOKEN_DATA_TYPE)) {
      const string type = PreviousText();
      if (Accept(TOKEN_LEFT_BRACKET)) {
        return ConsumeDataTypeArrayDeclare(type);
      }
      return ConsumeDataTypeDeclare();
    }

    // struct & struct array
    // enum & enum array
    if (Accept(TOKEN_ID)) {
      // TODO support struct array type
      const Token type_id = tokenizer->Previous();
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

    DataType type = DataTypeValue.at(type_string);

    generator->descriptor->include_type_array = true;
    generator->descriptor->AddDataTypesOnce(type);

    RightValue* rv = new RightValue(type, CloneToken(token), true);
    return new Declare(type, CloneToken(id), rv, true);
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
          generator->descriptor->AddDataTypesOnce(TYPE_BOOL);
          Next();
        }
        break;

      case TYPE_FLOAT:
      case TYPE_DOUBLE:
      case TYPE_INT32:
      case TYPE_INT64:
      case TYPE_UINT32:
      case TYPE_UINT64:
        generator->descriptor->AddDataTypesOnce(TYPE_FLOAT);
        Expect(TOKEN_DIGIT);
        break;

      case TYPE_STRING:
        generator->descriptor->AddDataTypesOnce(TYPE_STRING);
        Expect(TOKEN_LETTER);
        break;

      default:
        RuntimeError("unknow data type [" + type + "]");
        break;
    }

    RightValue* rv = new RightValue(data_type, dvt);
    Declare* declare = new Declare(data_type, id, rv);
    return declare;
  }

  // Foo foo = null
  Declare* Parser::ConsumeStructDeclare() {
    Token* sid = CloneToken(tokenizer->Previous());

    // struct type id
    if (!generator->descriptor->FindStructContextVariableById(sid->text)) {
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

    generator->descriptor->AddDataTypesOnce(TYPE_STRUCT);
    RightValue* rv = new RightValue(sv);
    Declare* declare = new Declare(TYPE_STRUCT, id, sid, rv);
    return declare;
  }

  Declare* Parser::ConsumeEnumDeclare() {
    Token* eid = CloneToken(tokenizer->Previous());

    // enum type id
    if (!generator->descriptor->FindEnumContextVariableById(eid->text)) {
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
    if (!generator->descriptor->FindEnumContextVariableById(ei->text)) {
      RuntimeError("undefined enum [" + ei->text + "] in current scope");
    }

    Expect(TOKEN_CONNECTION);
    Expect(TOKEN_ID);
    Token* ep = CloneToken(token);

    if (!generator->descriptor->EnumInlcudeProperty(generator->descriptor->FindEnumContextVariableById(ei->text), ep->text)) {
      RuntimeError("undefined property [" + ep->text + "] in enum [" + ei->text + "]");
    }

    EnumValue* ev = new EnumValue(ei, ep);
    RightValue* rv = new RightValue(ev);
    Declare* declare = new Declare(TYPE_ENUM, id, eid, rv);
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

    generator->descriptor->include_struct_array = true;
    RightValue* rv = new RightValue(sv, true);
    return new Declare(TYPE_STRUCT, id, sid, rv, true);
  }

  // Color[] color = [];
  // Color[] color;
  Declare* Parser::ConsumeEnumArrayDeclare(const Token& enum_id) {
    Expect(TOKEN_RIGHT_BRACKET);
    Expect(TOKEN_ID);

    Token* eid = CloneToken(enum_id);
    Token* id = CloneToken(token);

    generator->descriptor->include_enum_array = true;

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

  Enum* Parser::ConsumeEnum(Struct* parent) {
    Expect(TOKEN_ENUM);
    Expect(TOKEN_ID);

    if (generator->descriptor->FindCurrentContextVariableById(token.text)
      || (parent && generator->descriptor->StructIncludeProperty(parent, token.text))) {
      RuntimeError("duplicate declare named [" + token.text + "]");
    }

    Token* id = CloneToken(token);
    Enum* e = new Enum(id);
    generator->descriptor->PushContextVariable(e);

    Expect(TOKEN_LEFT_BRACE);

    // no property enum
    if (Accept(TOKEN_RIGHT_BRACE)) {
      return e;
    }

    do {
      EnumProperty* property = ConsumeEnumProperty();
      if (generator->descriptor->EnumInlcudeProperty(e, property->id->text)) {
        RuntimeError("duplicate declare enum property named [" + property->id->text + "]");
        break;
      }
      e->properties.push_back(property);
    } while (Accept(TOKEN_COMMA));

    Expect(TOKEN_RIGHT_BRACE);

    return e;
  }

}; // compiler
}; // reviser
