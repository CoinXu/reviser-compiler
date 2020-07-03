/**
 * @date 2020-06-22
 * @author duanxian0605@163.com
 * @description
 */

#ifndef REVISER_COMPILER_CODE_GENERATOR
#define REVISER_COMPILER_CODE_GENERATOR

#include <ast/expr.h>
#include <ast/stmt.h>
#include <ast/stmt_enum.h>
#include <ast/stmt_struct.h>
#include <compiler/descriptor.h>

using namespace reviser::ast;
using namespace std;

namespace reviser {
namespace compiler {
  class CodeGenerator {
  protected:
    enum StmtSeqItemType {
      STMT_TYPE_ENUM,
      STMT_TYPE_STRUCT
    };

    struct StmtSeqItem {
      StmtSeqItemType type;
      size_t index;
    };

    vector<StmtSeqItem> seq;
    vector<Struct*> structures;
    vector<Enum*> enums;

  public:
    Descriptor* descriptor;
    virtual string StmtStruct(Struct*);
    virtual string StmtEnum(Enum*);
    virtual string Generate();

    void AddStmtStruct(Struct*);
    void AddStmtEnum(Enum*);

    CodeGenerator();
    ~CodeGenerator();
  };
};
};

#endif
