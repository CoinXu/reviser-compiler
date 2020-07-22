//
// @date 2020-07-22
// @author duanxian0605@163.com
// @description
//

#include <compiler/code_generator.h>
#include <map>

using namespace reviser::compiler;

namespace reviser {
  class CommandLineInterface {
  private:
    struct GeneratorInfo {
      CodeGenerator* generator;
      string help_text;
      string output_file_suffix;
    };

    typedef map<string, GeneratorInfo> GeneratorMap;

    struct OutputDirective {
      string name;
      CodeGenerator* generator;
      string output_location;
    };

    GeneratorMap generators;
    vector<OutputDirective> output_directives;
    vector<string> input_files;
    string version_info;
    string printer_name = "terminal";
    string executable_name;

    bool ParseArgument(const char* arg, string* name, string* value);
    bool ParseArguments(int argc, const char* const argv[]);
    bool InterpretArgument(const string& name, const string& value);
    void PrintHelpText();
    string MakeSourceCodeInputs(const string& path);

  public:
    CommandLineInterface();
    ~CommandLineInterface();

    void SetVersionInfo(const string& text);
    void RegisterGenerator(const string& name, CodeGenerator* generator, const string& help_text, const string& suffix);
    int Run(int argc, const char* const argv[]);
  };
};
