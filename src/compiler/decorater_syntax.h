//
//  @date 2020-07-09
//  @author duanxian0605@163.com
//  @description
//

#ifndef REVISER_COMPILER_DECORATER_SYNTAX
#define REVISER_COMPILER_DECORATER_SYNTAX

#include <vector>
#include <string>
#include <tokenizer.h>

using namespace std;

namespace reviser {
namespace compiler {
  enum DecoraterSyntaxType {
    SYNTAX_CALLABLE,
    SYNTAX_FUNCTION
  };

  enum DecoraterSyntaxArgType {
    ARG_NUMBER,
    ARG_STRING,
    ARG_STRUCT,
    ARG_ARRAY
  };

  struct DecoraterArgDef {
    string name;
    DecoraterSyntaxArgType type;
    bool optional;
  };

  struct DecoraterSyntaxDefinition {
    string name;
    DecoraterSyntaxType type;
    vector<DecoraterArgDef> args;
  };

  struct DecoraterArg {
    DecoraterSyntaxArgType type;
    vector<string> value;
  };

  extern std::map<std::string, DecoraterSyntaxDefinition> DecoraterSyntaxBuildIn;
  extern std::map<DataType, DecoraterSyntaxDefinition> DecoraterSyntaxTranslator;
  extern std::map<DataType, DecoraterSyntaxDefinition> DecoraterSyntaxDataType;
};
};

#endif
