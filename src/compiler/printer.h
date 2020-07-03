//
//  @date 2020-07-02
//  @author duanxian0605@163.com
//  @description 输出接口
//

#ifndef REVISER_COMPILER_PRINTER
#define REVISER_COMPILER_PRINTER

#include <string>

namespace reviser {
namespace compiler {
  class Printer {
  public:
    virtual bool Print(std::string message) = 0;
  };
}; // reviser
}; // compiler

#endif
