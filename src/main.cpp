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
 * CLI args:
 * --ts-output={dirname}
 * --js-output={dirname}
 * --printer={terminal|fs}
 */

#include <iostream>
#include <fstream>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include <parser.h>
#include <io/path.h>
#include <io/printer_terminal.h>
#include <io/printer_file.h>
#include <cstdint>

using namespace reviser;
using namespace reviser::message;
using namespace reviser::io;
using namespace reviser::compiler;
using namespace reviser::javascript;
using namespace reviser::typescript;

enum CommandLineArg {
  CLI_OUTPUT_TS,
  CLI_OUTPUT_JS,
  CLI_PRINTER,
  CLI_PRINTER_TERMINAL,
  CLI_PRINTER_FS
};

map<CommandLineArg, string> CommandLineArgNameMap = {
  { CLI_OUTPUT_TS, "--ts-output" },
  { CLI_OUTPUT_JS, "--js-output" },
  { CLI_PRINTER, "--printer" },
  { CLI_PRINTER_FS, "fs" },
  { CLI_PRINTER_TERMINAL, "terminal" }
};

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int args, char** argv, char** envp) {
  signal(SIGSEGV, handler);

  const string pwd = string(getenv("PWD"));
  Message logger("main");

  logger.Info("args: " + to_string(args));

  string javascript_output;
  string typescript_output;
  string printer_type = CommandLineArgNameMap[CLI_PRINTER_TERMINAL];
  string original_source_file_name;
  string source_file_name;

  for (int i = 1; i < args; ++i) {
    logger.Info("args::[" +  to_string(i) + "] = " + argv[i]);
    string s = string(argv[i]);

    if (~s.find(CommandLineArgNameMap[CLI_OUTPUT_JS])) {
      javascript_output = s.substr(s.find("=") + 1);

      if (!io::absolute(javascript_output)) {
        javascript_output = io::join(pwd, javascript_output);
      }
    } else if (~s.find(CommandLineArgNameMap[CLI_OUTPUT_TS])) {
      typescript_output = s.substr(s.find("=") + 1);

      if (!io::absolute(typescript_output)) {
        typescript_output = io::join(pwd, typescript_output);
      }
    } else if (~s.find(CommandLineArgNameMap[CLI_PRINTER])) {
      printer_type = s.substr(s.find("=") + 1);
    } else {
      original_source_file_name = s;
      source_file_name = s;

      if (!io::absolute(source_file_name)) {
        source_file_name = io::join(pwd, source_file_name);
      }
    }
  }

  if (source_file_name.size() == 0) {
    logger.Info("no entry source file");
    return 1;
  }

  logger.Info("open file: " + source_file_name);

  // read file
  ifstream is(source_file_name, ifstream::binary);

  if (!is) {
    logger.Runtime("not found file :" + source_file_name);
  }

  is.seekg(0, is.end);
  int length = is.tellg();
  is.seekg(0, is.beg);

  char* buffer = new char [length];

  is.read(buffer, length);
  is.close();

  // 转为string，传给Tokenizer
  string input(buffer, length);

  if (javascript_output.size() > 0) {
    Printer* printer;

    if (printer_type == CommandLineArgNameMap[CLI_PRINTER_FS]) {
      string name = io::basename(original_source_file_name);
      printer = new PrinterFile(io::join(javascript_output, name + ".js"));
    } else if (printer_type == CommandLineArgNameMap[CLI_PRINTER_TERMINAL]) {
      printer = new PrinterTerminal();
    }

    Tokenizer tokenizer(input);
    JavaScriptGenerator javascript;
    Parser parser(&tokenizer, &javascript, printer);
    parser.Program();
  }

  if (typescript_output.size() > 0) {
    Printer* printer;

    if (printer_type == CommandLineArgNameMap[CLI_PRINTER_FS]) {
      string name = io::basename(original_source_file_name);
      printer = new PrinterFile(io::join(typescript_output, name + ".ts"));
    } else if (printer_type == CommandLineArgNameMap[CLI_PRINTER_TERMINAL]) {
      printer = new PrinterTerminal();
    }

    Tokenizer tokenizer(input);
    TypeScriptGenerator typescript;
    Parser parser(&tokenizer, &typescript, printer);
    parser.Program();
  }

  delete[] buffer;

  return 0;
}
