/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description 定义.reviser文件内容标记，词法定义参考syntax.md
 */

#ifndef DATA_REVIER_TOKENIZER
#define DATA_REVIER_TOKENIZER

#include <string>

namespace reviser {
namespace tokenizer {

  enum TokenType {
    CODE_START,
    DATA_TYPES,
    DATA_STRUCT,
    DECORATOR, 
    OPERATOR,
    BLOCK_START,
    BLOCK_END,
    STATEMENT_END,
    IDENTIFIER,
    DIGIT,
    LETTER,
    CODE_END
  };

  struct Token {
    TokenType type;
    std::string text;

    int line;            // 行号
    int column_start;    // 列开始位置
    int column_end;      // 列结束位置
    int pos_start;       // 全部字符中开始位置
    int pos_end;         // 全部字符中结束位置
  };

  class Tokenizer {
  private:
    std::string input_;
    Token current_;
    Token previous_;
    
    char current_char_;
    int current_pos_;
    int line_;
    int column_;

    static const int cTabWidth = 8;

    template<typename CharacterClass> inline void ConsumeCharacters();
    template<typename CharacterClass> inline void TryConsumeCharacters();
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
