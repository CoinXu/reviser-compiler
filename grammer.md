## 0.1.0

## 数据类型
```
type -> "bool" | "float" | "double" | "int32" | "int64" | "uint32" | "uint64" | "string"
```

## 字段限定标记
```
decorater -> "optional" | "required"
```

## 文法
```
struct  -> "struct" id "{" [structp { ";", structp }] "}"
structp -> [decorater { " ", decorater }] declare
declare -> "bool" id ["=" bool]
         | "float" id ["=" float]
         | "double" id ["=" double]
         | "int32" id ["=" int32]
         | "int64" id ["=" int64]
         | "uint32" id ["=" uint32]
         | "uint64" id ["=" uint64]
         | "string" id ["=" string]
         | id id "=" id "." id
id      -> letter (letter | digit)*
letter  -> a | ... | z | A | ... | Z | _
digit   -> 0 | ... | 9
enum    -> "enum" id "{" [enump { ",", enump }] "}"
enump   -> id ["=" int32]
bool    -> "true" | "false"
float   -> -3.402823669209385e+38 | ... | +3.402823669209385e+38
double  -> -1.79769313486232e308 | ... | +1.79769313486232e308
int32   -> -2,147,483,648 | ... | +2,147,483,648
int64   -> -9,223,372,036,854,775,808 | ... | +9,223,372,036,854,775,808
uint32  -> 0 | ... | 4294967295
uint64  -> 0 | ... | 18446744073709551615
string  -> "\"" [.*] "\""
```

## 程序
```
program -> { stmt }*
stmt    -> struct | enum
```
