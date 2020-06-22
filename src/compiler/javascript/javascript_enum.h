/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_JAVASCRIPT_ENUM
#define REVISER_COMPILER_JAVASCRIPT_ENUM

#include <compiler/javascript/javascript_stmt.h>
#include <ast/stmt_enum.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
  class JavaScriptEnum : public JavaScriptStmt {
  public:
    JavaScriptStmt* parent = NULL;
    Enum* node;

    std::string Generate();
    JavaScriptEnum(Enum* node);
    JavaScriptEnum(Enum* node, JavaScriptStmt* parent);
    ~JavaScriptEnum();
  };

  class JavaScriptEnumProperty : public JavaScriptStmt {
  public:
    JavaScriptEnum* parent;
    EnumProperty* node;

    std::string Generate(int index = 0);
    JavaScriptEnumProperty(EnumProperty* node, JavaScriptEnum* parent);
    ~JavaScriptEnumProperty();
  };
};
};

#endif
