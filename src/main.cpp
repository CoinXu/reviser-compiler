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
#include <path.h>
#include <compiler/printer_terminal.h>

using namespace reviser;
using namespace reviser::compiler;
using namespace reviser::message;

int main(int args, char** argv, char** envp) {

  Message logger("main");

  const string pwd = string(getenv("PWD"));
  logger.Debug("pwd: " + pwd);

  logger.Info("args: " + to_string(args));
  string javascript_output;
  string typescript_output;
  string file_name;

  for (int i = 1; i < args; ++i) {
    logger.Info("args::[" +  to_string(i) + "] = " + argv[i]);
    string s = string(argv[i]);

    if (~s.find("--js-output")) {
      javascript_output = s.substr(s.find("=") + 1);
    } else if (~s.find("--ts-output")) {
      typescript_output = s.substr(s.find("=") + 1);
    } else {
      file_name = s;
    }
  }


  file_name = path::join(pwd, file_name);

  if (file_name.size() == 0) {
    logger.Info("no entry source file");
    return 1;
  }

  logger.Info("open file: " + file_name);

  return 0;

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
