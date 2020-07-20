/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description 定义.reviser文件内容标记，词法定义参考syntax.md
 */

#ifndef REVISER_COMPILER_TOKENIZER
#define REVISER_COMPILER_TOKENIZER

#include <string>
#include <vector>
#include <map>
#include <message.h>

using namespace std;
using namespace reviser;

namespace reviser {
namespace compiler {

  enum TokenType {
    TOKEN_DATA_TYPE,
    TOKEN_DECORATER,
    TOKEN_STRUCT,
    TOKEN_ENUM,
    TOKEN_ID,
    TOKEN_LETTER,
    TOKEN_DIGIT,
    TOKEN_BOOL,
    TOKEN_CODE_START,
    TOKEN_CODE_END,
    TOKEN_NULL,
    TOKEN_DIVIDE = '/',
    TOKEN_ASTERISK = '*',
    TOKEN_ASSIGN = '=',
    TOKEN_LEFT_BRACE = '{',
    TOKEN_RIGHT_BRACE = '}',
    TOKEN_LEFT_BRACKET = '[',
    TOKEN_RIGHT_BRACKET = ']',
    TOKEN_SEMICOLON = ';',
    TOKEN_COMMA = ',',
    TOKEN_CONNECTION = '.',
    TOKEN_QUOTE = '"',
    TOKEN_PLUS = '+',
    TOKEN_HYPHEN= '-'
  };

  enum ReservedWord {
    RESERVED_STRUCT,
    RESERVED_ENUM,

    RESERVED_TRUE,
    RESERVED_FALSE,
    RESERVED_BOOL,
    RESERVED_FLOAT,
    RESERVED_DOUBLE,
    RESERVED_INT32,
    RESERVED_INT64,
    RESERVED_UINT32,
    RESERVED_UINT64,
    RESERVED_STRING,
    RESERVED_NULL,

    RESERVED_OPTIONAL,
    RESERVED_REQUIRED
  };

  enum DataType {
    TYPE_BOOL,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_INT32,
    TYPE_INT64,
    TYPE_UINT32,
    TYPE_UINT64,
    TYPE_STRING,
    TYPE_NULL,

    TYPE_ENUM,
    TYPE_STRUCT
  };

  struct Token {
    TokenType type;
    string text;

    int start_line;      // 开始行号
    int end_line;        // 结束行号
    int column_start;    // 列开始位置
    int column_end;      // 列结束位置
    int pos_start;       // 全部字符中开始位置
    int pos_end;         // 全部字符中结束位置
  };

  extern map<ReservedWord, string> ReservedWordMap;
  extern map<TokenType, string> TokenTypeNameMap;
  extern map<DataType, string> DataTypeName;
  extern map<string, DataType> DataTypeValue;

  static const struct Token EmptyToken = {
    TOKEN_ID,
    "",
    0,
    0,
    0,
    0,
    0,
    0
  };

  class Tokenizer {
  private:
    string input;
    vector<string> type;
    vector<string> decorater;
    message::Message message;

    Token current;
    Token previous;

    char peek;
    int pos;
    int line;
    int column;

    static const int CTabWidth = 8;

    // 依次对比字符，直到找到不是该字符集的字符为止
    template<typename CharacterClass> inline void ConsumeCharacters();

    // 依次对比字符，直到找到该字符集的为止
    template<typename CharacterClass> inline void TryConsumeCharacters();

    // 当前字符是否是某个字符集中的字符
    template<typename CharacterClass> inline bool InCharacters();

    bool TryConsume(char c);

    bool TypeIdentifier(const string id);
    bool DecoraterIdentifier(const string id);

    void ConsumeComment();

    // 处理数字，包括小数
    void ConsumeNumber();

  public:
    Tokenizer(string input);
    ~Tokenizer();

    const Token& Current();
    const Token& Previous();

    void Printf(const Token* token);
    void PrintPoint(const string mark);
    void NextChar();
    bool Next();
  };
} // tokenizer
} // reviser

#endif
