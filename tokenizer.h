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
    BLOCK_START,
    BLOCK_END,
    STATEMENT_END,
    STATEMENT_SEPARATOR,
    DECORATE,
    TYPE,
    STRUCTURE,
    NAME,
    CODE_END
  };

  struct Token {
    TokenType type;
    std::string text;

    int line;            // 行号
    int column_start;    // 列开始位置
    int column_end;      // 列结束位置
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

    template<typename CharacterClass>
    inline void consumeCharacters();

  public:
    Tokenizer(std::string input);
    ~Tokenizer();

    const Token& getCurrentToken();
    const Token& getPreviousToken();

    void findNextToken();
    void getNextChar();
    bool getNextToken();
  };
} // tokenizer
} // reviser

#endif
