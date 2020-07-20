//
// @date 2020-07-20
// @author duanxian0605@163.com
// @description
//

#include <helper.h>
#include <limits>
#include <tokenizer.h>

using namespace reviser::compiler;

namespace reviser {
namespace helper {
  bool numeric_is_float(string text) {
    long double value = std::stold(text);
    return value >= numeric_limits<float>::lowest()
      && value <= numeric_limits<float>::max();
  }

  bool numeric_is_double(string text) {
    long double value = std::stold(text);
    return value >= numeric_limits<double>::lowest()
      && value <= numeric_limits<double>::max();
  };

  bool numeric_is_int32(string text) {
    long double value = std::stold(text);
    int min = numeric_limits<int>::lowest();
    int max = numeric_limits<int>::max();
    return value >= min && value <= max;
  };

  bool numeric_is_int64(string text) {
    long double value = std::stold(text);
    long int min = numeric_limits<long int>::lowest();
    long int max = numeric_limits<long int>::max();
    return value >= min && value <= max;
  };

  bool numeric_is_uint32(string text) {
    long double value = std::stold(text);
    unsigned int min = numeric_limits<unsigned int>::lowest();
    unsigned int max = numeric_limits<unsigned int>::max();
    return value >= min && value <= max;
  };

  bool numeric_is_uint64(string text) {
    long double value = std::stold(text);
    unsigned long int min = numeric_limits<unsigned long int>::lowest();
    unsigned long int max = numeric_limits<unsigned long int>::max();
    return value >= min && value <= max;
  };

  bool bool_is_true(string text) {
    return text == ReservedWordMap[RESERVED_TRUE];
  }

  bool bool_is_false(string text) {
    return text == ReservedWordMap[RESERVED_FALSE];
  }

  bool bool_is_bool(string text) {
    return bool_is_true(text) || bool_is_false(text);
  }
}; // helper
}; // reviser
