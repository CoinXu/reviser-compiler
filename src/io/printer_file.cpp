//
//  @date 2020-07-17
//  @author duanxian0605@163.com
//  @description 输出到文件
//

#include <io/printer_file.h>
#include <io/path.h>

namespace reviser {
namespace io {
  PrinterFile::PrinterFile(std::string path): path(path) {
    mkdir_parents(path);
    stream.open(path, std::ios::out | std::ios::trunc);

    if (!stream.is_open()) {
      throw std::runtime_error("not found file in path [" + path + "]");
    }
  }

  PrinterFile::~PrinterFile() {
    stream.flush();
    stream.close();
  }

  bool PrinterFile::Print(std::string message) {
    stream << message;
    return true;
  }
};
};
