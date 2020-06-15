/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description 词法分析，词法定义参考syntax.md
 */

#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>

#include <message.h>
#include <tokenizer.h>

namespace reviser {
namespace compiler {

#define CHARACTER_CLASS(NAME, EXPERSSION)                    \
class NAME {                                                 \
public:                                                      \
  static inline bool InClass(char c) { return EXPERSSION; }  \
}

CHARACTER_CLASS(Whitespace, c == ' ' || c == '\n' || c == '\t' || c == '\r' ||
                            c == '\v' || c == '\f');
CHARACTER_CLASS(WhitespaceNoNewLine, c == ' ' || c == '\t' || c == '\r'
                            || c == '\v' || c == '\f');
CHARACTER_CLASS(NewLine, c == '\n');
CHARACTER_CLASS(CharDigit, '0' <= c && c <= '9');
CHARACTER_CLASS(Identifier, ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
                          ('0' <= c && c <= '9') || (c == '_'));
CHARACTER_CLASS(CharAssign, c == Assign);
CHARACTER_CLASS(CharLeftBrace, c == LeftBrace);
CHARACTER_CLASS(CharRightBrance, c == RightBrace);
CHARACTER_CLASS(CharSemicolon, c == Semicolon);
CHARACTER_CLASS(CharComma, c == Comma);
CHARACTER_CLASS(CharConnection, c == Connection);
CHARACTER_CLASS(CharQuote, c == Quote);

#undef CHARACTER_CLASS

message::Message message("tokenizer");

std::map<TokenType, std::string> TokenTypeNameMap = {
  { DataType, "DataType" },
  { Decorater, "Decorater" },
  { Struct, "Struct" },
  { Enum, "Enum" },
  { ID, "ID" },
  { Letter, "Letter" },
  { Digit, "Digit" },
  { Bool, "Bool" },
  { CodeEnd, "CodeEnd" },
  { Assign, "Assig" },
  { LeftBrace, "LeftBrace" },
  { RightBrace, "RightBrace" },
  { Semicolon, "Semicolon" },
  { Comma, "Comma" },
  { Connection, "Connection" },
  { Quote, "Quote" }
};

Tokenizer::Tokenizer(std::string input_): input(input_) {
  peek = input.at(0);
  pos = 0;
  line = 1;
  column = 0;

  type.push_back("bool");
  type.push_back("float");
  type.push_back("double");
  type.push_back("int32");
  type.push_back("int64");
  type.push_back("uint32");
  type.push_back("uint64");
  type.push_back("string");

  decorater.push_back("optional");
  decorater.push_back("required");

  NextChar();
}

Tokenizer::~Tokenizer() {}

// private
template<typename CharacterClass> inline void Tokenizer::ConsumeCharacters() {
  while(CharacterClass::InClass(peek)) {
    NextChar();
  }
}

template<typename CharacterClass> inline void Tokenizer::TryConsumeCharacters() {
  while(!CharacterClass::InClass(peek)) {
    NextChar();
  }
}

template<typename CharacterClass> inline bool Tokenizer::InCharacters() {
  return CharacterClass::InClass(peek);
}

bool Tokenizer::TypeIdentifier(const std::string id) {
  auto result = std::find(std::begin(type), std::end(type), id);
  return result != std::end(type);
}

bool Tokenizer::DecoraterIdentifier(const std::string id) {
  auto result = std::find(std::begin(decorater), std::end(decorater), id);
  return result != std::end(decorater);
}

// public
const Token& Tokenizer::Current() {
  return current;
}

const Token& Tokenizer::Previous() {
  return previous;
}

void Tokenizer::Printf(const Token* token) {
  message.SetLine(token->start_line);
  message.SetColumn(token->column_start);
  message.Debug("-------------------------------------------");
  message.Debug("token.type: " + std::to_string(token->type));
  message.Debug("token.name: " + TokenTypeNameMap.at(token->type));
  message.Debug("token.text: " + token->text);
}

void Tokenizer::PrintPoint(const std::string mark) {
  message.SetLine(line);
  message.SetColumn(column);
  message.Debug("pos: " + std::to_string(pos));
  message.Debug("char: " + std::to_string(peek));
}

void Tokenizer::NextChar() {
  if (peek == '\n') {
    line++;
    column = 1;
  } else if (peek == '\t') {
    column += CTabWidth - column % CTabWidth;
  } else {
    column++;
  }

  peek = input.at(pos);
  pos++;
}

bool Tokenizer::Next() {
  if (pos == input.size()) {
    return false;
  }

  ConsumeCharacters<Whitespace>();

  previous = current;
  current.text = peek;

  int start_line = line;
  int start_column = column;
  int start_pos = pos;

  switch (peek) {
    case EOF:
      current.type = CodeEnd;
      break;

    case Assign:
    case LeftBrace:
    case RightBrace:
    case Semicolon:
    case Comma:
    case Connection:
      current.type = (TokenType) peek;
      NextChar();
      break;

    case Quote:
      current.type = Letter;
      NextChar();
      TryConsumeCharacters<CharQuote>();
      NextChar();
      current.text = input.substr(start_pos -1, pos - start_pos);
      break;

    default:
      if (InCharacters<CharDigit>()) {
        current.type = Digit;
        ConsumeCharacters<CharDigit>();
        current.text = input.substr(start_pos - 1, pos - start_pos);
      } else if (InCharacters<Identifier>()) {
        ConsumeCharacters<Identifier>();
        current.text = input.substr(start_pos - 1, pos - start_pos);

        if (TypeIdentifier(current.text)) {
          current.type = DataType;
        } else if (DecoraterIdentifier(current.text)) {
          current.type = Decorater;
        } else if (current.text == "struct") {
          current.type = Struct;
        } else if (current.text == "enum") {
          current.type = Enum;
        } else {
          current.type = ID;
        }
      } else {
        TryConsumeCharacters<NewLine>();
        const std::string content = input.substr(start_pos - 1,  pos - start_pos);
        message.Runtime("unkown token error: \n  " + content + "\n  ^");
      }
  }

  current.start_line = start_line;
  current.end_line = line;
  current.column_start = start_column;
  current.column_end = column - 1;
  current.pos_start = start_pos;
  current.pos_end = pos;

  return current.type != CodeEnd;
}
} // tokenizer
} // reviser
