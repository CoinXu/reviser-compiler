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

    string code_type;
    if (DecoraterSyntaxTranslator.find(node->declare->type) != DecoraterSyntaxTranslator.end()) {
      // 如果是数组类型数据，将translator放在TypeArray装饰器中
      if (!node->declare->array_type) {
        code_type += TypeScriptCommon::Indent(node->level + 1)
          + "@"
          + TypeScriptCommon::DecoraterDefinition(DecoraterSyntaxTranslator.at(node->declare->type))
          + "\n";
      }
    }

    if (DecoraterSyntaxDataType.find(node->declare->type) != DecoraterSyntaxDataType.end()) {
      if (node->declare->array_type) {
        vector<DecoraterArg> args({
          { 
            ARG_ARRAY, 
            vector<string>({ 
              TypeScriptCommon::DecoraterDefinition(DecoraterSyntaxDataType[node->declare->type]),
              TypeScriptCommon::DecoraterDefinition(DecoraterSyntaxTranslator[node->declare->type]) 
            }) 
          }
        });

        code_type += TypeScriptCommon::Indent(node->level + 1)
          + "@"
          + TypeScriptCommon::DecoraterDefinition(DecoraterSyntaxDataType[TYPE_ARRAY], &args)
          + "\n";
      } else {
        code_type += TypeScriptCommon::Indent(node->level + 1)
          + "@"
          + TypeScriptCommon::DecoraterDefinition(DecoraterSyntaxDataType.at(node->declare->type))
          + "\n";
      }
   }

    TypeScriptDeclare declare(node->declare);
    return code_type + code_decorater + TypeScriptCommon::Indent(node->level + 1) + declare.Generate() + ";";
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
        + node->declare->id->text + ": " + node->declare->eid->text
        + "; /* enum " + node->declare->eid->text + " */";
    }

    string type;
    if (TypeScriptDataTypeMap.find(node->declare->type) == TypeScriptDataTypeMap.end()) {
      type = "any";
    } else {
      type = TypeScriptDataTypeMap.at(node->declare->type);
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
    if (DecoraterSyntaxBuildIn.find(node->id->text) == DecoraterSyntaxBuildIn.end()) {
      return "";
    }

    return TypeScriptCommon::Indent(node->level + 1)
      + "@"
      + TypeScriptCommon::DecoraterDefinition(DecoraterSyntaxBuildIn.at(node->id->text))
      + "\n";
  }

}; // reviser
}; // compiler
