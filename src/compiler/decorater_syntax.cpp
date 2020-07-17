//
//  @date 2020-07-09
//  @author duanxian0605@163.com
//  @description
//

#include <compiler/decorater_syntax.h>
#include <tokenizer.h>

namespace reviser {
namespace compiler {
  std::map<std::string, ReviserSyntaxDefinition> ReviserSyntaxBuildIn = {
    {
      ReservedWordMap[RESERVED_REQUIRED],
      { "Required", SYNTAX_CALLABLE, { { ARG_STRING, true } } }
    }
  };

  std::map<ReviserType, ReviserSyntaxDefinition> ReviserMethodMap = {
    { REVISER_TYPE_BOOL, { "TypeBoolean", SYNTAX_CALLABLE, { { ARG_STRING, true } } } },
    { REVISER_TYPE_FLOAT, { "TypeFloat", SYNTAX_CALLABLE, { { ARG_STRING, true } } } },
    { REVISER_TYPE_DOUBLE, { "TypeDouble", SYNTAX_CALLABLE, { { ARG_STRING, true } } } },
    { REVISER_TYPE_INT32, { "TypeInt32", SYNTAX_CALLABLE, { { ARG_STRING, true } } } },
    { REVISER_TYPE_INT64, { "TypeInt64", SYNTAX_CALLABLE, { { ARG_STRING, true } } } },
    { REVISER_TYPE_UINT32, { "TypeUnInt32", SYNTAX_CALLABLE, { { ARG_STRING, true } } } },
    { REVISER_TYPE_UINT64, { "TypeUnInt64", SYNTAX_CALLABLE, { { ARG_STRING, true } } } },
    { REVISER_TYPE_STRING, { "TypeString", SYNTAX_CALLABLE, { { ARG_STRING, true } } } },
    {
      REVISER_TYPE_STRUCT,
      { "TypeStruct", SYNTAX_CALLABLE, { { ARG_STRUCT, false } } }
    },
    {
      REVISER_TYPE_ARRAY,
      { "TypeArray", SYNTAX_CALLABLE, { { ARG_ARRAY, true }, { ARG_STRING, true } } }
    },
    {
      REVISER_TYPE_ARRAY_STRUCT,
      { "TypeArrayStruct", SYNTAX_CALLABLE, { { ARG_STRUCT, false }, { ARG_STRING, true } } }
    },
    { REVISER_TO_BOOL, { "ToBoolean", SYNTAX_FUNCTION, {} } },
    { REVISER_TO_FLOAT, { "ToFloat", SYNTAX_FUNCTION, {} } },
    { REVISER_TO_DOUBLE, { "ToDouble", SYNTAX_FUNCTION, {} } },
    { REVISER_TO_INT32, { "ToInt32", SYNTAX_FUNCTION, {} } },
    { REVISER_TO_INT64, { "ToInt64", SYNTAX_FUNCTION, {} } },
    { REVISER_TO_UINT32, { "ToUnInt32", SYNTAX_FUNCTION, {} } },
    { REVISER_TO_UINT64, { "ToUnInt64", SYNTAX_FUNCTION, {} } },
    { REVISER_TO_STRING, { "ToString", SYNTAX_FUNCTION, {} } }
  };

};
};
