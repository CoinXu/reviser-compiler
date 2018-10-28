/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description .reviser文件输入源
 */

#include <string>

namespace reviser {
namespace source {

  class InputSourceStream {
  private:
    std::string input;
    int line;
    int column;    
  };
} // reviser
} // source
