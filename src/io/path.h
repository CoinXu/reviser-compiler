//
// @date 2020-07-08
// @author duanxian0605@163.com
// @description
//

#include <string>

using namespace std;

namespace reviser {
namespace io {
  // 组合两个字符为一个合法的文件路径
  string join(const string&, const string&);

  // 判断一个路径是否是绝对路径
  bool absolute(const string&);

  // 修正非法路径，将多个/换成一个
  string normalize(const string&);

  string basename(const string&);

  bool is_dir(const string&);

  bool mkdir_parents(const string&, int mode = 0755);
};
};
