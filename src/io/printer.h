//
//  @date 2020-07-02
//  @author duanxian0605@163.com
//  @description 输出接口
//

#ifndef REVISER_IO_PRINTER
#define REVISER_IO_PRINTER

#include <string>

namespace reviser {
namespace io {
  class Printer {
  public:
    virtual bool Print(std::string message) = 0;
  };
}; // reviser
}; // compiler

#endif
