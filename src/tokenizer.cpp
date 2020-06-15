/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description 词法分析，词法定义参考syntax.md
 */

#include <string>
#include <iostream>
#include <map>

#include "tokenizer.h"

namespace reviser {
namespace compiler {

// 定义Token类型名称
typedef std::map<TokenType, char> TokenTypeMarkMap;


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

Tokenizer::Tokenizer(std::string input): input(input) {
  peek = input.at(0);
  pos = 0;
  line = 1;
  column = 0;

  NextChar();
}

Tokenizer::~Tokenizer() {}

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

const Token& Tokenizer::Current() {
  return current;
}

const Token& Tokenizer::Previous() {
  return previous;
}

void Tokenizer::Printf(const Token* token) {
  std::cout << "=============== token ===============" << std::endl;
  std::cout << "token.type: " << token->type << std::endl;
  std::cout << "token.text: " << token->text << std::endl;
  std::cout << "token.line: " << token->start_line << std::endl;
  std::cout << "token.column_start: " << token->column_start << std::endl;
  std::cout << "token.column_end: " << token->column_end << std::endl;
  std::cout << "token.pos_start: " << token->pos_start << std::endl;
  std::cout << "token.pos_end: " << token->pos_end << std::endl;
  std::cout << "====================================" << std::endl;
}

void Tokenizer::PrintPoint(const std::string mark) {
  std::cout << mark << "line: " << line
    << " column: " << column
    << " char: " << peek
    << " currentpos: " << pos
    << std::endl;
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
      current.type = Quote;
      NextChar();
      TryConsumeCharacters<CharQuote>();
      NextChar();
      current.text = input.substr(start_pos -1, pos - start_pos);
      break;

    case Digit:
      current.type = Digit;
      ConsumeCharacters<CharDigit>();
      current.text = input.substr(start_pos - 1, pos - start_pos);
      break;

    default:
      if (InCharacters<Identifier>()) {
        ConsumeCharacters<Identifier>();
        current.text = input.substr(start_pos - 1, pos - start_pos);
      } else {
        TryConsumeCharacters<NewLine>();
        const std::string message = input.substr(start_pos - 1,  pos - start_pos);
        throw std::runtime_error("unkown token error: \n  " + message + "\n  ^");
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
