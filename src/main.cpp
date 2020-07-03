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
#include <compiler/printer_terminal.h>

using namespace reviser::compiler;
using namespace reviser::message;

int main(int args, char** argv) {

  Message logger("main");

  logger.Info("args: " + to_string(args));
  string javascript_output;
  string typescript_output;
  string file_name;

  for (int i = 1; i < args; ++i) {
    logger.Info("args::[" +  to_string(i) + "] = " + argv[i]);
    string s = string(argv[i]);

    if (~s.find_first_of("--js-output")) {
      logger.Info("js = post: " + s.find_first_of("="));
      javascript_output = s.substr(s.find_first_of("="));
    } else if (~s.find_first_of("--ts-output")) {
      logger.Info("ts = post: " + s.find_first_of("="));
      typescript_output = s.substr(s.find_first_of("="));
    } else {
      file_name = s;
    }
  }

  if (file_name.size() == 0) {
    logger.Info("no entry source file");
    return 1;
  }

  logger.Info("open file: " + file_name);

  // read file
  ifstream is(file_name, ifstream::binary);

  if (!is) {
    logger.Runtime("not found file :" + file_name);
  }

  is.seekg(0, is.end);
  int length = is.tellg();
  is.seekg(0, is.beg);

  char* buffer = new char [length];

  is.read(buffer, length);
  is.close();

  // 转为string，传给Tokenizer
  string input(buffer, length);
  PrinterTerminal printer;

  if (javascript_output.size() > 0) {
    Tokenizer tokenizer(input);
    JavaScriptGenerator javascript;
    Parser parser(&tokenizer, &javascript, &printer);
    parser.Program();
  }

  if (typescript_output.size() > 0) {
    Tokenizer tokenizer(input);
    TypeScriptGenerator typescript;
    Parser parser(&tokenizer, &typescript, &printer);
    parser.Program();
  }

  delete[] buffer;

  return 0;
}
