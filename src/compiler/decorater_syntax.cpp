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
      { "Optional", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) }
    },
    {
      ReservedWordMap[RESERVED_REQUIRED],
      { "Required", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) }
    }
  };

  std::map<DataType, DecoraterSyntaxDefinition> DecoraterSyntaxDataType = {
    { TYPE_BOOL, { "TypeBoolean", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) } },
    { TYPE_FLOAT, { "TypeFloat", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) } },
    { TYPE_DOUBLE, { "TypeDouble", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) } },
    { TYPE_INT32, { "TypeInt32", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) } },
    { TYPE_INT64, { "TypeInt64", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) } },
    { TYPE_UINT32, { "TypeUnInt32", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) } },
    { TYPE_UINT64, { "TypeUnInt64", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) } },
    { TYPE_STRING, { "TypeString", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) } },
    {
      TYPE_STRUCT,
      {
        "TypeStruct",
        SYNTAX_CALLABLE,
        vector<DecoraterArgDef>({
          { "Clazz", ARG_STRING, false }
        })
      }
    },
    {
      TYPE_ARRAY,
      {
        "TypeArray",
        SYNTAX_CALLABLE, vector<DecoraterArgDef>({
          { "decorators", ARG_ARRAY, true },
          { "template", ARG_STRING, true }
        })
      }
    },
    { TYPE_ARRAY_STRUCT, { "TypeArrayStruct", SYNTAX_CALLABLE, vector<DecoraterArgDef>({}) } }
  };

  std::map<DataType, DecoraterSyntaxDefinition> DecoraterSyntaxTranslator = {
    { TYPE_BOOL, { "ToBoolean", SYNTAX_FUNCTION, vector<DecoraterArgDef>({}) } },
    { TYPE_FLOAT, { "ToFloat", SYNTAX_FUNCTION, vector<DecoraterArgDef>({}) } },
    { TYPE_DOUBLE, { "ToDouble", SYNTAX_FUNCTION, vector<DecoraterArgDef>({}) } },
    { TYPE_INT32, { "ToInt32", SYNTAX_FUNCTION, vector<DecoraterArgDef>({}) } },
    { TYPE_INT64, { "ToInt64", SYNTAX_FUNCTION, vector<DecoraterArgDef>({}) } },
    { TYPE_UINT32, { "ToUnInt32", SYNTAX_FUNCTION, vector<DecoraterArgDef>({}) } },
    { TYPE_UINT64, { "ToUnInt64", SYNTAX_FUNCTION, vector<DecoraterArgDef>({}) } },
    { TYPE_STRING, { "ToString", SYNTAX_FUNCTION, vector<DecoraterArgDef>({}) } }
  };
};
};
