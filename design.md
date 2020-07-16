# 架构设计
```
source code -> lexer -> token stream -> parser -> AST -> code generation
```

# LEXER
词法分析，根据源码依赖产生Token
```
DATA_TYPES = ["bool", "float", "double", "int32", "int64", "string", "uint32", "uint64"]
DATA_STRUCT = ["struct", "enum"]
DECORATOR = ["required"]
OPERATOR = ["import", "package", "extends"]

BLOCK_START = "{"
BLOCK_END = "}"
STATEMENT_END = ";"
IDENTIFIER = /[a-zA-Z_]+[a-zA-Z0-9_]*/
DIGIT = /[0-9]+|[0-9]*\.[0-9]+|0x[0-9A-F]/
LETTER = /[a-zA-Z0-0_]/
```
### Example
```
struct Foo {
    required string foo "";
}

<DATA_STRUCT, struct>
<IDENTIFIER, Foo>
<BLOCK_START, {>
<DECORATOR, required>
<DATA_TYPE, string>
<IDENTIFIER, foo>
<LETTER, "">
<STATEMENT_END, ;>
<BLOCK_END, }>
```

# PARSING
语法分析，根据Token生成AST

# AST
定义`.reviser`代码

# CODE GENERATION
根据AST生成各类代码，如JavaScript\TypeScript
