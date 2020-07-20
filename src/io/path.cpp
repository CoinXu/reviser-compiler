//
// @date 2020-07-08
// @author duanxian0605@163.com
// @description
//

#include <regex>
#include <io/path.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

namespace reviser {
namespace io {
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

  string basename(const string& path) {
    std::regex reg("\\..*?$");
    return std::regex_replace(path, reg, "");
  }

  bool is_dir(const string& path) {
    if (path.size() == 0) {
      return false;
    }

    struct stat s;
    if (stat(path.c_str(), &s) == -1) {
      return false;
    }

    return s.st_mode & S_IFDIR;
  }

  bool mkdir_parents(const string& path, int mode) {
    int size = 0;
    string current;
    while (size < path.size()) {
      current.push_back(path[size++]);
      if (current.back() == separator) {
        if (!is_dir(current)) {
          if (mkdir(current.c_str(), mode) == -1) {
            return false;
          }
        }
      }
    }

    return true;
  }
};
};
