/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/typescript/typescript_generator.h>
#include <compiler/typescript/typescript_common.h>
#include <compiler/typescript/typescript_enum.h>
#include <compiler/typescript/typescript_struct.h>

namespace reviser {
namespace compiler {
  std::map<string, string> TypeScriptDecoraterNameMap = {
    { ReservedWordMap[RESERVED_OPTIONAL], "Optional" },
    { ReservedWordMap[RESERVED_REQUIRED], "Required" }
  };

  std::map<DataType, string> TypeScriptDataTypeDecoraterNameMap = {
    { TYPE_BOOL, "TypeBoolean" },
    { TYPE_FLOAT, "TypeFloat" },
    { TYPE_DOUBLE, "TypeDouble" },
    { TYPE_INT32, "TypeInt32" },
    { TYPE_INT64, "TypeInt64" },
    { TYPE_UINT32, "TypeUnInt32" },
    { TYPE_UINT64, "TypeUnInt64" },
    { TYPE_STRING, "TypeString" }
  };

  std::map<DataType, string> TypeScriptDataTypeMap = {
    { TYPE_BOOL, "number" },
    { TYPE_FLOAT, "number" },
    { TYPE_DOUBLE, "number" },
    { TYPE_INT32, "number" },
    { TYPE_INT64, "number" },
    { TYPE_UINT32, "number" },
    { TYPE_UINT64, "number" },
    { TYPE_STRING, "string" }
  };

  TypeScriptGenerator::TypeScriptGenerator(): CodeGenerator(), message("typescript") {}

  TypeScriptGenerator::~TypeScriptGenerator() {}

  //
  // private
  string TypeScriptGenerator::Import() {
    // decorators
    string code_decorator = "import {";
    vector<string> decorators = descriptor->Decorators();
    for (vector<string>::iterator it = begin(decorators); it != end(decorators); it++ ) {
      if (TypeScriptDecoraterNameMap.find(*it) == TypeScriptDecoraterNameMap.end()) {
        message.Runtime("undefined error: " + *it + " not defined in decorators.");
      }
      code_decorator += " " + TypeScriptDecoraterNameMap.at(*it) + (next(it) == end(decorators) ? "" : ",");
    }
    code_decorator += "} from \"data-reviser\";";

    // data type
    string code_data_type = "import {";
    vector<DataType> types = descriptor->DataTypes();
    for (vector<DataType>::iterator it = begin(types); it != end(types); it++) {
      if (TypeScriptDataTypeDecoraterNameMap.find(*it) == TypeScriptDataTypeDecoraterNameMap.end()) {
        message.Runtime("undefined error: " + DataTypeName.at(*it) + " not defined in data types.");
      }
      code_data_type += " " + TypeScriptDataTypeDecoraterNameMap.at(*it) + (next(it) == end(types) ? "" : ",");
    }

    code_data_type += "} from \"data-reviser\";";


    return code_decorator + "\n" + code_data_type;
  }

  string TypeScriptGenerator::Export() {
    string code;

    if (descriptor->GlobalVariables().size() == 0) {
      return code;
    }

    code += "export {\n";
    vector<string> variables = descriptor->GlobalVariables();
    for (vector<string>::iterator it = begin(variables); it != end(variables); it++) {
      code += TypeScriptCommon::Indent(1) + *it + (*it == variables.back() ? "\n" : ",\n");
    }

    return code += "}";
  }

  //
  // public
  string TypeScriptGenerator::StmtStruct(Struct* s) {
    descriptor->AddGlobalVariable("Struct" + s->id->text);
    TypeScriptStruct g(s);
    return g.Generate();
  }

  string TypeScriptGenerator::StmtEnum(Enum* e) {
    TypeScriptEnum g(e);
    return g.Generate();
  }

  string TypeScriptGenerator::Generate() {
    string block_separetor = "\n\n";
    string line_commit = "// ";
    string code = line_commit + "\n"
      + line_commit + "language: TypeScript\n"
      + line_commit + "generated by reviser-comiper\n"
      + line_commit + "do not change this file\n"
      + line_commit + "see https://github.com/CoinXu/reviser-compiler\n"
      + line_commit + block_separetor;

    code += Import() + block_separetor;

    for (StmtSeqItem it: seq) {
      switch(it.type) {
        case STMT_TYPE_STRUCT:
          code += StmtStruct(structures.at(it.index)) + block_separetor;
          break;

        case STMT_TYPE_ENUM:
          code += StmtEnum(enums.at(it.index)) + block_separetor;
          break;

        default:
          break;
      }
    }

    return code + Export() + block_separetor;
  }

}; // typescript
}; // compiler
