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

using namespace reviser::message;

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
CHARACTER_CLASS(CharDivide, c == TOKEN_DIVIDE);
CHARACTER_CLASS(CharAsterisk, c == TOKEN_ASTERISK);
CHARACTER_CLASS(CharAssign, c == TOKEN_ASSIGN);
CHARACTER_CLASS(CharLeftBrace, c == TOKEN_LEFT_BRACE);
CHARACTER_CLASS(CharRightBrance, c == TOKEN_RIGHT_BRACE);
CHARACTER_CLASS(CharSemicolon, c == TOKEN_SEMICOLON);
CHARACTER_CLASS(CharComma, c == TOKEN_COMMA);
CHARACTER_CLASS(CharConnection, c == TOKEN_CONNECTION);
CHARACTER_CLASS(CharQuote, c == TOKEN_QUOTE);

#undef CHARACTER_CLASS


map<TokenType, string> TokenTypeNameMap = {
  { TOKEN_DATA_TYPE, "data type" },
  { TOKEN_DECORATER, "decorater" },
  { TOKEN_STRUCT, "struct" },
  { TOKEN_ENUM, "enum" },
  { TOKEN_ID, "id" },
  { TOKEN_LETTER, "letter" },
  { TOKEN_DIGIT, "digit" },
  { TOKEN_BOOL, "bool" },
  { TOKEN_CODE_END, "code end" },
  { TOKEN_ASSIGN, "assig" },
  { TOKEN_LEFT_BRACE, "left brace" },
  { TOKEN_RIGHT_BRACE, "right brace" },
  { TOKEN_SEMICOLON, "semicolon" },
  { TOKEN_COMMA, "comma" },
  { TOKEN_CONNECTION, "connection" },
  { TOKEN_QUOTE, "quote" }
};

map<ReservedWord, string> ReservedWordMap = {
  { RESERVED_STRUCT, "struct" },
  { RESERVED_ENUM, "enum" },

  { RESERVED_TRUE, "true" },
  { RESERVED_FALSE, "false" },

  { RESERVED_BOOL, "bool" },
  { RESERVED_FLOAT, "float" },
  { RESERVED_DOUBLE, "double" },
  { RESERVED_INT32, "int32" },
  { RESERVED_INT64, "int64" },
  { RESERVED_UINT32, "uint32" },
  { RESERVED_UINT64, "uint64" },
  { RESERVED_STRING, "string" },
  { RESERVED_NULL, "null" },

  { RESERVED_REQUIRED, "required" }
};

map<DataType, string> DataTypeName = {
  { TYPE_BOOL, ReservedWordMap[RESERVED_BOOL] },
  { TYPE_FLOAT, ReservedWordMap[RESERVED_FLOAT] },
  { TYPE_DOUBLE, ReservedWordMap[RESERVED_DOUBLE] },
  { TYPE_INT32, ReservedWordMap[RESERVED_INT32] },
  { TYPE_INT64, ReservedWordMap[RESERVED_INT64] },
  { TYPE_UINT32, ReservedWordMap[RESERVED_UINT32] },
  { TYPE_UINT64, ReservedWordMap[RESERVED_UINT64] },
  { TYPE_STRING, ReservedWordMap[RESERVED_STRING] }
};

map<string, DataType> DataTypeValue {
  { ReservedWordMap[RESERVED_BOOL], TYPE_BOOL },
  { ReservedWordMap[RESERVED_FLOAT], TYPE_FLOAT },
  { ReservedWordMap[RESERVED_DOUBLE], TYPE_DOUBLE },
  { ReservedWordMap[RESERVED_INT32], TYPE_INT32 },
  { ReservedWordMap[RESERVED_INT64], TYPE_INT64 },
  { ReservedWordMap[RESERVED_UINT32], TYPE_UINT32 },
  { ReservedWordMap[RESERVED_UINT64], TYPE_UINT64 },
  { ReservedWordMap[RESERVED_STRING], TYPE_STRING },
  { ReservedWordMap[RESERVED_NULL], TYPE_NULL }
};

