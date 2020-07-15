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
<<<<<<< HEAD
+ [x] support `struct` types.
+ [x] support `array<struct>` types.
=======
+ [ ] support `struct` types.
>>>>>>> 17701809e18e9e41a15f7bb7a2861df8a3e2e4b2
+ [x] support `enum`, `array<T>` types.
+ [ ] `decorator` allow parameters.
+ [x] check data type.
+ [x] support nested statement
+ [x] support scope.
+ [ ] support package & import.
+ [x] syntax highligth for editor.
+ [ ] delete unused ast pointer.

# Licence
MIT
