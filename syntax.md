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

## Data Structure
+ struct
+ enum

## Decorate
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
+ block start: `{`.
+ block end: `}`;
+ statement end: `;`. 
+ decorate: Decorate.
+ type: Data Types.
+ structure: `struct` or `enum`.
+ name: Characters only allow `a-z`, `A-Z`, `0-9`, `_`. Do not start with `0-9`. 

# Define description mark.
+ []: optional
+ (): required
+ <>: description

# statement format:
## 1. struct
Format:  [decorate][<SPACE>](type)[<SPACE>](name)[<SPACE>][default](end)

Example:
```
required string foo "foo";
bool bar true;
float baz 1.0;
```
## 2. enum
Format: (name)[<SPACE>]=[<SPACE>](int32 or string)

Example:
```
foo = 1;
bar = "bar";
```

## 3. Structure
Format: (structure)<SPALCE>(name)(block start)[statement](block end);

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
