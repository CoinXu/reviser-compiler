/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description 定义.reviser文件内容标记，词法定义参考syntax.md
 */

#ifndef REVISER_COMPILER_TOKENIZER
#define REVISER_COMPILER_TOKENIZER

#include <string>
#include <array>

namespace reviser {
namespace compiler {

  enum TokenType {
    Type,
    Decorater,
    Struct,
    ID,
    Letter,
    Digit,
    Enum,
    Bool,
    CodeEnd,
    Assign = '=',
    LeftBrace = '{',
    RightBrace = '}',
    Semicolon = ';',
    Comma = ',',
    Connection = '.',
    Quote = '"'
  };

  struct Token {
    TokenType type;
    std::string text;

    int start_line;       // 开始行号
    int end_line;         // 结束行号
    int column_start;    // 列开始位置
    int column_end;      // 列结束位置
    int pos_start;       // 全部字符中开始位置
    int pos_end;         // 全部字符中结束位置
  };

  class Tokenizer {
  private:
    std::string input;
    std::array<std::string, 2> types = {
      "",
      ""
    };
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

  public:
    Tokenizer(std::string input);
    ~Tokenizer();

    const Token& Current();
    const Token& Previous();

    void Printf(const Token* token);
    void PrintPoint(const std::string mark);
    void NextChar();
    bool Next();
  };
} // tokenizer
} // reviser

#endif
