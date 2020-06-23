/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_JAVASCRIPT_COMMON
#define REVISER_COMPILER_JAVASCRIPT_COMMON

#include <string>

namespace reviser {
namespace compiler {
  class JavaScriptCommon {
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
