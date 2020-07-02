//
//  @date 2020-07-02
//  @author duanxian0605@163.com
//  @description 输出到终端
//

#include <compiler/printer.h>

namespace reviser {
namespace compiler {
  class PrinterTerminal : Printer {
  public:
    bool Print(std::string message);

    PrinterTerminal();
    ~PrinterTerminal();
  };
};
};
