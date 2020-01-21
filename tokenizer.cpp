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
    { STATEMENT_END,       ';' }
  };

  return map;
}

bool IsDataTypeLetter(const std::string c) {
  return c == "bool" || c == "float" || c == "double" || c == "int32" 
    || c == "int64" || c == "string" || c == "uint32" || c == "uint64";
}

bool IsDataStructLetter(const std::string c) {
  return c == "struct" || c == "enum";
}

bool IsDecoratorLetter(const std::string c) {
  return c == "optional" || c == "required" || c == "maxlen" || c == "minlen" 
    || c == "range" || c == "max" || c == "min" || c == "interval";
}

bool IsOperatorLetter(const std::string c) {
  return c == "import" || c == "package" || c == "extends";
}

static const TokenTypeNameMap TokenTypeName = MakeTokenTypeNameMap();

#define CHARACTER_CLASS(NAME, EXPERSSION)                    \
class NAME {                                                 \
public:                                                      \
  static inline bool InClass(char c) { return EXPERSSION; }  \
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

#undef CHARACTER_CLASS

Tokenizer::Tokenizer(std::string input): input_(input) {
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
  while(CharacterClass::InClass(current_char_)) {
    NextChar();
  }
}

// 依次对比字符，直到找到该字符集的为止
template<typename CharacterClass> inline void Tokenizer::TryConsumeCharacters() {
  while(!CharacterClass::InClass(current_char_)) {
    NextChar();
  }
}

// 当前字符是否是某个字符集中的字符
template<typename CharacterClass> inline bool Tokenizer::InCharacters() {
  return CharacterClass::InClass(current_char_);
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
  ConsumeCharacters<Whitespace>();

  previous_ = current_;
  int start_pos = current_pos_ - 1;
  int start_line = line_;

  // TODO try statment marker
  // 1. DIGIT
  // 2. LETTER
  // 3. BLOCK_START
  // 4. BLOCK_END
  // 5. STATEMENT_END

  if (current_char_ == TokenTypeName.at(BLOCK_START)) {
    current_.text = current_char_;
    current_.type = BLOCK_START;
  } else if (current_char_ == TokenTypeName.at(BLOCK_END)) {
    current_.text = current_char_;
    current_.type = BLOCK_END;
  } else if (current_char_ == TokenTypeName.at(STATEMENT_END)) {
    current_.text = current_char_;
    current_.type = STATEMENT_END;
  } else if (InCharacters<Digit>()) {
    ConsumeCharacters<Digit>();
    current_.text = input_.substr(start_pos, current_pos_ - 1 - start_pos);
    current_.type = DIGIT;
  } else if (InCharacters<Letter>()) {
    ConsumeCharacters<Letter>();
    current_.text = input_.substr(start_pos, current_pos_ - 1 - start_pos);

    if (IsDataStructLetter(current_.text)) {
      current_.type = DATA_STRUCT;
    } else if (IsDataTypeLetter(current_.text)) {
      current_.type = DATA_TYPES;
    } else if (IsDecoratorLetter(current_.text)) {
      current_.type = DECORATOR;
    } else if (IsOperatorLetter(current_.text)) {
      current_.type = OPERATOR;
    } else {
      current_.type = LETTER;
    }
  } else {
    current_.type = CODE_END;
  }

  current_.line = start_line;
  current_.column_start = previous_.column_end;
  current_.column_end = column_;
  current_.pos_start = previous_.pos_end;
  current_.pos_end = current_pos_;

  NextChar();
 
  return current_.type != CODE_END;
}
} // tokenizer
} // reviser
