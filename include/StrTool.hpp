#ifndef _StrTool_H
#define _StrTool_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <cstdint>
namespace object {

	typedef std::string _String;
	typedef std::wstring _WString;
	typedef std::vector<_String> StringList;
	typedef std::vector<_WString> WStringList;

	//_String " \n\r\t" = " \n\r\t";
#define HEXLOOKUP "0123456789ABCDEF"

	class StrTool
	{
	public:
	  static bool	IsGbk(const char* str);
		//判断是否是acsii
		static bool isasciistring(const unsigned char* data, int maxlen);

		static bool IsUnicode(const unsigned char* data);

		static bool isunicodestring(const unsigned char* data, int maxlen);




	public:
		static void Split(const _String & s, const _String& delim, std::vector<_String> & elems);

		//https://github.com/lefticus/presentations/blob/master/PracticalPerformancePractices.md#smaller-code-is-faster-code-11
		static _String Escape(unsigned char ch, bool escapeSafe = true);

		static int IsValidUTF8Char(const char* data, int size);

		static _String Escape(const _String & s, bool escapeSafe = true);

		static bool Unescape(const _String & s, _String & result, bool quoted = true);

		static _String Trim(const _String & s, const _String & delim = " \n\r\t");
		static _String TrimLeft(const _String & s, const _String & delim = " \n\r\t");
		static _String TrimRight(const _String & s, const _String & delim = " \n\r\t");

		static _WString Trim(const _WString & s, const _WString & delim = L" \n\r\t");
		static _WString TrimLeft(const _WString & s, const _WString & delim = L" \n\r\t");
		static _WString TrimRight(const _WString & s, const _WString & delim = L" \n\r\t");

		static size_t Length(const char *s);

		static size_t Length(const wchar_t* s);
		
		static _String PadLeft(const _String & s, size_t minLength, char ch);
		//Conversion functions taken from: http://www.nubaria.com/en/blog/?p=289
		static _String Utf16ToUtf8(const _WString & wstr);
		static _WString PtrToWString(intptr_t ptr);
		static _String PtrToString(intptr_t ptr);

		static _String Utf16ToUtf8(const wchar_t* wstr);

		static _WString Utf8ToUtf16(const _String & str);

		static _WString Utf8ToUtf16(const char* str);

		static _String LocalCpToUtf8(const _String & str);

		static _String LocalCpToUtf8(const char* str);

		static std::vector<_String> Split(const _String &str, const _String &pattern);

		static std::vector<_WString> Split(const _WString &str, const _WString &pattern);
		static void Split(const _WString & s, const _WString& delim, std::vector<_WString> & elems);

		static _WString LocalCpToUtf16(const _String & str);
		static _WString LocalCpToUtf16(const char* str);

		//Taken from: https://stackoverflow.com/a/24315631
		static _String ReplaceAll(_String  s, const _String & from, const _String & to);

		static _WString ReplaceAll(_WString  s, const _WString & from, const _WString & to);

		static _String vsprintf(_In_z_ _Printf_format_string_ const char* format, va_list args);


		static _WString ToString(const _String& str);

		static _String ToString(const _WString& wstr);

		static	_String sprintf(_In_z_ _Printf_format_string_ const char* format, ...);

		static _WString vsprintf(_In_z_ _Printf_format_string_ const wchar_t* format, va_list args);
		static _WString sprintf(_In_z_ _Printf_format_string_ const wchar_t* format, ...);
		static _String ToLower(const _String & s);
		static bool StartsWith(const _String & str, const _String & prefix);
		static bool EndsWith(const _WString & str, const _WString & suffix);

		static bool EndsWith(const _String & str, const _String & suffix);

		static bool StartsWith(const _WString & str, const _WString & suffix);

		static int hex2int(char ch);

		static bool FromHex(const _String & text, std::vector<unsigned char> & data, bool reverse = false);

		static _String ToHex(unsigned long long value);

		static std::wstring UTF82Wide(const std::string& strUTF8);

		static std::wstring Ansi2Wide(const std::string& strAnsi);
		static std::string Wide2UTF8(const std::wstring& strWide);
		static std::string Wide2Ansi(const std::wstring strWide);
		static std::string Ansi2UTF8(const std::string& strAnsi);



		static _String ToHex(const /*unsigned*/ char* buffer, size_t size, bool reverse = false);
		//十六进制转二进制
		static std::string HexToBin(const std::string &strHex);

		static _String ToCompressedHex(const unsigned char* buffer, size_t size);

		static bool FromCompressedHex(const _String & text, std::vector<unsigned char> & data);
		static int hackicmp(const char* s1, const char* s2);

		template<typename T>
		static _String ToFloatingString(void* buffer);
		template<typename T>
		static _String ToIntegralString(void* buffer);

		static inline bool convertLongLongNumber(const char* str, unsigned long long & result, int radix);
		static inline bool convertNumber(const char* str, size_t & result, int radix);

		static size_t HexToNumber(const char* str);


	};

}
#endif //_StrTool_H
