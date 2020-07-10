# data-reviser compiler
compile [data-reviser](https://github.com/CoinXu/data-reviser) code to javascript or typescript.

# Developer
1. base on vscode `Remote-Containers` https://code.visualstudio.com/docs/remote/containers
2. execute `Open folder in contaier` in vscode

# Install
```bash
make install
```

# Uninstall
```bash
make uninstall
```

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

# TODO
+ [x] support comment.
+ [x] compile to javascript.
+ [x] compile to typescript.
+ [ ] support `enum`, `array<T>`, `struct` types.
+ [ ] `decorator` allow parameters.
+ [x] check data type.
+ [x] support nested statement
+ [ ] support scope.
+ [ ] support package & import.
+ [ ] syntax highligth for editor.
+ [ ] delete all pointer.

# Licence
MIT
