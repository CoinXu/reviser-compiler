/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_JAVASCRIPT_ENUM
#define REVISER_JAVASCRIPT_ENUM

#include <compiler/javascript/javascript_stmt.h>
#include <compiler/javascript/javascript_struct.h>
#include <ast/stmt_enum.h>

using namespace reviser::ast;
using namespace reviser::message;
using namespace std;

namespace reviser {
namespace javascript {
  class JavaScriptEnum : public JavaScriptStmt {
  public:
    JavaScriptStruct* parent = nullptr;
    Enum* node = nullptr;

    string Generate();
    JavaScriptEnum(Enum* node);
    JavaScriptEnum(Enum* node, JavaScriptStruct* parent);
    ~JavaScriptEnum();
  };

  class JavaScriptEnumProperty : public JavaScriptStmt {
  public:
    JavaScriptEnum* parent = nullptr;
    EnumProperty* node = nullptr;

    string Generate(int index = 0);
    JavaScriptEnumProperty(EnumProperty* node, JavaScriptEnum* parent);
    ~JavaScriptEnumProperty();
  };
};
};

#endif
