/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_generator.h>
#include <compiler/javascript/javascript_common.h>
#include <compiler/javascript/javascript_enum.h>
#include <compiler/javascript/javascript_struct.h>

namespace reviser {
namespace compiler {
  std::map<string, string> JavaScriptDecoraterNameMap = {
    { ReservedWordMap[RESERVED_OPTIONAL], "Optional" },
    { ReservedWordMap[RESERVED_REQUIRED], "Required" }
  };

  std::map<DataType, string> JavaScriptDataTypeDecoraterNameMap = {
    { TYPE_BOOL, "TypeBoolean" },
    { TYPE_FLOAT, "TypeFloat" },
    { TYPE_DOUBLE, "TypeDouble" },
    { TYPE_INT32, "TypeInt32" },
    { TYPE_INT64, "TypeInt64" },
    { TYPE_UINT32, "TypeUnInt32" },
    { TYPE_UINT64, "TypeUnInt64" },
    { TYPE_STRING, "TypeString" }
  };

  JavaScriptGenerator::JavaScriptGenerator(): CodeGenerator(), message("javascript") {}

  JavaScriptGenerator::~JavaScriptGenerator() {}

  //
  // private
  string JavaScriptGenerator::Import() {
    // decorators 
    string code_decorator = "import {";
    vector<string> decorators = descriptor->Decorators();
    for (vector<string>::iterator it = begin(decorators); it != end(decorators); it++ ) {
      if (JavaScriptDecoraterNameMap.find(*it) == JavaScriptDecoraterNameMap.end()) {
        message.Runtime("undefined error: " + *it + " not defined in decorators.");
      }
      code_decorator += " " + JavaScriptDecoraterNameMap.at(*it) + (*it == decorators.back() ? " " : ", ");
    }
    code_decorator += "} from \"data-reviser\";";

    // data type
    string code_data_type = "import {";
    vector<DataType> types = descriptor->DataTypes();
    for (vector<DataType>::iterator it = begin(types); it != end(types); it++) {
      if (JavaScriptDataTypeDecoraterNameMap.find(*it) == JavaScriptDataTypeDecoraterNameMap.end()) {
        message.Runtime("undefined error: " + DataTypeName.at(*it) + " not defined in data types.");
      }
      code_data_type += " " + JavaScriptDataTypeDecoraterNameMap.at(*it) + (*it == types.back() ? " " : ", ");
    }

    code_data_type += "} from \"data-reviser\";";


    return code_decorator + "\n" + code_data_type;
  }

  string JavaScriptGenerator::Export() {
    string code;

    if (descriptor->GlobalVariables().size() == 0) {
      return code;
    }

    code += "export {";
    vector<string> variables = descriptor->GlobalVariables();
    for (vector<string>::iterator it = begin(variables); it != end(variables); it++) {
      code += JavaScriptCommon::Indent(1) + *it + (*it == variables.back() ? " " : ", ");
    }

    return code += "}";
  }

  //
  // public
  string JavaScriptGenerator::StmtStruct(Struct* s) {
    JavaScriptStruct g(s);
    return g.Generate();
  }

  string JavaScriptGenerator::StmtEnum(Enum* e) {
    JavaScriptEnum g(e);
    return g.Generate();
  }

  string JavaScriptGenerator::Generate() {
    string code = Import() + "\n";

    for (StmtSeqItem it: seq) {
      switch(it.type) {
        case STMT_TYPE_STRUCT:
          code += StmtStruct(structures.at(it.index));
          break;

        case STMT_TYPE_ENUM:
          code += StmtEnum(enums.at(it.index));
          break;

        default:
          break;
      }
    }

    for (auto s : structures) {
      delete s;
    }
    structures.clear();

    for (auto e : enums) {
      delete e;
    }
    enums.clear();

    return code + "\n" + Export() + "\n";
  }

}; // javascript
}; // compiler
