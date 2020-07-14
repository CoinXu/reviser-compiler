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

using namespace reviser::compiler;

namespace reviser {
namespace typescript {
  extern std::map<DataType, string> TypeScriptDataTypeMap;

  class TypeScriptCommon {
  

  public:
    const static int IndentSize = 2;

    const static string Indent(int level) {
      string s;
      for (int i = 0; i < level * IndentSize; i++) {
        s = s + " ";
      }
      return s;
    }

    const static string JoinVector(vector<string> v, string separator) {
      string result;

      for (vector<string>::const_iterator it = begin(v); it != end(v); it++) {
        result += *it;
        if (next(it) != end(v)) {
          result += separator;
        }
      }

      return result;
    } 

    const static string DecoraterSyntaxCallable(DecoraterSyntaxDefinition def, vector<DecoraterArg>* args) {
      vector<string> result;

      if (args) {
        for (DecoraterArg arg : *args)  {
          switch (arg.type) {
            case ARG_ARRAY:
              result.push_back("[" + JoinVector(arg.value, ", ") + "]");
              break;

            case ARG_NUMBER:
            case ARG_STRING:
            case ARG_STRUCT:
              result.push_back(JoinVector(arg.value, ", "));
              break;

            default:
              break;
          }
        }
      }

      return def.name + "(" + JoinVector(result, ", ") + ")";
    }

    const static string DecoraterDefinition(DecoraterSyntaxDefinition def, vector<DecoraterArg>* args = nullptr) {
      switch (def.type) {
        case SYNTAX_FUNCTION:
          return def.name;

        case SYNTAX_CALLABLE:
          return DecoraterSyntaxCallable(def, args);

        default:
          return "";
      }
    }

    const static string ImportId(DecoraterSyntaxDefinition def) {
      return def.name;
    }
  };

};
};

#endif
