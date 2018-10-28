/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description 定义.reviser文件内容标记，词法定义参考syntax.md
 */

#include <string>
#include <iostream>

#include "tokenizer.h"

namespace reviser {
namespace tokenizer {

#define CHARACTER_CLASS(NAME, EXPERSSION) \
class NAME {                              \
public:                                   \
  static inline bool is(char c) {         \
    return EXPERSSION;                    \
  }                                       \
}

CHARACTER_CLASS(Whitespace, c == ' ' || c == '\n' || c == '\t' || c == '\r' || 
                            c == '\v' || c == '\f');
CHARACTER_CLASS(WhitespaceNoNewLine, c == ' ' || c == '\t' || c == '\r' 
                            || c == '\v' || c == '\f');

CHARACTER_CLASS(Digit, '0' <= c && c <= '0');
CHARACTER_CLASS(Property, ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
                          ('0' <= c && c <= '9') || (c == '_'));

#undef CHARACTER_CLASS

Tokenizer::Tokenizer(std::string input): input_(input) {
  current_.type = CODE_START;
  current_.text = "";
  current_.line = 0;
  current_.column_start = 0;
  current_.column_end = 0;
}

Tokenizer::~Tokenizer() {}

template<typename CharacterClass> 
inline void Tokenizer::consumeCharacters() {
  while(CharacterClass::is(current_char_)) {
    getNextChar();
  }
}

const Token& Tokenizer::getCurrentToken() {
  return current_;
}

const Token& Tokenizer::getPreviousToken() {
  return previous_;
}

void Tokenizer::findNextToken() {

}

void Tokenizer::getNextChar() {
  if (current_char_ == '\n') {
    line_++;
    column_ = 0;
  } else if (current_char_ == '\t') {
    column_ += cTabWidth - column_ % cTabWidth; 
  } else {
    column_++;
  }

  current_char_ = input_.at(current_pos_);
  current_pos_++;

  std::cout << "current_char_: " << current_char_ << std::endl;
}

bool Tokenizer::getNextToken() {
  previous_ = current_;

  do {
    // enum
    if (previous_.type == CODE_START) {
      consumeCharacters<WhitespaceNoNewLine>();
    }
    consumeCharacters<Property>();
  } while(current_char_ != '\0');

  return true;
}
} // tokenizer
} // reviser
