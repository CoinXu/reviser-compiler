//
// @date 2020-07-22
// @author duanxian0605@163.com
// @description
// format: --foo=bar --bar=baz

#include <cstring>
#include <iostream>
#include <fstream>
#include <command_line_interface.h>
#include <io/path.h>
#include <io/printer.h>
#include <io/printer_terminal.h>
#include <io/printer_file.h>
#include <parser.h>
#include <tokenizer.h>

using namespace reviser::io;

namespace reviser {
  //
  // public
  CommandLineInterface::CommandLineInterface() {}

  CommandLineInterface::~CommandLineInterface() {}

  void CommandLineInterface::SetVersionInfo(const string& text) {
    version_info = text;
  }

  void CommandLineInterface::RegisterGenerator(const string& name,
    CodeGenerator* generator, const string& help_text, const string& suffix) {
    GeneratorInfo info;
    info.generator = generator;
    info.help_text = help_text;
    info.output_file_suffix = suffix;
    generators[name] = info;
  }

  int CommandLineInterface::Run(int argc, const char* const argv[]) {
    if (!ParseArguments(argc, argv)) {
      return -1;
    }

    for (int i = 0; i < input_files.size(); i++) {
      for (int j = 0; j < output_directives.size(); j++) {
        OutputDirective directive = output_directives.at(j);
        GeneratorMap::const_iterator iter = generators.find(directive.name);
        Printer* printer;


        if (printer_name == "fs") {
          string output = io::absolute(directive.output_location)
            ? directive.output_location
            : io::join(string(getenv("PWD")), directive.output_location);
          string file_name = io::basename(input_files.at(i)) + "." + iter->second.output_file_suffix;
          printer = new PrinterFile(io::join(output, file_name));
        } else if (printer_name == "terminal") {
          printer = new PrinterTerminal();
        } else {
          cerr << "unkown printer type name: " << printer_name << endl;
          return -1;
        }

        Tokenizer tokenizer(MakeSourceCodeInputs(input_files.at(i)));
        Parser parse(&tokenizer, iter->second.generator, printer);
        parse.Program();
        delete printer;
      }
    }

    return 0;
  }

  //
  // private
  bool CommandLineInterface::ParseArguments(int argc, const char* const argv[]) {
    executable_name = argv[0];

    for (int i = 1; i < argc; i++) {
      string name, value;

      if (ParseArgument(argv[i], &name, &value)) {
        if (i + 1 == argc || argv[i + 1][0] == '-') {
          cerr << "missing value for flag: " << name << endl;
          return false;
        } else {
          i++;
          value = argv[i];
        }
      }

      if (!InterpretArgument(name, value)) {
        return false;
      }
    }

    if (input_files.empty()) {
      cerr << "missing input file." << endl;
      return false;
    }

    if (output_directives.empty()) {
      cerr << "missing output directives." << endl;
      return false;
    }

    return true;
  }

  bool CommandLineInterface::ParseArgument(const char* arg, string* name, string* value) {
    bool parsed_value = false;

    if (arg[0] != '-') {
      name->clear();
      parsed_value = false;
      *value = arg;
      return false;
    } else if (arg[1] == '-') {
      const char* equals_post = strchr(arg, '=');
      if (equals_post != NULL) {
        *name = string(arg, equals_post - arg);
        *value = equals_post + 1;
        parsed_value = true;
      } else {
        *name = arg;
      }
    } else {
      if (arg[1] == '\0') {
        name->clear();
        *value = arg;
        parsed_value = true;
      } else {
        *name = string(arg, 2);
        *value = arg + 2;
        parsed_value = !value->empty();
      }
    }

    if (parsed_value) {
      return false;
    }

    // these are only flags that don't take a value
    if (*name == "-h" || *name == "--help" || *name == "--version") {
      return false;
    }

    return true;
  }

  bool CommandLineInterface::InterpretArgument(const string& name, const string& value) {
    if (name.empty()) {
      if (value.empty()) {
        cerr << "you seem to have passed an empty string as one of the arguments "
          "to " << executable_name << ". it is not valid input so the program "
          "is going to die now." << endl;
        return false;
      }
      // not a flag, just a filename
      input_files.push_back(value);
    } else if (name == "--printer") {
      if (value == "fs" || value == "terminal") {
        printer_name = value;
        return true;
      }
      cerr << "invalid value for --printer. must be <fs> or <terminal>." << endl;
      return false;
    } else if (name == "-h" || name == "--help") {
      PrintHelpText();
      return true;
    } else if (name == "--version") {
      if (!version_info.empty()) {
        cout << version_info << endl;
      }
      return false;
    } else {
      GeneratorMap::const_iterator iter = generators.find(name);

      if (iter == generators.end()) {
        cerr << "unkown flag: " << name << endl;
        return false;
      }

      OutputDirective directive;
      directive.name = name;
      directive.generator = iter->second.generator;
      directive.output_location = value;

      output_directives.push_back(directive);
    }

    return true;
  }

  void CommandLineInterface::PrintHelpText() {
    cerr << "Usage: " << executable_name << " [option] DR_FILE\n"
    "  --printer              Specify output type, <fs> will write code to a file on disk\n"
    "                         <terminal> will output to terminal. default <terminal>\n"
    "  --version              Show version info and exit.\n"
    "  -h, --help             Show this text and exit.\n"
    << endl;

    for (GeneratorMap::iterator iter = generators.begin();
      iter != generators.end(); iter++) {
      cerr << "  " << iter->first << "={OUT_DIR}"
        << string(13 - iter->first.size(), ' ')
        << iter->second.help_text << endl;
    }
  }

  string CommandLineInterface::MakeSourceCodeInputs(const string& path) {
    const string file_path = io::absolute(path)
      ? path
      : io::join(string(getenv("PWD")), path);

    ifstream f(file_path, ifstream::binary);

    if (!f) {
      cerr << "not found file : " << file_path;
      return "";
    }

    f.seekg(0, f.end);
    int length = f.tellg();
    f.seekg(0, f.beg);
    char* buffer = new char[length];
    f.read(buffer, length);
    f.close();

    string content(buffer, length);
    delete[] buffer;
    return content;
  }
};
