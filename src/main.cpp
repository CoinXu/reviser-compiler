//
//                  _
//   _ __ _____   _(_)___  ___ _ __
//  | '__/ _ \ \ / / / __|/ _ \ '__|
//  | | |  __/\ V /| \__ \  __/ |
//  |_|  \___| \_/ |_|___/\___|_|
//
// @date 2018-10-28
// @author duanxian0605@163.com
// @description
// CLI args:
// --ts-output={dirname}
// --js-output={dirname}
// --printer={terminal|fs}
//


#include <execinfo.h>
#include <signal.h>
#include <unistd.h>
#include <command_line_interface.h>
#include <compiler/javascript/javascript_generator.h>
#include <compiler/typescript/typescript_generator.h>

#define REVISER_COMPILER_VERSION "0.1.1"

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

  CommandLineInterface cli;
  cli.SetVersionInfo(REVISER_COMPILER_VERSION);

  reviser::javascript::JavaScriptGenerator js_generator;
  cli.RegisterGenerator("--js-out", &js_generator,
    "Generate JavaScript source file", "js");

  reviser::typescript::TypeScriptGenerator ts_generator;
  cli.RegisterGenerator("--ts-out", &ts_generator,
    "Generate TypeScript source file", "ts");

  return cli.Run(args, argv);
}
