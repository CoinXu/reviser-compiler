/**
 * @date 2018-10-28
 * @author duanxian0605@163.com
 * @description
 */

#include <iostream>
#include <fstream>

#include "tokenizer.h"

using namespace reviser::compiler;

int main(int args, char** argv) {
  std::cout << "args::" << args;
  for (int i = 0; i < args; ++i) {
    std::cout << "args::[" << i << "] = " << argv[i] << std::endl;
  }

  if (args == 1) {
    return 1;
  }

  char* filename = argv[1];

  std::cout << "open file: " << filename << std::endl;

  // read file
  std::ifstream is(filename, std::ifstream::binary);

  if (!is) {
    std::cout << "not found file [" << filename << "]";
    return 1;
  }

  is.seekg(0, is.end);
  int length = is.tellg();
  is.seekg(0, is.beg);

  char* buffer = new char [length];

  is.read(buffer, length);
  is.close();

  std::cout << "================ [" << filename << "] ================" << std::endl;
  std::cout.write(buffer, length);
  std::cout << "================ [" << filename << "] ================" << std::endl;


  // 转为string，传给Tokenizer
  std::string input(buffer, length);

  Tokenizer* tokenizer = new Tokenizer(input);
  while(tokenizer->Next()) {
    tokenizer->PrintfThreeAddressCode(&tokenizer->Current());
  };

  delete[] buffer;

  return 0;
}
