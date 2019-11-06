#include"SdkUtil.h"
#include <windows.h>
#include <time.h>

std::string get_randrom_string(int length)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	srand((unsigned)time(NULL));
	std::string str;
	for (int i = 0; i < length; ++i) {
		str += alphanum[rand() % (sizeof(alphanum) - 1)];
	}

	return str;
}

std::string int_to_string(int i)
{
	char buf[20];
	_itoa_s(i, buf, 10);
	return std::string(buf);
}
std::wstring Utf8ToWide(const char* str) {
	DWORD dwNum = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wchar_t *pwText;
	pwText = new wchar_t[dwNum];
	if (!pwText)
	{
		delete[]pwText;
	}
	MultiByteToWideChar(CP_UTF8, 0, str, -1, pwText, dwNum);
	std::wstring result(pwText);
	return result;
}

std::string GBKToUTF8(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	std::string ret(str);
	delete[]str;
	return ret;
}
std::string UTF8ToGBK(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	std::string ret(str);
	delete[]str;
	return ret;
}
std::string WChar2Ansi(const wchar_t* pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	if (nLen <= 0) return std::string("");
	char* pszDst = new char[nLen];
	if (NULL == pszDst) return std::string("");
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen - 1] = 0;
	std::string strTemp(pszDst);
	delete[] pszDst;
	return strTemp;
}

std::string WChatToUTF8Str(wchar_t* gb2312) {
	int len = 0;
	len = WideCharToMultiByte(CP_UTF8, 0, gb2312, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, gb2312, -1, str, len, NULL, NULL);
	std::string ret(str);
	delete[]str;
	return ret;
}

std::wstring Ansi2WChar(const char* pwszSrc) {
	DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, pwszSrc, -1, NULL, 0);
	wchar_t *pwText;
	pwText = new wchar_t[dwNum];
	if (!pwText)
	{
		delete[]pwText;
	}
	MultiByteToWideChar(CP_ACP, 0, pwszSrc, -1, pwText, dwNum);

	std::wstring wstrRet(pwText);
	delete[]pwText;
	pwText = NULL;
	return wstrRet;
}
