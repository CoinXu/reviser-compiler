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
    Accept(CodeStart);

    do {
      if (LookAtTokenType(compiler::AstStruct)) {
        ast::AstStruct s = AstStruct();
        message.Info(s.generate());
        seq.AddStmt(s);
      } else if (LookAtTokenType(compiler::AstEnum)) {
        ast::AstEnum s = AstEnum();
        message.Info(s.generate());
        seq.AddStmt(s);
      } else {
        Next();
      }
    } while (!Accept(CodeEnd));
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

  Token Parser::CloneCurrentToken() {
    Token current = tokenizer.Current();
    Token c;
    return c;
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
  ast::AstStruct Parser::AstStruct() {
    Expect(compiler::AstStruct);
    Expect(ID);
    ast::AstStruct s(token);
    Expect(LeftBrace);

    do {
      if (LookAtTokenType(compiler::AstStruct)) {
        s.AddStruct(AstStruct());
      } else if (LookAtTokenType(compiler::AstEnum)) {
        s.AddEnum(AstEnum());
      } else {
        s.AddProperty(AstStructProperty());
      }
    } while (!Accept(RightBrace));

    return s;
  }

  ast::AstStructProperty Parser::AstStructProperty() {
    vector<ast::AstDecorater> v;

    if (Accept(compiler::AstDecorater)) {
      do {
        v.push_back(AstDecorater());
      } while (Accept(compiler::AstDecorater));
    }


    ast::AstDeclare declare = AstDeclare();
    ast::AstStructProperty property(declare);

    Expect(Semicolon);

    for (ast::AstDecorater d: v) {
      property.AddDecorater(d);
    }

    return property;
  }

  ast::AstDecorater Parser::AstDecorater() {
    ast::AstDecorater d(token);
    return d;
  }

  // expr
  ast::AstDeclare Parser::AstDeclare() {
    if (Accept(DataType)) {
      return DataTypeDeclare();
    } else if (Accept(ID)) {
      return EnumDeclare();
    }
    // TODO
    // else if
    // runtime error
  }

  ast::AstDeclare Parser::DataTypeDeclare() {
    // Token t = tokenizer.Current();
    // string type = PreviousText();

    Token id = tokenizer.Current();
    string type = PreviousText();

    Expect(ID);

    // TODO
    // value optional support
    if (Accept(compiler::AstAssign)) {
      Token dvt = tokenizer.Current();
      string value = CurrentText();
      DataValueType data_type;

      if (type == ReservedWordMap[ReservedWordTypeBoolean]) {
        data_type = DataTypeBoolean;
        if (value != ReservedWordMap[ReservedWordBooleanFalse]
          && value != ReservedWordMap[ReservedWordBooleanTrue]) {
          message.Runtime("expect true or false");
        } else {
          Next();
        }
      } else if (type == ReservedWordMap[ReservedWordTypeFloat]) {
        data_type = DataTypeFloat;
        Expect(Digit);
      } else if (type == ReservedWordMap[ReservedWordTypeDouble]) {
        data_type = DataTypeDouble;
        Expect(Digit);
      } else if (type == ReservedWordMap[ReservedWordTypeInt32]) {
        data_type = DataTypeInt32;
        Expect(Digit);
      } else if (type == ReservedWordMap[ReservedWordTypeInt64]) {
        data_type = DataTypeInt64;
        Expect(Digit);
      } else if (type == ReservedWordMap[ReservedWordTypeUint32]) {
        data_type = DataTypeUint32;
        Expect(Digit);
      } else if (type == ReservedWordMap[ReservedWordTypeUint64]) {
        data_type = DataTypeUint64;
        Expect(Digit);
      } else if (type == ReservedWordMap[ReservedWordTypeString]) {
        data_type = DataTypeString;
        Expect(Letter);
      }

      ast::AstRightValue dv(data_type, dvt);
      ast::AstDeclare declare(data_type, id, dv);
      return declare;
    } else {
      message.Runtime("expect AstAssign token");
    }
  }

  ast::AstDeclare Parser::EnumDeclare() {
    Token eid = token;
    Expect(ID);
    Token id = token;
    Expect(compiler::AstAssign);
    Expect(ID);
    Token ei = token;
    Expect(Connection);
    Expect(ID);
    Token ep = token;

    ast::AstEnumValue v(ei, ep);
    ast::AstDeclare declare(DataTypeEnum, id, eid, v);

    return declare;
  }

  //
  // stmt -> enum
  ast::AstEnumProperty Parser::AstEnumProperty() {
    Expect(ID);
    Token id = token;

    if (Accept(compiler::AstAssign)) {
      Expect(Digit);
      ast::AstRightValue value(DataTypeInt32, token);
      ast::AstEnumProperty property(id, value);
      return property;
    }

    ast::AstEnumProperty property(id);
    return property;
  }

  ast::AstEnum Parser::AstEnum () {
    Expect(compiler::AstEnum);
    Expect(ID);
    Token id = token;
    Expect(LeftBrace);

    ast::AstEnum e(id);

    do {
      e.AddProperty(AstEnumProperty());
    } while (Accept(Comma));

    Expect(RightBrace);
    return e;
  }
}; // compiler
}; // reviser
