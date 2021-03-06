//
// language: JavaScript
// generated by reviser-comiper
// do not change this file
// see https://github.com/CoinXu/reviser-compiler


import { Reviser } from "data-reviser";
import { TypeBoolean, ToBoolean } from "data-reviser";

var Color = {
  Red: 1,
  Pink: 100,
  Blue: 200
};

var Bar = (function() {
  var Numberic = {
    Int32: 1,
    Float: 2,
    Double: 3
  };

  var Foo = (function() {
    class Foo extends Reviser {
    }
    return Foo;
  })();



  class Bar extends Reviser {
    @ToBoolean
    @TypeBoolean()
    b0 = true;

    @ToBoolean
    @TypeBoolean()
    b1 = false;
  }
  return Bar;
})();



export {
  Color,
  Bar
}

