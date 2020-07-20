# Architecture
```
source code -> tokenizer -> token stream -> parser -> ast -> code generation
```

# Source Code (Grammer)
设计源码也就是设计文法，文法中定义了合法语句与表达式。`dr`因基需求简单，语句、表达式简单，所以采用了上下文无关文法(CFG)以降低实现难度与代码复杂度，详细文法参考[grammer.md](./grammer.md)。

# Tokenizer
将`source code`解析为一个个的结构化描述，以供`parser`使用。在该阶段，不关注语法。但可以做一些基本解析，比如将字符数值转为真实数值、标记保留字、特殊类型，忽略空行、注册等。

# Parser
该阶段依次读取token，根据文法判断token是否出现在正确的位置，如果校验失败，抛出异常，停止解析。同时会校验数据类型，初始值。

在解析过程中，生成各个语句、表达式对应的`AST`。同时可以标记一些辅助字段，以供`Generator`可以快速计算并使用。

此外，该阶段定义了`grammer`中不曾定义的作用域。

# AST
`AST`是以编译器实现语言可直接运行的一种结构化语言描述源码。主要分为两部分，`statement`与`expr`。

假设要描述如下源码
```dr
int32 foo = 1;
```
该段源码可以定义为一个expr，也可以定义为一个statement，简单起见，我们定义其为expr，并以Declare命名，以表示其为一个声明，ast代码如下
```c++
class Declare : public Expr {
public:
  DataType type;
  Token* id;
  RightValue* rv;
}
```
其中，`type`描述其数据类型，是一个`enum`值，`id`描述了其标识符，此处为`foo`，使用`RightValue`定义其右值，此处为int32类型，值为1。

`AST`规划时主要考虑两个问题，其一是分类，其二是扩展。分类决定了其属于谁的基类，继承谁的属性，如果划分错了，那么继承来的属性也是一些不合理的属性。扩展性主要体现在属性定义上，这里有个简单的方法：解耦，一个属性就表示一个定义，不要多个定义用同一个属性表示，这样的设计在扩展的时候，影响的小范围会比较大。

# Generator
由于`dr`是生成的中间代码，如`js`，`ts`等，所以没什么好说的。
