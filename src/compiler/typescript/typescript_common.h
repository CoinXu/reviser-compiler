/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_TYPESCRIPT_COMMON
#define REVISER_COMPILER_TYPESCRIPT_COMMON

#include <string>
#include <map>
#include <tokenizer.h>

namespace reviser {
namespace compiler {
  enum TypeScriptDecoraterType {
    DECORATER_CALLBLE,
    DECORATER_FUNCTIONAL
  };

  enum TypeScriptDecoraterArgDataType {
    DECORATER_ARG_TYPE_NUMBER,
    DECORATER_ARG_TYPE_STRING,
    DECORATER_ARG_TYPE_JSON
  };

  struct TypeScriptDecoraterArgDefinition {
    TypeScriptDecoraterArgDataType type;
    bool optional;
  };

  struct TypeScriptDecoraterDefinition {
    std::string name;
    TypeScriptDecoraterType type;
    vector<TypeScriptDecoraterArgDefinition> args;
  };


  extern std::map<std::string, std::string> TypeScriptDecoraterNameMap;
  extern std::map<DataType, std::string> TypeScriptDataTypeDecoraterNameMap;
  extern std::map<DataType, std::string> TypeScriptDataTypeTranslatorNameMap;
  extern std::map<DataType, std::string> TypeScriptDataTypeMap;

  extern std::map<std::string, TypeScriptDecoraterDefinition> TypeScriptBuildInDefinitionMap;
  extern std::map<DataType, TypeScriptDecoraterDefinition> TypeScriptDecoraterDefinitionMap;
  extern std::map<DataType, TypeScriptDecoraterDefinition> TypeScriptDataTYpeDefinitionMap;

  class TypeScriptCommon {
  public:
    const static int IndentSize = 2;

    const static std::string Indent(int level) {
      std::string s;
      for (int i = 0; i < level * IndentSize; i++) {
        s = s + " ";
      }
      return s;
    }
  };

};
};

#endif
