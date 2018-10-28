# Comment
```
// This is line comment.

/*
 * This is block comment.
 */
```

# Keyword

## Data types
+ bool
+ float
+ double
+ int32
+ int64
+ string
+ uint32
+ uint64

## Data struct
+ struct
+ enum

## DECORATE
+ required
+ maxlength
+ minlength
+ range
+ max
+ min
+ interval

## Semantics
+ package
+ import
+ extends

# Identifier
+ BLOCK_START: `{`.
+ BLOCK_END: `}`;
+ STATEMENT_END: `;`. 
+ STATEMENT_SEPARATOR: `,`
+ DECORATE: decorate.
+ TYPE: Data types or Data struct.
+ STRUCTURE: `struct` or `enum`.
+ NAME: Characters only allow `a-z`, `A-Z`, `0-9`, `_`. Do not start with `0-9`. 

# Define description mark.
+ []: optional
+ (): required
+ <>: description

# statement format:
## 1. struct
Format: [DECORATE][<SPACE>](TYPE)[<SPACE>](NAME)[<SPACE>][default](STATEMENT_END)

Example:
```
required string foo "foo";
bool bar true;
float baz 1.0;
```
## 2. enum
Format: (NAME)[<SPACE>][=[<SPACE>](int32 or string)](STATEMENT_SEPARATOR)

Example:
```
foo = 1,
bar = "bar",
baz
```

## 3. structure
Format: (STRUCTURE)<SPACE>(NAME)(BLOCK_START)[statement](BLOCK_END)

Example:
```
struct Foo {
  required string foo "foo";
  bool bar true;
}

enum Bar {
  foo = 1;
  bar = 2;	
}
```
