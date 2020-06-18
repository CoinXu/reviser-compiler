/**
 * @date 2020-06-15
 * @author duanxian0605@gmail.com
 * @description
 */

#ifndef REVISER_COMPILER_MESSAGE
#define REVISER_COMPILER_MESSAGE

#include <string>

namespace reviser {
namespace message {
  class Message {
  private:
    int line = 0;
    int column = 0;
    std::string name;

    std::string mark(std::string level);

  public:
    Message(std::string name);
    ~Message();

    void Fatal(std::string msg);
    void Warn(std::string msg);
    void Info(std::string msg);
    void Debug(std::string msg);
    void Runtime(std::string msg);
    void SetLine(int l) {
      line = l;
    }
    void SetColumn(int c) {
      column = c;
    }
  };
} // message
} // reviser

#endif
