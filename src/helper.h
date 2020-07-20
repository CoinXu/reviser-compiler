//
// @date 2020-07-20
// @author duanxian0605@163.com
// @description
//

#include <string>

using namespace std;

namespace reviser {
namespace helper {
  bool numeric_is_float(string);
  bool numeric_is_double(string);
  bool numeric_is_int32(string);
  bool numeric_is_int64(string);
  bool numeric_is_uint32(string);
  bool numeric_is_uint64(string);

  bool bool_is_bool(string);
  bool bool_is_true(string);
  bool bool_is_false(string);
}; // helper
}; // reviser
