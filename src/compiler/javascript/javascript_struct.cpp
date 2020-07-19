/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#include <compiler/javascript/javascript_struct.h>
#include <compiler/javascript/javascript_expr.h>
#include <compiler/javascript/javascript_enum.h>
#include <compiler/javascript/javascript_common.h>

namespace reviser {
namespace javascript {
  //
  // JavaScriptStruct
  JavaScriptStruct::JavaScriptStruct(Struct* node): node(node) {
    node->level = 0;
  }

  JavaScriptStruct::JavaScriptStruct(Struct* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
      node->level = parent->node->level + 1;
    }

  JavaScriptStruct::~JavaScriptStruct() {
  }

  string JavaScriptStruct::Generate() {
    string indent = JavaScriptCommon::Indent(node->level);
    string indent_next = JavaScriptCommon::Indent(node->level + 1);

    vector<string> properties;
    string code = indent + "var " + node->id->text + " = (function() {\n";

    for (vector<Struct::ContentStore>::iterator it = begin(node->contents);
      it != end(node->contents); it++) {
      const string new_line = next(it) == end(node->contents) ? "\n" : "\n\n";

      switch ((*it).type) {
        case DeclareProperty: {
          JavaScriptStructProperty g(node->properties.at((*it).index), this);
          properties.push_back(g.Generate() + new_line);
          break;
        }

        case DeclareStruct: {
          JavaScriptStruct g(node->structs.at((*it).index), this);
          code += g.Generate() + new_line;
          break;
        }

        case DeclareEnum: {
          JavaScriptEnum g(node->enums.at((*it).index), this);
          code += g.Generate() + new_line;
          break;
        }

        default:
          break;
      }
    }

    code += indent_next + "class " + node->id->text + " extends Reviser {\n";
    for (string p: properties) {
      code = code + p;
    }
    code += indent_next + "}\n";
    code += indent_next + "return " + node->id->text + ";\n"; 

    return code + indent + "})();" + "\n\n";
  }

  //
  // JavaScriptStructProperty
  JavaScriptStructProperty::JavaScriptStructProperty(StructProperty* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  JavaScriptStructProperty::~JavaScriptStructProperty() {
  }

  string JavaScriptStructProperty::Generate() {
    string code_decorater;
    for (Decorater* d: node->decoraters) {
      JavaScriptDecorater decorater(d, parent);
      code_decorater += decorater.Generate();
    }

    vector<string> revisers;
    vector<ReviserSyntaxDefinition> defs = JavaScriptCommon::FindReviserSyntaxDefinitionByDataType(node->declare->type);

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
            args.push_back(JavaScriptCommon::DecoraterDefinition(d));
          }
          vector<DecoraterArg> v({{ ARG_ARRAY, args }});
          revisers.push_back(JavaScriptCommon::DecoraterDefinition(ReviserMethodMap[REVISER_TYPE_ARRAY], &v));
          break;
        }

        case TYPE_ENUM:
          break;

        case TYPE_STRUCT: {
          vector<DecoraterArg> v({{ ARG_STRING, vector<string>({ node->declare->type_id->text }) }});
          revisers.push_back(JavaScriptCommon::DecoraterDefinition(ReviserMethodMap[REVISER_TYPE_ARRAY_STRUCT], &v));
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
          for (int i = defs.size() - 1; i >= 0; i--) {
            revisers.push_back(JavaScriptCommon::DecoraterDefinition(defs.at(i)));
          }
          break;
        }

        case TYPE_ENUM:
          break;

        case TYPE_STRUCT: {
          vector<DecoraterArg> v({{ ARG_STRING, vector<string>({ node->declare->type_id->text }) }});
          revisers.push_back(JavaScriptCommon::DecoraterDefinition(ReviserMethodMap[REVISER_TYPE_STRUCT], &v));
          break;
        }

        default:
          break;
      }
    }

    string indent = JavaScriptCommon::Indent(node->level + 1);
    return (
        revisers.size() > 0
        ? indent + ("@" + JavaScriptCommon::JoinVector(revisers, "\n" + indent + "@") + "\n")
        : ""
      )
      + code_decorater + indent + JavaScriptDeclare(node->declare).Generate() + ";";
 
  }

  //
  // JavaScriptDecorater
  JavaScriptDecorater::JavaScriptDecorater(Decorater* node, JavaScriptStruct* parent)
    : node(node), parent(parent) {
    node->level = parent->node->level + 1;
  }

  JavaScriptDecorater::~JavaScriptDecorater() {
  }

  string JavaScriptDecorater::Generate() {
    if (ReviserSyntaxBuildIn.find(node->id->text) == ReviserSyntaxBuildIn.end()) {
      return "";
    }

    return JavaScriptCommon::Indent(node->level + 1)
      + "@"
      + JavaScriptCommon::DecoraterDefinition(ReviserSyntaxBuildIn.at(node->id->text))
      + "\n";
  }

}; // reviser
}; // compiler
