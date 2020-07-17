//
//  @date 2020-07-17
//  @author duanxian0605@163.com
//  @description 输出到文件
//

#include <io/printer.h>
#include <fstream>

namespace reviser {
namespace io {
  class PrinterFile : public Printer {
  private:
    std::ofstream stream;
    std::string path;

  public:
    bool Print(std::string message);

    PrinterFile(std::string path);
    ~PrinterFile();
  };
};
};
