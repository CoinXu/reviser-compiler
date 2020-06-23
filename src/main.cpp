/**
 *                  _
 *   _ __ _____   _(_)___  ___ _ __
 *  | '__/ _ \ \ / / / __|/ _ \ '__|
 *  | | |  __/\ V /| \__ \  __/ |
 *  |_|  \___| \_/ |_|___/\___|_|
 *
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description
 */

#include <iostream>
#include <fstream>

#include <parser.h>

using namespace reviser::compiler;

int main(int args, char** argv) {

  reviser::message::Message logger("main");
  logger.Info("args: " + to_string(args));

  for (int i = 0; i < args; ++i) {
    logger.Info("args::[" +  to_string(i) + "] = " + argv[i]);
  }

  if (args == 1) {
    return 1;
  }

  string filename = argv[1];

  logger.Info("open file: " + filename);

  // read file
  ifstream is(filename, ifstream::binary);

  if (!is) {
    logger.Runtime("not found file :" + filename);
  }

  is.seekg(0, is.end);
  int length = is.tellg();
  is.seekg(0, is.beg);

  char* buffer = new char [length];

  is.read(buffer, length);
  is.close();

  // 转为string，传给Tokenizer
  string input(buffer, length);

  JavaScriptGenerator javascript;
  TypeScriptGenerator typescript;
  CodeGenerator generator;

  Tokenizer tokenizer(input);
  Descriptor descriptor;

  Parser parser(&tokenizer, &javascript, &descriptor, JavaScript);
  // Parser parser(&tokenizer, &typescript, &descriptor, TypeScript);

  parser.Program();

  delete[] buffer;

  return 0;
}