Tokenizer::Tokenizer(string input): input(input), message("tokenizer") {
  peek = input.at(0);
  pos = 0;
  line = 1;
  column = 0;

  current.type = TOKEN_CODE_START;
  current.text = "";
  current.start_line = line;
  current.end_line = line;
  current.column_start = column;
  current.column_end = column;
  current.pos_start = pos;
  current.pos_end = pos;

  type.push_back(ReservedWordMap[RESERVED_BOOL]);
  type.push_back(ReservedWordMap[RESERVED_FLOAT]);
  type.push_back(ReservedWordMap[RESERVED_DOUBLE]);
  type.push_back(ReservedWordMap[RESERVED_INT32]);
  type.push_back(ReservedWordMap[RESERVED_INT64]);
  type.push_back(ReservedWordMap[RESERVED_UINT32]);
  type.push_back(ReservedWordMap[RESERVED_UINT64]);
  type.push_back(ReservedWordMap[RESERVED_STRING]);
  type.push_back(ReservedWordMap[RESERVED_NULL]);

  decorater.push_back(ReservedWordMap[RESERVED_OPTIONAL]);
  decorater.push_back(ReservedWordMap[RESERVED_REQUIRED]);

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

bool Tokenizer::TryConsume(char c) {
  if (peek == c) {
    NextChar();
    return true;
  }
  return false;
}

bool Tokenizer::TypeIdentifier(const string id) {
  auto result = find(begin(type), end(type), id);
  return result != end(type);
}

bool Tokenizer::DecoraterIdentifier(const string id) {
  auto result = find(begin(decorater), end(decorater), id);
  return result != end(decorater);
}

void Tokenizer::ConsumeComment() {
  while (InCharacters<CharDivide>()) {
    NextChar();

    if (InCharacters<CharDivide>()) {
      // line comment
      NextChar();
      if (peek != EOF) {
        TryConsumeCharacters<NewLine>();
      }
    } else if (InCharacters<CharAsterisk>()) {
      // block comment
      NextChar();
      while(true) {
        TryConsumeCharacters<CharAsterisk>();
        NextChar();
        if (InCharacters<CharDivide>() || peek == EOF) {
          break;
        }
      }
    }

    NextChar();
    ConsumeCharacters<Whitespace>();
  }
}

void Tokenizer::ConsumeNumber() {
  // 整数位
  ConsumeCharacters<CharDigit>();

  // 小数位
  if (TryConsume(TOKEN_CONNECTION)) {
    ConsumeCharacters<CharDigit>();
  }
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
  message.Debug("token.type: " + to_string(token->type));
  message.Debug("token.name: " + TokenTypeNameMap.at(token->type));
  message.Debug("token.text: " + token->text);
}

void Tokenizer::PrintPoint(const string mark) {
  message.SetLine(line);
  message.SetColumn(column);
  message.Debug("pos: " + to_string(pos));
  message.Debug("char: " + to_string(peek));
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

  if (pos < input.size()) {
    peek = input.at(pos);
    pos++;
    return;
  }

  peek = EOF;
}

bool Tokenizer::Next() {
  previous = current;

  if (pos >= input.size()) {
    current.type = TOKEN_CODE_END;
    current.text = "";
    return false;
  }

  ConsumeCharacters<Whitespace>();
  ConsumeComment();

  current.text = peek;

  int start_line = line;
  int start_column = column;
  int start_pos = pos;

  switch (peek) {
    case EOF:
      current.type = TOKEN_CODE_END;
      current.text = "";
      break;

    case TOKEN_ASSIGN:
    case TOKEN_LEFT_BRACE:
    case TOKEN_RIGHT_BRACE:
    case TOKEN_SEMICOLON:
    case TOKEN_COMMA:
    case TOKEN_CONNECTION:
    case TOKEN_LEFT_BRACKET:
    case TOKEN_RIGHT_BRACKET:
      current.type = (TokenType)peek;
      NextChar();
      break;

    case TOKEN_QUOTE:
      current.type = TOKEN_LETTER;
      NextChar();
      TryConsumeCharacters<CharQuote>();
      NextChar();
      current.text = input.substr(start_pos, pos - start_pos - 2);
      break;

    default:
      if (InCharacters<CharDigit>()) {
        current.type = TOKEN_DIGIT;
        ConsumeNumber();
        current.text = input.substr(start_pos - 1, pos - start_pos);
      } else if (InCharacters<Identifier>()) {
        ConsumeCharacters<Identifier>();
        current.text = input.substr(start_pos - 1, pos - start_pos);

        if (TypeIdentifier(current.text)) {
          current.type = TOKEN_DATA_TYPE;
        } else if (DecoraterIdentifier(current.text)) {
          current.type = TOKEN_DECORATER;
        } else if (current.text == ReservedWordMap[RESERVED_STRUCT]) {
          current.type = TOKEN_STRUCT;
        } else if (current.text == ReservedWordMap[RESERVED_ENUM]) {
          current.type = TOKEN_ENUM;
        } else {
          current.type = TOKEN_ID;
        }
      } else {
        TryConsumeCharacters<NewLine>();
        const string content = input.substr(start_pos - 1,  pos - start_pos);
        message.Runtime("unkown token error: \n  " + content + "\n  ^");
      }
  }

  current.start_line = start_line;
  current.end_line = line;
  current.column_start = start_column;
  current.column_end = column - 1;
  current.pos_start = start_pos;
  current.pos_end = pos;

  return current.type != TOKEN_CODE_END;
}
} // tokenizer
} // reviser
