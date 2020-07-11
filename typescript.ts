[main][info] line 0, column 0: open file: /workspaces/reviser - compiler / example.dr
// 
// language: TypeScript
// generated by reviser-comiper
// do not change this file
// see https://github.com/CoinXu/reviser-compiler
// 

import { Reviser } from "data-reviser";
import { ToInt32, TypeInt32, ToDouble, TypeDouble, Required } from "data-reviser";

enum Color {
  Red,
  Pink = 100,
  Blue = 200
};

namespace ClassBar {
  export enum Foo {
    Foo
  };

  export class Baz extends Reviser {
    @ToInt32
    @TypeInt32()
    public baz: number = 1;

    @Required()
    public foo: Foo = Foo.Foo;
  }
}

class Bar extends Reviser {
  public color: Color = Color.Pink;

  @ToDouble
  @TypeDouble()
  public d: number = 1.23;

  @Required()
  public foo: ClassBar.Foo = ClassBar.Foo.Foo;
}


export {
  Color,
  Bar
}