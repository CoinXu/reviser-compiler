/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description
 */

#include <iostream>
#include <fstream>

#include <message.h>
#include <parser.h>

using namespace reviser::compiler;

int main(int args, char** argv) {

  reviser::message::Message logger("main");
  logger.Info("args: " + std::to_string(args));

  for (int i = 0; i < args; ++i) {
    logger.Info("args::[" +  std::to_string(i) + "] = " + argv[i]);
  }

  if (args == 1) {
    return 1;
  }

  std::string filename = argv[1];

  logger.Info("open file: " + filename);

  // read file
  std::ifstream is(filename, std::ifstream::binary);

  if (!is) {
    logger.Runtime("not found file :" + filename);
  }

  is.seekg(0, is.end);
  int length = is.tellg();
  is.seekg(0, is.beg);

  char* buffer = new char [length];

  is.read(buffer, length);
  is.close();

  std::cout.write(buffer, length);

  // 转为string，传给Tokenizer
  std::string input(buffer, length);

  Tokenizer tokenizer(input);
  Parser parser(tokenizer);

  parser.Program();

  delete[] buffer;

  return 0;
}
