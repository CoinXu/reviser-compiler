/**
 * @date 2020-07-03
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/typescript/typescript_struct.h>
#include <compiler/typescript/typescript_expr.h>
#include <compiler/typescript/typescript_enum.h>
#include <compiler/typescript/typescript_common.h>

namespace reviser {
namespace typescript {
  //
  // TypeScriptStruct
  TypeScriptStruct::TypeScriptStruct(Struct* node): node(node) {
    node->level = 0;
  }

  TypeScriptStruct::TypeScriptStruct(Struct* node, TypeScriptStruct* parent)
    : node(node), parent(parent) {
      node->level = parent->node->level + 1;
    }

  TypeScriptStruct::~TypeScriptStruct() {
  }

  string TypeScriptStruct::Generate() {
    string indent = TypeScriptCommon::Indent(node->level);
    string indent_next = TypeScriptCommon::Indent(node->level + 1);

    vector<string> properties;
    string ns =  indent + "namespace Ns" + node->id->text + " {\n";

    for (vector<Struct::ContentStore>::iterator it = begin(node->contents);
      it != end(node->contents); it++) {
      const string new_line = next(it) == end(node->contents) ? "\n" : "\n\n";

      switch ((*it).type) {
        case DeclareProperty: {
          TypeScriptStructProperty g(node->properties.at((*it).index), this);
          properties.push_back(g.Generate() + new_line);
          break;
        }

        case DeclareStruct: {
          TypeScriptStruct g(node->structs.at((*it).index), this);
          ns += g.Generate() + new_line;
          break;
        }

        case DeclareEnum: {
          TypeScriptEnum g(node->enums.at((*it).index), this);
          ns += g.Generate() + new_line;
          break;
        }

        default:
          break;
      }
    }

    ns += indent_next + "export class " + node->id->text + " extends Reviser {\n";
    for (string p: properties) {
      ns += p;
    }
    ns += indent_next + "}\n";
    ns += indent + "}\n";

    return ns;
  }

  //
  // TypeScriptStructProperty
  TypeScriptStructProperty::TypeScriptStructProperty(StructProperty* node, TypeScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  TypeScriptStructProperty::~TypeScriptStructProperty() {
  }

  string TypeScriptStructProperty::Generate() {
    string code_decorater;
    for (Decorater* d: node->decoraters) {
      TypeScriptDecorater decorater(d, parent);
      code_decorater += decorater.Generate();
    }

    vector<string> revisers;
    vector<ReviserSyntaxDefinition> defs = TypeScriptCommon::FindReviserSyntaxDefinitionByDataType(node->declare->type);

    // 如果是数组类型数据，将translator放在TypeArray装饰器中
    if (node->declare->array_type) {
      switch (node->declare->type) {
        case TYPE_BOOL:
        case TYPE_FLOAT:
        case TYPE_DOUBLE:
        case TYPE_INT32:
        case TYPE_INT64:
        case TYPE_UINT32:
        case TYPE_UINT64:
        case TYPE_STRING: {
          vector<string> args;
          for (ReviserSyntaxDefinition d : defs) {
            args.push_back(TypeScriptCommon::DecoraterDefinition(d));
          }
          vector<DecoraterArg> v({{ ARG_ARRAY, args }});
          revisers.push_back(TypeScriptCommon::DecoraterDefinition(ReviserMethodMap[REVISER_TYPE_ARRAY], &v));
          break;
        }

        case TYPE_ENUM:
          break;

        case TYPE_STRUCT: {
          vector<DecoraterArg> v({{ ARG_STRING, vector<string>({ node->declare->type_id->text }) }});
          revisers.push_back(TypeScriptCommon::DecoraterDefinition(ReviserMethodMap[REVISER_TYPE_ARRAY_STRUCT], &v));
          break;
        }

        default:
          break;
      }
    } else {
      switch (node->declare->type) {
        case TYPE_BOOL:
        case TYPE_FLOAT:
        case TYPE_DOUBLE:
        case TYPE_INT32:
        case TYPE_INT64:
        case TYPE_UINT32:
        case TYPE_UINT64:
        case TYPE_STRING: {
          for (ReviserSyntaxDefinition d : defs) {
            revisers.push_back(TypeScriptCommon::DecoraterDefinition(d));
          }
          break;
        }

        case TYPE_ENUM:
          break;

        case TYPE_STRUCT: {
          vector<DecoraterArg> v({{ ARG_STRING, vector<string>({ node->declare->type_id->text }) }});
          revisers.push_back(TypeScriptCommon::DecoraterDefinition(ReviserMethodMap[REVISER_TYPE_STRUCT], &v));
          break;
        }

        default:
          break;
      }
    }

    string indent = TypeScriptCommon::Indent(node->level + 1);
    return (
        revisers.size() > 0
        ? indent + ("@" + TypeScriptCommon::JoinVector(revisers, "\n" + indent + "@") + "\n")
        : ""
      )
      + code_decorater + indent + TypeScriptDeclare(node->declare).Generate() + ";";
  }

  //
  // TypeScriptStructInterfaceProperty
  TypeScriptStructInterfaceProperty::TypeScriptStructInterfaceProperty(StructProperty* node, TypeScriptStruct* parent)
    : node(node), parent(parent) {
      node->level = parent->node->level + 1;
    }

  TypeScriptStructInterfaceProperty::~TypeScriptStructInterfaceProperty() {}

  string TypeScriptStructInterfaceProperty::Generate() {
    if (node->declare->type == TYPE_ENUM) {
      return TypeScriptCommon::Indent(node->level)
        + node->declare->id->text + ": " + node->declare->type_id->text
        + "; /* enum " + node->declare->type_id->text + " */";
    }

    string type;
    if (TypeScriptBuildInDataTypeMap.find(node->declare->type) == TypeScriptBuildInDataTypeMap.end()) {
      type = "any";
    } else {
      type = TypeScriptBuildInDataTypeMap.at(node->declare->type);
    }

    return TypeScriptCommon::Indent(node->level)
      + node->declare->id->text + ": " + type
      + "; /* " + DataTypeName.at(node->declare->type) + " */";
  }

  //
  // TypeScriptDecorater
  TypeScriptDecorater::TypeScriptDecorater(Decorater* node, TypeScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  TypeScriptDecorater::~TypeScriptDecorater() {
  }

  string TypeScriptDecorater::Generate() {
    if (ReviserSyntaxBuildIn.find(node->id->text) == ReviserSyntaxBuildIn.end()) {
      return "";
    }

    return TypeScriptCommon::Indent(node->level + 1)
      + "@"
      + TypeScriptCommon::DecoraterDefinition(ReviserSyntaxBuildIn.at(node->id->text))
      + "\n";
  }

}; // reviser
}; // compiler
