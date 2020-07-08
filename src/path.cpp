//
// @date 2020-07-08
// @author duanxian0605@163.com
// @description
//

#include <path.h>

using namespace std;

namespace reviser {
namespace path {
  //
  // @example
  // join("a", "b") => a/b
  // join("a/", "b/c//d") => a/b/c/d
  string join(const string& a, const string& b) {
    const char separator = '/';
    string temp_a = a;
    string temp_b = b;

    if (temp_a.back() != separator) {
      temp_a += separator;
    }

    if (temp_b.front() != separator) {
      temp_b = separator + temp_b;
    }

    string result = temp_a + temp_b;
    size_t index = 0;

    while (index < result.length()) {
      if (result[index] == separator && result[index + 1] == separator) {
        result.erase(index);
        continue;
      }
      index++;
    }

    return result;
  }
};
};
