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
namespace typescript {
  std::map<DataType, string> TypeScriptBuildInDataTypeMap = {
    { TYPE_BOOL, "boolean" },
    { TYPE_FLOAT, "number" },
    { TYPE_DOUBLE, "number" },
    { TYPE_INT32, "number" },
    { TYPE_INT64, "number" },
    { TYPE_UINT32, "number" },
    { TYPE_UINT64, "number" },
    { TYPE_STRING, "string" }
  };

  std::map<DataType, vector<ReviserType>> TypeScriptDataTypeReviserMap = {
    // { TYPE_BOOL, { REVISER_TYPE_BOOL, REVISER_TO_BOOLEAN } }
  };

  TypeScriptGenerator::TypeScriptGenerator(): CodeGenerator(), message("typescript") {}

  TypeScriptGenerator::~TypeScriptGenerator() {}

  //
  // private
  string TypeScriptGenerator::Import() {
    // decorators
    vector<string> deco(descriptor->Decorators());
    vector<string> decorators;

    for (vector<string>::iterator it = begin(deco); it != end(deco); it++ ) {
      if (ReviserSyntaxBuildIn.find(*it) == ReviserSyntaxBuildIn.end()) {
        message.Runtime("undefined error: " + *it + " not defined in decorators.");
      }
      decorators.push_back(TypeScriptCommon::ImportId(ReviserSyntaxBuildIn.at(*it)));
    }

    string code_decorator(
    );

    // data type
    vector<string> revisers;
    vector<DataType> types = descriptor->DataTypes();
    map<string, int> unique;

    if (descriptor->include_type_array) {
      revisers.push_back(TypeScriptCommon::ImportId(ReviserMethodMap[REVISER_TYPE_ARRAY]));
    }

    if (descriptor->include_struct_array) {
      revisers.push_back(TypeScriptCommon::ImportId(ReviserMethodMap[REVISER_TYPE_ARRAY_STRUCT]));
    }

    for (vector<DataType>::iterator it = begin(types); it != end(types); it++) {
      vector<ReviserSyntaxDefinition> defs = TypeScriptCommon::FindReviserSyntaxDefinitionByDataType(*it);
      for (ReviserSyntaxDefinition d : defs) {
        string id = TypeScriptCommon::ImportId(d);
        if (unique.find(id) == unique.end()) {
          unique[id] = 0;
          revisers.push_back(id);
        }
      }
    }

    return "import { Reviser } from \"data-reviser\";\n"
      "import { " + TypeScriptCommon::JoinVector(decorators, ", ") + " } from \"data-reviser\";"
      "import { " + TypeScriptCommon::JoinVector(revisers, ", ") + " } from \"data-reviser\";";
  }

  string TypeScriptGenerator::Export() {
    string code;

    if (descriptor->GlobalVariables().size() == 0) {
      return code;
    }

    code += "export {\n";
    string alias;
    vector<Descriptor::VariableDeclare> variables = descriptor->GlobalVariables();

    for (vector<Descriptor::VariableDeclare>::iterator it = begin(variables); it != end(variables); it++) {
      if ((*it).type == DECLARE_STRUCT) {
        alias += "const " + (*it).id + " = Ns" + (*it).id + "." + (*it).id + ";\n";
      }
      code += TypeScriptCommon::Indent(1) + (*it).id + (next(it) == end(variables) ? "\n" : ",\n");
    }

    return (alias.size() > 0 ? (alias + "\n") : "") + code += "}";
  }

  //
  // public
  string TypeScriptGenerator::StmtStruct(Struct* s) {
    TypeScriptStruct g(s);
    return g.Generate();
  }

  string TypeScriptGenerator::StmtEnum(Enum* e) {
    TypeScriptEnum g(e);
    return g.Generate();
  }

  string TypeScriptGenerator::Generate() {
    string block_separetor = "\n\n";
    string code(
      "//\n"
      "// language: TypeScript\n"
      "// generated by reviser-comiper\n"
      "// do not change this file\n"
      "// see https://github.com/CoinXu/reviser-compiler\n\n\n"
    );
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
