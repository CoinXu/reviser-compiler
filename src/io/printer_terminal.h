//
//  @date 2020-07-02
//  @author duanxian0605@163.com
//  @description 输出到终端
//

#include <io/printer.h>

namespace reviser {
namespace io {
  class PrinterTerminal : public Printer {
  public:
    bool Print(std::string message);

    PrinterTerminal();
    ~PrinterTerminal();
  };
};
};
