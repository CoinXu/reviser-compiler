/**
 * @date 2020-06-15
 * @author duanxian0605@gmail.com
 * @description
 */

#include <iostream>
#include <cstdlib>

#include <message.h>

namespace reviser {
namespace message {
  Message::Message(std::string name_): name(name_) {}
  Message::~Message() {}

  // private
  std::string Message::mark(std::string level) {
    return  name + " " + level + " " + std::to_string(line) + ":" + std::to_string(column);
  }

  // public
  void Message::Fatal(std::string msg) {
    std::cout << mark("fatal") + ": " << msg << std::endl;
    std::exit(EXIT_FAILURE);
  }

  void Message::Warn(std::string msg) {
    std::cout << mark("warn") + ": " << msg << std::endl;
  }

  void Message::Info(std::string msg) {
    std::cout << mark("info") + ": " << msg << std::endl;
  }

  void Message::Debug(std::string msg) {
    std::cout << mark("debug") + ": " << msg << std::endl;
  }

  void Message::Runtime(std::string msg) {
    throw std::runtime_error(mark("debug") + ": " + msg);
  }
} // message
} // reviser
