//
//  @date 2020-07-09
//  @author duanxian0605@163.com
//  @description
//

#ifndef REVISER_COMPILER_DECORATER_SYNTAX
#define REVISER_COMPILER_DECORATER_SYNTAX

#include <vector>
#include <string>
#include <map>

using namespace std;

namespace reviser {
namespace compiler {
  enum ReviserType {
    REVISER_TYPE_ARRAY_STRUCT,
    REVISER_TYPE_ARRAY,
    REVISER_TYPE_STRUCT,
    REVISER_TYPE_BOOL,
    REVISER_TYPE_DOUBLE,
    REVISER_TYPE_EMAIL,
    REVISER_TYPE_FLOAT,
    REVISER_TYPE_INT32,
    REVISER_TYPE_INT64,
    REVISER_TYPE_UINT32,
    REVISER_TYPE_UINT64,
    REVISER_TYPE_STRING,
    REVISER_TYPE_PHONE,
    REVISER_TO_BOOL,
    REVISER_TO_DOUBLE,
    REVISER_TO_FLOAT,
    REVISER_TO_INT32,
    REVISER_TO_INT64,
    REVISER_TO_STRING,
    REVISER_TO_UINT32,
    REVISER_TO_UINT64,
    REVISER_MAX_LENGTH,
    REVISER_MAX,
    REVISER_MIN_LENGTH,
    REVISER_REQUIRED
  };

  enum ReviserSyntaxType {
    SYNTAX_CALLABLE,
    SYNTAX_FUNCTION
  };

  enum ReviserSyntaxArgType {
    ARG_NUMBER,
    ARG_STRING,
    ARG_STRUCT,
    ARG_ARRAY
  };

  struct ReviserArgDef {
    ReviserSyntaxArgType type;
    bool optional;
  };

  struct ReviserSyntaxDefinition {
    string name;
    ReviserSyntaxType type;
    vector<ReviserArgDef> args;
  };

  struct DecoraterArg {
    ReviserSyntaxArgType type;
    vector<string> value;
  };

  extern map<string, ReviserSyntaxDefinition> ReviserSyntaxBuildIn;
  extern map<ReviserType, ReviserSyntaxDefinition> ReviserMethodMap;
};
};

#endif
