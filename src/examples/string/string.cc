#include <iostream>

#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"

int main(int argc, char** argv) {

  base::string16 str16 = L"This is a test string. 这是中文测试";
  std::cout << "Output string utf16: " << str16.c_str() << std::endl;

  std::string str_utf8 = base::WideToUTF8(str16);
  std::cout << "Output string utf8: " << str_utf8.c_str() << std::endl;

  base::string16 str_utf16 = base::UTF8ToWide(str_utf8);

  std::cout << "Output string utf16: " << str_utf16.c_str() << std::endl;

  std::wstring wstr = base::UTF16ToWide(str_utf16);

  std::cout << "Output wstring: " << wstr.c_str() << std::endl;
  
  return 0;
}