# data-reviser compiler
compile [data-reviser](https://github.com/CoinXu/data-reviser) code to javascript or typescript.

# Developer
1. base on vscode `Remote-Containers` https://code.visualstudio.com/docs/remote/containers
2. execute `Remote-Containers: Open Folder In Contaier` in vscode then chose this project root dir.

# Install
```bash
make install
```

# Uninstall
```bash
make uninstall
```

# CLI Args
+ --ts-output={path} - specify typescript code output directory, may be a absolute path or relative path base on `pwd`
+ --js-output={path} - same as `--ts-output`, but for javascript code.
+ --printer={fs|terminal} - specify output type, `fs` will write code to a file on disk.  default `terminal`

# Example
1. create `example.dr` then type below:
   ```
   enum Color {
     Red = 1,
     Blue,
     Yellow
   }

   struct Foo {
     required string foo = "foo";
     bool baz = true;
     Color bar = Color.Red;
     int32 age = 0;
   }
   ```
2. execute `reviserc --ts-output=tsoutput example.dr` will output code to the terminal.

# Grammer
see [grammer.md](./grammer.md)

# TODO
+ [x] support comment.
+ [x] compile to javascript.
+ [x] compile to typescript.
+ [x] support `struct` types.
+ [x] support `array<struct>` types.
+ [x] support `enum`, `array<T>` types.
+ [x] ~~`decorator` allow parameters.~~
+ [x] check data type.
+ [x] support nested statement
+ [x] support scope.
+ [x] support write to file.
+ [ ] support package & import.
+ [x] syntax highligth for editor.
+ [ ] delete unused ast pointer.

# Licence
MIT
