//
//  @date 2020-07-02
//  @author duanxian0605@163.com
//  @description 输出到终端
//

#include <compiler/printer_terminal.h>
#include <iostream>

namespace reviser {
namespace compiler {
  PrinterTerminal::PrinterTerminal() {}
  PrinterTerminal::~PrinterTerminal() {}

  bool PrinterTerminal::Print(std::string message) {
    std::cout << message;
    return true;
  }
};
};
