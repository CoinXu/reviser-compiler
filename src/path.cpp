//
// @date 2020-07-08
// @author duanxian0605@163.com
// @description
//

#include <path.h>

using namespace std;

namespace reviser {
namespace path {
  const char separator = '/';

  //
  // @example
  // join("a", "b") => a/b
  // join("a/", "b/c//d") => a/b/c/d
  string join(const string& a, const string& b) {
    string temp_a = a;
    string temp_b = b;

    if (temp_a.back() != separator) {
      temp_a += separator;
    }

    if (temp_b.front() != separator) {
      temp_b = separator + temp_b;
    }

    return normalize(temp_a + temp_b);
  }

  //
  // @example
  // absolute("/f/b") => true
  // absolute("f/b") => false
  bool absolute(const string& path) {
    return normalize(path).front() == separator;
  }

  //
  // @example
  // normalize("//a//b/c//d/") => /a/b/c/d
  string normalize(const string& path) {
    string result = path;
    size_t index = 0;

    while (index < result.length()) {
      if (result[index] == separator && result[index + 1] == separator) {
        result.erase(index, 1);
        continue;
      }
      index++;
    }

    if (result.back() == separator) {
      result.erase(result.length() - 1, 1);
    }

    return result;
  }
};
};
