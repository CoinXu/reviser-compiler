/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description 定义.reviser文件内容标记，词法定义参考syntax.md
 */

#include <string>
#include <iostream>
#include <map>

#include "tokenizer.h"

namespace reviser {
namespace tokenizer {

// 定义Token类型名称
typedef std::map<TokenType, char> TokenTypeNameMap;

TokenTypeNameMap MakeTokenTypeNameMap() {
  TokenTypeNameMap map = {
    { BLOCK_START,         '{' },
    { BLOCK_END,           '}' },
    { STATEMENT_END,       ';' },
    { STATEMENT_SEPARATOR, ',' }
  };

  return map;
}

static const TokenTypeNameMap TokenTypeName = MakeTokenTypeNameMap();

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

CHARACTER_CLASS(Digit, '0' <= c && c <= '9');
CHARACTER_CLASS(Letter, ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ||
                          ('0' <= c && c <= '9') || (c == '_'));

CHARACTER_CLASS(BlockStart, c == TokenTypeName.at(BLOCK_START));
CHARACTER_CLASS(BlockEnd, c == TokenTypeName.at(BLOCK_END));
CHARACTER_CLASS(StatementEnd, c == TokenTypeName.at(STATEMENT_END));
CHARACTER_CLASS(StatementSeparator, c == TokenTypeName.at(STATEMENT_SEPARATOR));

#undef CHARACTER_CLASS

Tokenizer::Tokenizer(std::string input): input_(input) {
  std::cout << "s" << MakeTokenTypeNameMap().at(BLOCK_START) << std::endl;

  current_char_ = input_.at(0);
  current_pos_ = 0;
  line_ = 1;
  column_ = 0;

  NextChar();
  Printf(&current_);
}

Tokenizer::~Tokenizer() {}

// 依次对比字符，直到找到不是该字符集的字符为止
template<typename CharacterClass> inline void Tokenizer::ConsumeCharacters() {
  while(CharacterClass::is(current_char_)) {
    NextChar();
  }
}

// 依次对比字符，直到找到该字符集的为止
template<typename CharacterClass> inline void Tokenizer::TryConsumeCharacters() {
  while(!CharacterClass::is(current_char_)) {
    NextChar();
  }
}

const Token& Tokenizer::Current() {
  return current_;
}

const Token& Tokenizer::Previous() {
  return previous_;
}

void Tokenizer::Printf(const Token* token) {
  std::cout << "=============== token ===============" << std::endl;
  std::cout << "token.type: " << token->type << std::endl;
  std::cout << "token.text: " << token->text << std::endl;
  std::cout << "token.line: " << token->line << std::endl;
  std::cout << "token.column_start: " << token->column_start << std::endl;
  std::cout << "token.column_end: " << token->column_end << std::endl;
  std::cout << "token.pos_start: " << token->pos_start << std::endl;
  std::cout << "token.pos_end: " << token->pos_end << std::endl;
  std::cout << "====================================" << std::endl;
}

void Tokenizer::PrintPoint(const std::string mark) {
  std::cout << mark << "line: " << line_ 
    << " column: " << column_
    << " char: " << current_char_
    << " current_pos: " << current_pos_
    << std::endl;
}

void Tokenizer::NextChar() {
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
}

bool Tokenizer::Next() {
  previous_ = current_;

  ConsumeCharacters<Whitespace>();
  
  int start_pos = current_pos_ - 1;
  int start_line = line_;

  ConsumeCharacters<Letter>();

  std::string letter(input_.substr(start_pos, current_pos_ - start_pos - 1));

  if (letter.compare("enum") == 0 || letter.compare("struct") == 0) {
    TryConsumeCharacters<BlockEnd>();

    current_.type = STRUCTURE;
    current_.text = input_.substr(start_pos, current_pos_ - start_pos);
    current_.line = start_line;
    current_.column_start = previous_.column_end;
    current_.column_end = column_;
    current_.pos_start = previous_.pos_end;
    current_.pos_end = current_pos_;

    NextChar();

    return true;
  } 

  return false;
}
} // tokenizer
} // reviser
