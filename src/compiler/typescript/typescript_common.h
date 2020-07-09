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
    DECORATER_CALLABLE,
    DECORATER_FUNCTION
  };

  enum TypeScriptDecoraterArgDataType {
    DECORATER_ARG_TYPE_NUMBER,
    DECORATER_ARG_TYPE_STRING,
    DECORATER_ARG_TYPE_JSON
  };

  struct TypeScriptArgDefinition {
    TypeScriptDecoraterArgDataType type;
    bool optional;
  };

  struct TypeScriptDecoraterDefinition {
    std::string name;
    TypeScriptDecoraterType type;
    vector<TypeScriptArgDefinition> args;
  };


  extern std::map<DataType, std::string> TypeScriptDataTypeDecoraterNameMap;
  extern std::map<DataType, std::string> TypeScriptDataTypeMap;

  extern std::map<std::string, TypeScriptDecoraterDefinition> TypeScriptBuildInDefinition;
  extern std::map<DataType, TypeScriptDecoraterDefinition> TypeScriptTranslatorDefinition;
  extern std::map<DataType, TypeScriptDecoraterDefinition> TypeScriptDataTypeDefinition;

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

    const static std::string DecoraterDefinition(TypeScriptDecoraterDefinition def) {
      switch (def.type) {
        case DECORATER_FUNCTION:
          return def.name;

        case DECORATER_CALLABLE:
          return def.name + "()";

        default:
          return "";
      }
    }

    const static std::string ImportId(TypeScriptDecoraterDefinition def) {
      return def.name;
    }
  };

};
};

#endif
