/**
 * @date 2020-01-21
 * @author duanxian0605@163.com
 * @description 语法解析，语法参考syntax.md
 */

#ifndef REVISER_COMPILER_PARSER
#define REVISER_COMPILER_PARSER

#include <string>

namespace reviser {
namespace compiler {
  enum ASTNodeType {
    PropertyStatement,
    Identifier,
    Literal,
    EnumDeclaration,
    StructDeclaration,
    ExpressionStatement,
    BlockStatement,
    CallExpression
  };

  struct BaseASTNode {
    ASTNodeType type;
    std::string label;
    int start;
    int end;
    int line;
  };

  struct IdentifierASTNode : BaseASTNode {
    std::string name;
  };

  template<typename T>
  struct LiteralASTNode : BaseASTNode {
    std::string raw;
    T value;
  };

  template<typename T>
  struct PropertyASTNode : BaseASTNode {
    IdentifierASTNode key;
    LiteralASTNode<T> value;
  };

  template<typename T>
  struct EnumDeclarationASTNode : BaseASTNode {
    IdentifierASTNode id;
    PropertyASTNode<T>* properties;
  };

  class Parser {

  };
} // reviser
} // compiler

#endif
