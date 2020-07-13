/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_TYPESCRIPT_COMMON
#define REVISER_TYPESCRIPT_COMMON

#include <string>
#include <map>
#include <tokenizer.h>
#include <compiler/decorater_syntax.h>

namespace reviser {
namespace typescript {
  extern std::map<DataType, std::string> TypeScriptDataTypeMap;

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

    const static std::string DecoraterDefinition(DecoraterSyntaxDefinition def) {
      switch (def.type) {
        case SYNTAX_FUNCTION:
          return def.name;

        case SYNTAX_CALLABLE:
          return def.name + "()";

        default:
          return "";
      }
    }

    const static std::string ImportId(DecoraterSyntaxDefinition def) {
      return def.name;
    }
  };

};
};

#endif
