//
//  @date 2020-07-09
//  @author duanxian0605@163.com
//  @description
//

#include <compiler/decorater_syntax.h>

namespace reviser {
namespace compiler {
  std::map<std::string, DecoraterSyntaxDefinition> DecoraterSyntaxBuildIn = {
    {
      ReservedWordMap[RESERVED_OPTIONAL],
      { "Optional", SYNTAX_CALLABLE, vector<DecoraterArg>({}) }
    },
    {
      ReservedWordMap[RESERVED_REQUIRED],
      { "Required", SYNTAX_CALLABLE, vector<DecoraterArg>({}) }
    }
  };

  std::map<DataType, DecoraterSyntaxDefinition> DecoraterSyntaxDataType = {
    { TYPE_BOOL, { "TypeBoolean", SYNTAX_CALLABLE, vector<DecoraterArg>({}) } },
    { TYPE_FLOAT, { "TypeFloat", SYNTAX_CALLABLE, vector<DecoraterArg>({}) } },
    { TYPE_DOUBLE, { "TypeDouble", SYNTAX_CALLABLE, vector<DecoraterArg>({}) } },
    { TYPE_INT32, { "TypeInt32", SYNTAX_CALLABLE, vector<DecoraterArg>({}) } },
    { TYPE_INT64, { "TypeInt64", SYNTAX_CALLABLE, vector<DecoraterArg>({}) } },
    { TYPE_UINT32, { "TypeUnInt32", SYNTAX_CALLABLE, vector<DecoraterArg>({}) } },
    { TYPE_UINT64, { "TypeUnInt64", SYNTAX_CALLABLE, vector<DecoraterArg>({}) } },
    { TYPE_STRING, { "TypeString", SYNTAX_CALLABLE, vector<DecoraterArg>({}) } }
  };

  std::map<DataType, DecoraterSyntaxDefinition> DecoraterSyntaxTranslator = {
    { TYPE_BOOL, { "ToBoolean", SYNTAX_FUNCTION, vector<DecoraterArg>({}) } },
    { TYPE_FLOAT, { "ToFloat", SYNTAX_FUNCTION, vector<DecoraterArg>({}) } },
    { TYPE_DOUBLE, { "ToDouble", SYNTAX_FUNCTION, vector<DecoraterArg>({}) } },
    { TYPE_INT32, { "ToInt32", SYNTAX_FUNCTION, vector<DecoraterArg>({}) } },
    { TYPE_INT64, { "ToInt64", SYNTAX_FUNCTION, vector<DecoraterArg>({}) } },
    { TYPE_UINT32, { "ToUnUnInt32", SYNTAX_FUNCTION, vector<DecoraterArg>({}) } },
    { TYPE_UINT64, { "ToUnUnInt64", SYNTAX_FUNCTION, vector<DecoraterArg>({}) } },
    { TYPE_STRING, { "ToString", SYNTAX_FUNCTION, vector<DecoraterArg>({}) } }
  };
};
};
