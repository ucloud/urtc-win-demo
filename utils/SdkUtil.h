#pragma once
#include "stdio.h"
#include <string>

std::string get_randrom_string(int length);

std::string int_to_string(int i);

std::wstring Utf8ToWide(const char* str);

std::string GBKToUTF8(const char* gb2312);

std::string UTF8ToGBK(const char* utf8);

std::string WChar2Ansi(const wchar_t* pwszSrc);

std::string WChar2Ansi(const wchar_t* pwszSrc);

std::string WChatToUTF8Str(wchar_t* gb2312);

std::wstring Ansi2WChar(const char* pwszSrc);