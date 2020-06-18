# data-reviser compiler
compile [data-reviser](https://github.com/CoinXu/data-reviser) code to javascript or typescript

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
2. execute `reviserc example.dr` will output code to the terminal
