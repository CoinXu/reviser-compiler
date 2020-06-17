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
      if (LookAtTokenType(compiler::Struct)) {
        ast::Struct s = Struct();
        message.Info(s.generate());
        seq.AddStmt(s);
      } else if (LookAtTokenType(compiler::Enum)) {
        ast::Stmt s = Enum();
        message.Info(s.generate());
        seq.AddStmt(s);
      } else {
        Next();
      }
    } while (!Accept(CodeEnd));

    // message.Info("code generated:");
    // message.Info(seq.generate());
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
  ast::Struct Parser::Struct() {
    Expect(compiler::Struct);
    Expect(ID);
    ast::Struct s(token);
    Expect(LeftBrace);

    do {
      s.AddProperty(StructProperty());
    } while (Accept(Semicolon) && !LookAtTokenType(RightBrace));

    Expect(RightBrace);
    return s;
  }

  ast::StructProperty Parser::StructProperty() {
    vector<ast::Decorater> v;

    if (Accept(compiler::Decorater)) {
      do {
        v.push_back(Decorater());
      } while (Accept(compiler::Decorater));
    }

    ast::Declare declare = Declare();
    ast::StructProperty property(declare);

    for (ast::Decorater d: v) {
      property.AddDecorater(d);
    }

    return property;
  }

  ast::Decorater Parser::Decorater() {
    ast::Decorater d(token);
    return d;
  }

  // expr
  ast::Declare Parser::Declare() {
    if (Accept(DataType)) {
      return DataTypeDeclare();
    } else if (Accept(ID)) {
      return EnumDeclare();
    }
    // TODO
    // else if
    // runtime error
  }

  ast::Declare Parser::DataTypeDeclare() {
    // Token t = tokenizer.Current();
    // string type = PreviousText();

    Token id = tokenizer.Current();
    string type = PreviousText();

    Expect(ID);

    // TODO
    // value optional support
    if (Accept(compiler::Assign)) {
      Token dvt = tokenizer.Current();
      string value = CurrentText();

      if (type == ReservedWordMap[ReservedWordTypeBoolean]) {
        if (value != ReservedWordMap[ReservedWordBooleanFalse]
          && value != ReservedWordMap[ReservedWordBooleanTrue]) {
          message.Runtime("expect true or false");
        } else {
          Next();
        }

        ast::DataValue dv(DataTypeBoolean, dvt);
        ast::Declare declare(DataTypeBoolean, id, dv);
        return declare;
      } else if (type == ReservedWordMap[ReservedWordTypeFloat]) {
        Expect(Digit);
        ast::DataValue dv(DataTypeFloat, dvt);
        ast::Declare declare(DataTypeFloat, id, dv);
        return declare;
      } else if (type == ReservedWordMap[ReservedWordTypeDouble]) {
        Expect(Digit);
        ast::DataValue dv(DataTypeDouble, dvt);
        ast::Declare declare(DataTypeDouble, id, dv);
        return declare;
      } else if (type == ReservedWordMap[ReservedWordTypeInt32]) {
        Expect(Digit);
        ast::DataValue dv(DataTypeInt32, dvt);
        ast::Declare declare(DataTypeInt32, id, dv);
        return declare;
      } else if (type == ReservedWordMap[ReservedWordTypeInt64]) {
        Expect(Digit);
        ast::DataValue dv(DataTypeInt64, dvt);
        ast::Declare declare(DataTypeInt64, id, dv);
        return declare;
      } else if (type == ReservedWordMap[ReservedWordTypeUint32]) {
        Expect(Digit);
        ast::DataValue dv(DataTypeUint32, dvt);
        ast::Declare declare(DataTypeUint32, id, dv);
        return declare;
      } else if (type == ReservedWordMap[ReservedWordTypeUint64]) {
        Expect(Digit);
        ast::DataValue dv(DataTypeUint64, dvt);
        ast::Declare declare(DataTypeUint64, id, dv);
        return declare;
      } else if (type == ReservedWordMap[ReservedWordTypeString]) {
        Expect(Letter);
        ast::DataValue dv(DataTypeString, dvt);
        ast::Declare declare(DataTypeString, id, dv);
        return declare;
      }
    }
  }

  ast::Declare Parser::EnumDeclare() {
    Token eid = token;
    Expect(ID);
    Token id = token;
    Expect(compiler::Assign);
    Expect(ID);
    Token ei = token;
    Expect(Connection);
    Expect(ID);
    Token ep = token;

    ast::EnumValue v(ei, ep);
    ast::Declare declare(DataTypeEnum, id, eid, v);

    return declare;
  }

  //
  // stmt -> enum
  ast::Stmt Parser::EnumProperty() {
    ast::Stmt s;
    return s;
  }

  ast::Stmt Parser::Enum () {
    ast::Stmt s;
    return s;
  }
}; // compiler
}; // reviser
