/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description 定义.reviser文件内容标记，词法定义参考syntax.md
 */

#ifndef REVISER_COMPILER_TOKENIZER
#define REVISER_COMPILER_TOKENIZER

#include <string>

namespace reviser {
namespace compiler {

  enum TokenType {
    CODE_START,                      // 代码开始
    DATA_TYPES,                      // 数据类型: bool/float/double/int32...
    DATA_STRUCT,                     // 数据结构类型: struct/enum
    DECORATOR,                       // 修饰函数: optional/required/max/range...
    OPERATOR,                        // 操作符: import/package/extends...
    BLOCK_START,                     // 代码块开始: {
    BLOCK_END,                       // 代码块结束: }
    PARAMS_START,                    // 参数开始: (
    PARAMS_END,                      // 参数结束: )
    STATEMENT_SEPARATOR,             // 语句分隔符: ,
    STATEMENT_END,                   // 表达式结束: ;
    CONNECTOR,                       // 链接符: .
    ASSIGN,                          // 赋值符: =
    IDENTIFIER,                      // 标记
    DIGIT,                           // 数字
    LETTER,                          // 字符: 以"包裹
    CODE_END                         // 代码结束
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
    void PrintfThreeAddressCode(const Token* token);
    void PrintPoint(const std::string mark);
    void NextChar();
    bool Next();
  };
} // tokenizer
} // reviser

#endif
