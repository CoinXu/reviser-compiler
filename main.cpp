/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description
 */

#include <iostream>
#include <fstream>

#include "tokenizer.h"

using namespace std;
using namespace reviser::tokenizer;

int main(int args, char** argv) {
  cout << "args::" << args;
  for (int i = 0; i < args; ++i) {
    cout << "args::[" << i << "] = " << argv[i] << endl;
  }

  if (args == 1) {
    return 1;
  }

  char* filename = argv[1];

  cout << "open file: " << filename << endl;

  // read file
  ifstream is(filename, ifstream::binary);
  
  if (!is) {
    cout << "not found file [" << filename << "]";
    return 1;
  }

  is.seekg(0, is.end);
  int length = is.tellg();
  is.seekg(0, is.beg);

  char* buffer = new char [length];

  is.read(buffer, length);
  is.close();

  cout << "================ [" << filename << "] ================" << endl;
  cout.write(buffer, length);
  cout << "================ [" << filename << "] ================" << endl;
  
  // delete[] buffer;

  // 转为string，传给Tokenizer
  string input(buffer);

  Tokenizer* tokenizer = new Tokenizer(input);
  while(tokenizer->Next()) {
    tokenizer->Printf(&tokenizer->Current());
  };
  
  return 0;
}
