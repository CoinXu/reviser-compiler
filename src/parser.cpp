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
  Parser::Parser(Tokenizer tokenizer)
    : tokenizer(tokenizer), message("parser"), seq() {}

  Parser::~Parser() {}

  void Parser::Program() {
    Accept(TOKEN_CODE_START);

    do {
      if (LookAtTokenType(TOKEN_STRUCT)) {
        Struct s = ConsumeStruct();
        message.Info(s.generate());
        seq.AddStmt(s);
      } else if (LookAtTokenType(TOKEN_ENUM)) {
        Enum s = ConsumeEnum();
        message.Info(s.generate());
        seq.AddStmt(s);
      } else {
        Next();
      }
    } while (!Accept(TOKEN_CODE_END));
  }

  //
  // private
  bool Parser::Accept(TokenType type) {
    token = tokenizer.Current();
    if (token.type == type) {
      tokenizer.Next();
      return true;
    }
    return false;
  }

  void Parser::Expect(TokenType type) {
    if (!Accept(type)) {
      message.SetLine(tokenizer.Current().start_line);
      message.SetColumn(tokenizer.Current().column_start);
      message.Runtime("syntax error: " + tokenizer.Current().text);
    }
  }

  void Parser::Next() {
    tokenizer.Next();
  }

  bool Parser::LookAt(string expect) {
    return CurrentText() == expect;
  }

  bool Parser::LookAtTokenType(TokenType expect) {
    return CurrentType() == expect;
  }

  TokenType Parser::CurrentType() {
    return tokenizer.Current().type;
  }

  TokenType Parser::PreviousType() {
    return tokenizer.Previous().type;
  }

  string Parser::CurrentText() {
    return tokenizer.Current().text;
  }

  string Parser::PreviousText() {
    return tokenizer.Previous().text;
  }

  // stmt -> struct
  Struct Parser::ConsumeStruct() {
    Expect(TOKEN_STRUCT);
    Expect(TOKEN_ID);
    Struct s(token);
    Expect(TOKEN_LEFT_BRACE);

    do {
      if (LookAtTokenType(TOKEN_STRUCT)) {
        s.AddStruct(ConsumeStruct());
      } else if (LookAtTokenType(TOKEN_ENUM)) {
        s.AddEnum(ConsumeEnum());
      } else {
        s.AddProperty(ConsumeStructProperty());
      }
    } while (!Accept(TOKEN_RIGHT_BRACE));

    return s;
  }

  StructProperty Parser::ConsumeStructProperty() {
    vector<Decorater> v;

    if (Accept(TOKEN_DECORATER)) {
      do {
        v.push_back(ConsumeDecorater());
      } while (Accept(TOKEN_DECORATER));
    }

    Declare declare = ConsumeDeclare();
    StructProperty property(declare);

    Expect(TOKEN_SEMICOLON);

    for (Decorater d: v) {
      property.AddDecorater(d);
    }

    return property;
  }

  Decorater Parser::ConsumeDecorater() {
    Decorater d(token);
    return d;
  }

  // expr
  Declare Parser::ConsumeDeclare() {
    if (Accept(TOKEN_DATA_TYPE)) {
      return ConsumeDataTypeDeclare();
    } else if (Accept(TOKEN_ID)) {
      return ConsumeEnumDeclare();
    }
    // TODO
    // else if
    // runtime error
  }

  Declare Parser::ConsumeDataTypeDeclare() {
    Token id = tokenizer.Current();
    string type = PreviousText();

    Expect(TOKEN_ID);

    // TODO
    // value optional support
    if (Accept(TOKEN_ASSIGN)) {
      Token dvt = tokenizer.Current();
      string value = CurrentText();
      DataType data_type;

      if (type == ReservedWordMap[RESERVED_BOOL]) {
        data_type = TYPE_BOOL;
        if (value != ReservedWordMap[RESERVED_FALSE]
          && value != ReservedWordMap[RESERVED_TRUE]) {
          message.Runtime("expect true or false");
        } else {
          Next();
        }
      } else if (type == ReservedWordMap[RESERVED_FLOAT]) {
        data_type = TYPE_FLOAT;
        Expect(TOKEN_DIGIT);
      } else if (type == ReservedWordMap[RESERVED_DOUBLE]) {
        data_type = TYPE_DOUBLE;
        Expect(TOKEN_DIGIT);
      } else if (type == ReservedWordMap[RESERVED_INT32]) {
        data_type = TYPE_INT32;
        Expect(TOKEN_DIGIT);
      } else if (type == ReservedWordMap[RESERVED_INT64]) {
        data_type = TYPE_INT64;
        Expect(TOKEN_DIGIT);
      } else if (type == ReservedWordMap[RESERVED_UINT32]) {
        data_type = TYPE_UINT32;
        Expect(TOKEN_DIGIT);
      } else if (type == ReservedWordMap[RESERVED_UINT64]) {
        data_type = TYPE_UINT64;
        Expect(TOKEN_DIGIT);
      } else if (type == ReservedWordMap[RESERVED_STRING]) {
        data_type = TYPE_STRING;
        Expect(TOKEN_LETTER);
      }

      RightValue dv(data_type, dvt);
      Declare declare(data_type, id, dv);
      return declare;
    } else {
      message.Runtime("expect Assign token");
    }
  }

  Declare Parser::ConsumeEnumDeclare() {
    Token eid = token;
    Expect(TOKEN_ID);
    Token id = token;
    Expect(TOKEN_ASSIGN);
    Expect(TOKEN_ID);
    Token ei = token;
    Expect(TOKEN_CONNECTION);
    Expect(TOKEN_ID);
    Token ep = token;

    EnumValue v(ei, ep);
    Declare declare(TYPE_ENUM, id, eid, v);

    return declare;
  }

  //
  // stmt -> enum
  EnumProperty Parser::ConsumeEnumProperty() {
    Expect(TOKEN_ID);
    Token id = token;

    if (Accept(TOKEN_ASSIGN)) {
      Expect(TOKEN_DIGIT);
      RightValue value(TYPE_INT32, token);
      EnumProperty property(id, value);
      return property;
    }

    EnumProperty property(id);
    return property;
  }

  Enum Parser::ConsumeEnum () {
    Expect(TOKEN_ENUM);
    Expect(TOKEN_ID);
    Token id = token;
    Expect(TOKEN_LEFT_BRACE);

    Enum e(id);

    do {
      e.AddProperty(ConsumeEnumProperty());
    } while (Accept(TOKEN_COMMA));

    Expect(TOKEN_RIGHT_BRACE);
    return e;
  }
}; // compiler
}; // reviser
