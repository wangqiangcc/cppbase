#include <iostream>

#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "base/strings/string_split.h"
#include "base/strings/pattern.h"
#include "base/strings/string_util.h"

int main(int argc, char** argv)
{
	// string convert
	base::string16 str16 = L"This is a test string. 这是中文测试";
	std::cout << "Output string utf16: " << str16.c_str() << std::endl;

	std::string str_utf8 = base::WideToUTF8(str16);
	std::cout << "Output string utf8: " << str_utf8.c_str() << std::endl;

	base::string16 str_utf16 = base::UTF8ToWide(str_utf8);

	std::cout << "Output string utf16: " << str_utf16.c_str() << std::endl;

	std::wstring wstr = base::UTF16ToWide(str_utf16);

	std::cout << "Output wstring: " << wstr.c_str() << std::endl;

	// string split
	std::string input = "hello, test, bye";
	std::vector<std::string> tokens = base::SplitString(
		input, ",", base::TRIM_WHITESPACE, base::SPLIT_WANT_ALL);


	// string match more see pattern_unittest.cc
	base::StringPiece src = "https://github.com";
	base::StringPiece pattern = "*.com";
	bool bmatch = base::MatchPattern(src, pattern);
	bool bmatch2 = base::MatchPattern("Hello", "H?l?o");


	// string util

	std::string as = base::ToLowerASCII("AbcDefg");
	base::string16 ws = base::ToLowerASCII(L"AbcDefg");

	int cmp = base::CompareCaseInsensitiveASCII("abc", "Abc");

	bool bcmp = base::EqualsCaseInsensitiveASCII("abc", "Abc");

	std::string url = "//https://github.com/dnybz/cppbase//";
	std::string path;
	static const char kURLPathSeparator[] = "/";
	base::TrimString(url, kURLPathSeparator, &path);


	bool blfind = base::StartsWith(L"C:\\Windows\\AppCompat\\Programs", L"C:\\Windows\\AppCompat", base::CompareCase::SENSITIVE);
	bool brfind = base::EndsWith(L"C:\\Windows\\AppCompat\\Programs", L"\\AppCompat\\ProgramS", base::CompareCase::INSENSITIVE_ASCII);

	return 0;
}