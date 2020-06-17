/**
 * @date 2020-06-16
 * @author duanxian0605@163.com
 * @description
 */

#include <parser.h>
#include <message.h>

using namespace reviser::message;

namespace reviser {
namespace compiler {

  Parser::Parser(Tokenizer tokenizer): tokenizer(tokenizer), message("parser") {}

  Parser::~Parser() {}

  void Parser::Program() {
    Accept(CodeStart);

    do {
      DefStmt();
    } while (!Accept(CodeEnd));
  }

  //
  // private
  bool Parser::Accept(TokenType type) {
    if (tokenizer.Current().type == type) {
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

  void Parser::DefStruct() {
    Expect(ID);
    Expect(LeftBrace);

    do {
      DefStructProperty();
    } while (Accept(Semicolon));

    Expect(RightBrace);
  }

  void Parser::DefStructProperty() {
    if (Accept(Decorater)) {
      do {
        DefDecorater();
      } while (Accept(Decorater));
    }

    DefDeclare();
  }

  void Parser::DefDecorater() {
    // TODO
  }

  void Parser::DefDeclare() {
    if (Accept(DataType)) {
      DefStructDataTypeDeclare();
    } else if (Accept(ID)) {
      DefStructEnumDeclare();
    }
  }

  void Parser::DefStructDataTypeDeclare() {
    std::string type = tokenizer.Previous().text;

    Expect(ID);

    if (Accept(Assign)) {
      std::string value = tokenizer.Current().text;
      TokenType token = tokenizer.Current().type;

      if (type == ReservedWordMap[ReservedWordTypeBoolean]) {
        if (value != ReservedWordMap[ReservedWordBooleanFalse]
          && value != ReservedWordMap[ReservedWordBooleanTrue]) {
          message.Runtime("expect true or false");
        } else {
          tokenizer.Next();
        }
      } else if (type == ReservedWordMap[ReservedWordTypeFloat]
        || type == ReservedWordMap[ReservedWordTypeDouble]
        || type == ReservedWordMap[ReservedWordTypeInt32]
        || type == ReservedWordMap[ReservedWordTypeInt64]
        || type == ReservedWordMap[ReservedWordTypeUint32]
        || type == ReservedWordMap[ReservedWordTypeUint64]) {
        Expect(Digit);
      } else if (type == ReservedWordMap[ReservedWordTypeString]) {
        Expect(Letter);
      }
    }
  }

  void Parser::DefStructEnumDeclare() {
    Expect(ID);
    Expect(Assign);
    Expect(ID);
    Expect(Connection);
    Expect(ID);
  }

  void Parser::DefEnum() {
    Expect(ID);
    Expect(LeftBrace);

    do {
      DefEnumProperty();
    } while (Accept(Comma));

    Expect(RightBrace);
  }

  void Parser::DefEnumProperty() {
    Expect(ID);

    if (Accept(Assign)) {
      Expect(Digit);
    }
  }

  void Parser::DefStmt() {
    if (Accept(Struct)) {
      DefStruct();
    } else if (Accept(Enum)) {
      DefEnum();
    }
  }
}; // reviser
}; // compiler
