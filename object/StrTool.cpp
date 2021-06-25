#include "../include/StrTool.hpp"

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <cstdint>
#include<regex>
namespace object {

		//判断是否是acsii
		bool StrTool::isasciistring(const unsigned char* data, int maxlen)
		{
			int len = 0;
			for (char* p = (char*)data; *p; len++, p++)
			{
				if (len >= maxlen)
					break;
			}

			if (len < 2 || len + 1 >= maxlen)
				return false;
			for (int i = 0; i < len; i++)
				if (!isprint(data[i]) && !isspace(data[i]))
					return false;

			return true;
		}

		bool  StrTool::IsGbk(const char* str)
		{
			unsigned int nBytes = 0;//GBK可用1-2个字节编码,中文两个 ,英文一个
			unsigned char chr = *str;
			bool bAllAscii = true; //如果全部都是ASCII,
			for (unsigned int i = 0; str[i] != '\0'; ++i) {
				chr = *(str + i);
				if ((chr & 0x80) != 0 && nBytes == 0) {// 判断是否ASCII编码,如果不是,说明有可能是GBK
					bAllAscii = false;
				}
				if (nBytes == 0) {
					if (chr >= 0x80) {
						if (chr >= 0x81 && chr <= 0xFE) {
							nBytes = +2;
						}
						else {
							return false;
						}
						nBytes--;
					}
				}
				else {
					if (chr < 0x40 || chr>0xFE) {
						return false;
					}
					nBytes--;
				}//else end
			}
			if (nBytes != 0) {   //违返规则
				return false;
			}
			if (bAllAscii) { //如果全部都是ASCII, 也是GBK
				return true;
			}
			return true;
		}


		bool StrTool::IsUnicode(const unsigned char* data) {
			try {
				wchar_t * wstr = (wchar_t*)data;
				_String convertedString;
				if (!wstr || !*wstr)
					return false;
				auto requiredSize = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
				if (requiredSize > 0)
				{
					convertedString.resize(requiredSize - 1);
					if (!WideCharToMultiByte(CP_UTF8, 0, wstr, -1, (char*)convertedString.c_str(), requiredSize, nullptr, nullptr))
						convertedString.clear();
				}
				return true;
			}
			catch (...) {
				return false;
			}
		}


		bool StrTool::isunicodestring(const unsigned char* data, int maxlen)
		{
			int len = 0;
			for (wchar_t* p = (wchar_t*)data; *p; len++, p++)
			{
				if (len >= maxlen)
					break;
			}

			if (len < 2 || len + 1 >= maxlen)
				return false;




			wchar_t c = 0;
			for (int i = 0; i < len * 2; i += 2)
			{

				if (data[i + 1]) //Extended ASCII only
				{

					//return IsTextUnicode(data, len, 0);
					return false;
				}

				if (!isprint(data[i]) && !isspace(data[i]))
				{
					//return IsUnicode(data);
					return false;
				}
			}
			return true;
		}




		 void StrTool::Split(const _String & s, const _String& delim, std::vector<_String> & elems)
		{
			 elems.clear();
			 std::regex reg(delim.c_str());
			 std::sregex_token_iterator it(s.begin(), s.end(), reg, -1);
			 std::sregex_token_iterator end;
			 for (; it != end; it++)
			 {
				 std::string x = it->str();
				 elems.push_back(x);
			 }
		}

		 void StrTool::Split(const _WString & s, const _WString& delim, std::vector<_WString> & elems)
		 {
			 elems.clear();
			 std::wregex reg(delim.c_str());
			 std::wsregex_token_iterator it(s.begin(), s.end(), reg, -1);
			 std::wsregex_token_iterator end;
			 for (;it != end;it++)
			 {
				 elems.push_back(it->str());
			 }
		 }

		

		 std::vector<_WString> StrTool::Split(const _WString &s, const _WString &pattern)
		 {
			 std::vector<_WString> elems;
			 Split(s, pattern, elems);
			 return elems;
		 }

		 std::vector<_String> StrTool::Split(const _String &str, const _String &pattern)
		 {
			 std::vector<_String> elems;
			 Split(str, pattern, elems);
			 return elems;
		 }

		//https://github.com/lefticus/presentations/blob/master/PracticalPerformancePractices.md#smaller-code-is-faster-code-11
		 _String StrTool::Escape(unsigned char ch, bool escapeSafe )
		{
			char buf[8] = "";
			switch (ch)
			{
			case '\0':
				return "\\0";
			case '\t':
				return escapeSafe ? "\\t" : "\t";
			case '\f':
				return "\\f";
			case '\v':
				return "\\v";
			case '\n':
				return escapeSafe ? "\\n" : "\n";
			case '\r':
				return escapeSafe ? "\\r" : "\r";
			case '\\':
				return escapeSafe ? "\\\\" : "\\";
			case '\"':
				return escapeSafe ? "\\\"" : "\"";
			case '\a':
				return "\\a";
			case '\b':
				return "\\b";
			default:
				if (!isprint(ch)) //unknown unprintable character
					sprintf_s(buf, "\\x%02X", ch);
				else
					*buf = ch;
				return buf;
			}
		}

		 int StrTool::IsValidUTF8Char(const char* data, int size)
		{
			if (*(unsigned char*)data >= 0xF8) //5 or 6 bytes
				return 0;
			else if (*(unsigned char*)data >= 0xF0) //4 bytes
			{
				if (size < 4)
					return 0;
				for (int i = 1; i <= 3; i++)
				{
					if ((*(unsigned char*)(data + i) & 0xC0) != 0x80)
						return 0;
				}
				return 4;
			}
			else if (*(unsigned char*)data >= 0xE0) //3 bytes
			{
				if (size < 3)
					return 0;
				for (int i = 1; i <= 2; i++)
				{
					if ((*(unsigned char*)(data + i) & 0xC0) != 0x80)
						return 0;
				}
				return 3;
			}
			else if (*(unsigned char*)data >= 0xC0) //2 bytes
			{
				if (size < 2)
					return 0;
				if ((*(unsigned char*)(data + 1) & 0xC0) != 0x80)
					return 0;
				return 2;
			}
			else if (*(unsigned char*)data >= 0x80) // BAD
				return 0;
			else
				return 1;
		}

		_String StrTool::Escape(const _String & s, bool escapeSafe)
		{
			std::string escaped;
			escaped.reserve(s.length() + s.length() / 2);
			for (size_t i = 0; i < s.length(); i++)
			{
				char buf[8];
				memset(buf, 0, sizeof(buf));
				unsigned char ch = (unsigned char)s[i];
				switch (ch)
				{
				case '\0':
					memcpy(buf, "\\0", 2);
					break;
				case '\t':
					if (escapeSafe)
						memcpy(buf, "\\t", 2);
					else
						memcpy(buf, &ch, 1);
					break;
				case '\f':
					memcpy(buf, "\\f", 2);
					break;
				case '\v':
					memcpy(buf, "\\v", 2);
					break;
				case '\n':
					if (escapeSafe)
						memcpy(buf, "\\n", 2);
					else
						memcpy(buf, &ch, 1);
					break;
				case '\r':
					if (escapeSafe)
						memcpy(buf, "\\r", 2);
					else
						memcpy(buf, &ch, 1);
					break;
				case '\\':
					if (escapeSafe)
						memcpy(buf, "\\\\", 2);
					else
						memcpy(buf, &ch, 1);
					break;
				case '\"':
					if (escapeSafe)
						memcpy(buf, "\\\"", 2);
					else
						memcpy(buf, &ch, 1);
					break;
				default:
					int UTF8CharSize;
					if (ch >= 0x80 && (UTF8CharSize = IsValidUTF8Char(s.c_str() + i, int(s.length() - i))) != 0) //UTF-8 Character is emitted directly
					{
						memcpy(buf, s.c_str() + i, UTF8CharSize);
						i += UTF8CharSize - 1;
					}
					else if (!isprint(ch)) //unknown unprintable character
						sprintf_s(buf, "\\x%02X", ch);
					else
						*buf = ch;
				}
				escaped.append(buf);
			}
			return escaped;
		}

		bool StrTool::Unescape(const _String & s, _String & result, bool quoted)
		{
			int mLastChar = EOF;
			size_t i = 0;
			auto nextChar = [&]()
			{
				if (i == s.length())
					return mLastChar = EOF;
				return mLastChar = s[i++];
			};
			if (quoted)
			{
				nextChar();
				if (mLastChar != '\"') //start of quoted string literal
					return false; //invalid string literal
			}
			result.reserve(s.length());
			while (true)
			{
				nextChar();
				if (mLastChar == EOF) //end of file
				{
					if (!quoted)
						break;
					return false; //unexpected end of file in string literal (1)
				}
				if (mLastChar == '\r' || mLastChar == '\n')
					return false; //unexpected newline in string literal (1)
				if (quoted && mLastChar == '\"') //end of quoted string literal
					break;
				if (mLastChar == '\\') //escape sequence
				{
					nextChar();
					if (mLastChar == EOF)
						return false; //unexpected end of file in string literal (2)
					if (mLastChar == '\r' || mLastChar == '\n')
						return false; //unexpected newline in string literal (2)
					if (mLastChar == '\'' || mLastChar == '\"' || mLastChar == '?' || mLastChar == '\\')
						mLastChar = mLastChar;
					else if (mLastChar == 'a')
						mLastChar = '\a';
					else if (mLastChar == 'b')
						mLastChar = '\b';
					else if (mLastChar == 'f')
						mLastChar = '\f';
					else if (mLastChar == 'n')
						mLastChar = '\n';
					else if (mLastChar == 'r')
						mLastChar = '\r';
					else if (mLastChar == 't')
						mLastChar = '\t';
					else if (mLastChar == 'v')
						mLastChar = '\v';
					else if (mLastChar == '0')
						mLastChar = '\0';
					else if (mLastChar == 'x') //\xHH
					{
						auto ch1 = nextChar();
						auto ch2 = nextChar();
						if (isxdigit(ch1) && isxdigit(ch2))
						{
							char byteStr[3] = "";
							byteStr[0] = ch1;
							byteStr[1] = ch2;
							uint64_t hexData;
							auto error = convertLongLongNumber(byteStr, hexData, 16);
							if (error)
								return false; //convertNumber failed (%s) for hex sequence \"\\x%c%c\" in string literal
							mLastChar = hexData & 0xFF;
						}
						else
							return false; //invalid hex sequence \"\\x%c%c\" in string literal
					}
					else
						return false; //invalid escape sequence \"\\%c\" in string literal
				}
				result.push_back(mLastChar);
			}
			return true;
		}

		//Trim functions taken from: https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring/16743707#16743707



		_String StrTool::Trim(const _String & s, const _String & delim )
		{
			return TrimRight(TrimLeft(s));
		}

		_String StrTool::TrimLeft(const _String & s, const _String & delim)
		{
			size_t startpos = s.find_first_not_of(delim);
			return (startpos == _String::npos) ? "" : s.substr(startpos);
		}
		_String StrTool::TrimRight(const _String & s, const _String & delim)
		{
			size_t endpos = s.find_last_not_of(delim);
			return (endpos == _String::npos) ? "" : s.substr(0, endpos + 1);
		}


		_WString StrTool::Trim(const _WString & s, const _WString & delim)
		{
			return TrimRight(TrimLeft(s));
		}

		_WString StrTool::TrimLeft(const _WString & s, const _WString & delim)
		{
			size_t startpos = s.find_first_not_of(delim);
			return (startpos == _WString::npos) ? L"" : s.substr(startpos);
		}
		_WString StrTool::TrimRight(const _WString & s, const _WString & delim)
		{
			size_t endpos = s.find_last_not_of(delim);
			return (endpos == _WString::npos) ? L"" : s.substr(0, endpos + 1);
		}

		size_t StrTool::Length(const char *s) {
			return std::strlen(s);
		}

		size_t StrTool::Length(const wchar_t* s) {
			return lstrlenW(s);
		}

		

		_String StrTool::PadLeft(const _String & s, size_t minLength, char ch)
		{
			if (s.length() >= minLength)
				return s;
			_String pad;
			pad.resize(minLength - s.length());
			for (size_t i = 0; i < pad.length(); i++)
				pad[i] = ch;
			return pad + s;
		}

		//Conversion functions taken from: http://www.nubaria.com/en/blog/?p=289
		_String StrTool::Utf16ToUtf8(const _WString & wstr)
		{
			return Utf16ToUtf8(wstr.c_str());
		}

		_WString StrTool::PtrToWString(intptr_t ptr) {
			wchar_t *p = (wchar_t*)ptr;
			size_t len = lstrlenW(p);
			return _WString(p, len);
		}

		_String StrTool::PtrToString(intptr_t ptr) {
			char *p = (char*)ptr;
			size_t len = std::strlen(p);
			return _String(p, len);
		}

	


		_String StrTool::Utf16ToUtf8(const wchar_t* wstr)
		{
			_String convertedString;
			if (!wstr || !*wstr)
				return convertedString;
			auto requiredSize = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
			if (requiredSize > 0)
			{
				convertedString.resize(requiredSize - 1);
				if (!WideCharToMultiByte(CP_UTF8, 0, wstr, -1, (char*)convertedString.c_str(), requiredSize, nullptr, nullptr))
					convertedString.clear();
			}
			return convertedString;
		}

		_WString StrTool::Utf8ToUtf16(const _String & str)
		{
			return Utf8ToUtf16(str.c_str());
		}

		_WString StrTool::Utf8ToUtf16(const char* str)
		{
			_WString convertedString;
			if (!str || !*str)
				return convertedString;
			int requiredSize = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
			if (requiredSize > 0)
			{
				convertedString.resize(requiredSize - 1);
				if (!MultiByteToWideChar(CP_UTF8, 0, str, -1, (wchar_t*)convertedString.c_str(), requiredSize))
					convertedString.clear();
			}
			return convertedString;
		}

		 _String StrTool::LocalCpToUtf8(const _String & str)
		{
			return LocalCpToUtf8(str.c_str());
		}

		_String StrTool::LocalCpToUtf8(const char* str)
		{
			return Utf16ToUtf8(LocalCpToUtf16(str).c_str());
		}

		_WString StrTool::LocalCpToUtf16(const _String & str)
		{
			return LocalCpToUtf16(str.c_str());
		}

		_WString StrTool::LocalCpToUtf16(const char* str)
		{
			_WString convertedString;
			if (!str || !*str)
				return convertedString;
			int requiredSize = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
			if (requiredSize > 0)
			{
				convertedString.resize(requiredSize - 1);
				if (!MultiByteToWideChar(CP_ACP, 0, str, -1, (wchar_t*)convertedString.c_str(), requiredSize))
					convertedString.clear();
			}
			return convertedString;
		}


		//Taken from: https://stackoverflow.com/a/24315631
		_String StrTool::ReplaceAll(_String  s, const _String & from, const _String & to)
		{
			size_t start_pos = 0;
			while ((start_pos = s.find(from, start_pos)) != std::string::npos)
			{
				s.replace(start_pos, from.length(), to);
				start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
			}
			return s;
		}

	

		_WString StrTool::ReplaceAll(_WString  s, const _WString & from, const _WString & to)
		{
			size_t start_pos = 0;
			while ((start_pos = s.find(from, start_pos)) != std::string::npos)
			{
				s.replace(start_pos, from.length(), to);
				start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
			}
			return s;
		}

		_String StrTool::vsprintf(_In_z_ _Printf_format_string_ const char* format, va_list args)
		{
			char sbuffer[64] = "";
			if (_vsnprintf_s(sbuffer, _TRUNCATE, format, args) != -1)
				return sbuffer;

			std::vector<char> buffer(256, '\0');
			while (true)
			{
				int res = _vsnprintf_s(buffer.data(), buffer.size(), _TRUNCATE, format, args);
				if (res == -1)
				{
					buffer.resize(buffer.size() * 2);
					continue;
				}
				else
					break;
			}
			return _String(buffer.data());
		}


		_WString StrTool::ToString(const _String& str) {
			using namespace std;
			wstring wstr;
			locale loc = locale();
			for (auto const& c : str)
			{
				wchar_t wchar = std::use_facet<ctype<wchar_t>>(loc).widen(c);
				wstr.push_back(wchar);
			}

			return wstr;
		}

		_String StrTool::ToString(const _WString& wstr) {
			using namespace std;
			string str;
			locale loc = locale();
			for (auto const& c : wstr)
			{
				char ch = std::use_facet<ctype<wchar_t>>(loc).narrow(c);
				str.push_back(ch);
			}

			return str;
		}


		_String StrTool::sprintf(_In_z_ _Printf_format_string_ const char* format, ...)
		{
			va_list args;
			va_start(args, format);
			auto result = vsprintf(format, args);
			va_end(args);
			return result;
		}

		_WString StrTool::vsprintf(_In_z_ _Printf_format_string_ const wchar_t* format, va_list args)
		{
			wchar_t sbuffer[64] = L"";
			if (_vsnwprintf_s(sbuffer, _TRUNCATE, format, args) != -1)
				return sbuffer;

			std::vector<wchar_t> buffer(256, L'\0');
			while (true)
			{
				int res = _vsnwprintf_s(buffer.data(), buffer.size(), _TRUNCATE, format, args);
				if (res == -1)
				{
					buffer.resize(buffer.size() * 2);
					continue;
				}
				else
					break;
			}
			return _WString(buffer.data());
		}

		_WString StrTool::sprintf(_In_z_ _Printf_format_string_ const wchar_t* format, ...)
		{
			va_list args;
			va_start(args, format);
			auto result = vsprintf(format, args);
			va_end(args);
			return result;
		}

		_String StrTool::ToLower(const _String & s)
		{
			auto result = s;
			for (size_t i = 0; i < result.size(); i++)
				result[i] = tolower(result[i]);
			return result;
		}

		bool StrTool::StartsWith(const _String & str, const _String & prefix)
		{
			return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
		}

		bool StrTool::StartsWith(const _WString & str, const _WString & prefix)
		{
			return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
		}

		bool StrTool::EndsWith(const _String & str, const _String & suffix)
		{
			return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
		}


		bool StrTool::EndsWith(const _WString & str, const _WString & suffix)
		{
			return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
		}


		int StrTool::hex2int(char ch)
		{
			if (ch >= '0' && ch <= '9')
				return ch - '0';
			if (ch >= 'A' && ch <= 'F')
				return ch - 'A' + 10;
			if (ch >= 'a' && ch <= 'f')
				return ch - 'a' + 10;
			return -1;
		}

		bool StrTool::FromHex(const _String & text, std::vector<unsigned char> & data, bool reverse )
		{
			auto size = text.size();
			if (size % 2)
				return false;
			data.resize(size / 2);
			for (size_t i = 0, j = 0; i < size; i += 2, j++)
			{
				auto high = hex2int(text[i]);
				auto low = hex2int(text[i + 1]);
				if (high == -1 || low == -1)
					return false;
				data[reverse ? data.size() - j - 1 : j] = (high << 4) | low;
			}
			return true;
		}

		_String StrTool::ToHex(unsigned long long value)
		{
			char buf[32];
			sprintf_s(buf, "%llX", value);
			return buf;
		}

		std::wstring StrTool::UTF82Wide(const std::string& strUTF8)
		{
			if (strUTF8.length() < 1) {
				return L"";
			}
			int nWide = ::MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), strUTF8.size(), NULL, 0);

			std::unique_ptr<wchar_t[]> buffer(new wchar_t[nWide + 1]);
			if (!buffer)
			{
				return L"";
			}

			::MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), strUTF8.size(), buffer.get(), nWide);
			buffer[nWide] = L'\0';

			return std::wstring(buffer.get());
		}

		std::wstring StrTool::Ansi2Wide(const std::string& strAnsi)
		{
			if (strAnsi.length() < 1) {
				return L"";
			}
			int nWide = ::MultiByteToWideChar(CP_ACP, 0, strAnsi.c_str(), strAnsi.size(), NULL, 0);

			std::unique_ptr<wchar_t[]> buffer(new wchar_t[nWide + 1]);
			if (!buffer)
			{
				return L"";
			}

			::MultiByteToWideChar(CP_ACP, 0, strAnsi.c_str(), strAnsi.size(), buffer.get(), nWide);
			buffer[nWide] = L'\0';

			return std::wstring( buffer.get());
		}

		std::string StrTool::Wide2UTF8(const std::wstring& strWide)
		{
			if (strWide.length() < 1) {
				return u8"";
			}
			int nUTF8 = ::WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), strWide.size(), NULL, 0, NULL, NULL);

			std::unique_ptr<char[]> buffer(new char[nUTF8 + 1]);
			if (!buffer)
			{
				return "";
			}

			::WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), strWide.size(), buffer.get(), nUTF8, NULL, NULL);
			buffer[nUTF8] = '\0';

			return std::string( buffer.get());
		}

		std::string StrTool::Wide2Ansi(const std::wstring strWide)
		{
			if (strWide.length() < 1) {
				return "";
			}
			int nAnsi = ::WideCharToMultiByte(CP_ACP, 0, strWide.c_str(), strWide.size(), NULL, 0, NULL, NULL);

			std::unique_ptr<char[]> buffer(new char[nAnsi + 1]);
			if (!buffer)
			{
				return "";
			}

			::WideCharToMultiByte(CP_ACP, 0, strWide.c_str(), strWide.size(), buffer.get(), nAnsi, NULL, NULL);
			buffer[nAnsi] = '\0';

			return std::string(buffer.get());
		}

		std::string StrTool::Ansi2UTF8(const std::string& strAnsi)
		{
			return Wide2UTF8(Ansi2Wide(strAnsi));
		}




		_String StrTool::ToHex(const /*unsigned*/ char* buffer, size_t size, bool reverse )
		{
			_String result;
			result.resize(size * 2);
			for (size_t i = 0, j = 0; i < size; i++, j += 2)
			{
				auto ch = buffer[reverse ? size - i - 1 : i];
				result[j] = HEXLOOKUP[(ch >> 4) & 0xF];
				result[j + 1] = HEXLOOKUP[ch & 0xF];
			}
			return result;
		}

		//十六进制转二进制
		std::string StrTool::HexToBin(const std::string &strHex)
		{
			if (strHex.size() % 2 != 0)
			{
				return "";
			}
			std::string strBin;
			strBin.resize(strHex.size() / 2);
			for (size_t i = 0; i < strBin.size(); i++)
			{
				uint8_t cTemp = 0;
				for (size_t j = 0; j < 2; j++)
				{
					char cCur = strHex[2 * i + j];
					if (cCur >= '0' && cCur <= '9')
					{
						cTemp = (cTemp << 4) + (cCur - '0');
					}
					else if (cCur >= 'a' && cCur <= 'f')
					{
						cTemp = (cTemp << 4) + (cCur - 'a' + 10);
					}
					else if (cCur >= 'A' && cCur <= 'F')
					{
						cTemp = (cTemp << 4) + (cCur - 'A' + 10);
					}
					else
					{
						return "";
					}
				}
				strBin[i] = cTemp;
			}
			return strBin;
		}

		_String StrTool::ToCompressedHex(const unsigned char* buffer, size_t size)
		{
			if (!size)
				return "";
			_String result;
			result.reserve(size * 2);
			for (size_t i = 0; i < size;)
			{
				size_t repeat = 0;
				auto lastCh = buffer[i];
				result.push_back(HEXLOOKUP[(lastCh >> 4) & 0xF]);
				result.push_back(HEXLOOKUP[lastCh & 0xF]);
				for (; i < size && buffer[i] == lastCh; i++)
					repeat++;
				if (repeat == 2)
				{
					result.push_back(HEXLOOKUP[(lastCh >> 4) & 0xF]);
					result.push_back(HEXLOOKUP[lastCh & 0xF]);
				}
				else if (repeat > 2)
#ifdef _WIN64
					result.append(StrTool::sprintf("{%llX}", repeat));
#else //x86
					result.append(StrTool::sprintf("{%X}", repeat));
#endif //_WIN64
			}
			return result;
		}

		bool StrTool::FromCompressedHex(const _String & text, std::vector<unsigned char> & data)
		{
			auto size = text.size();
			if (size < 2)
				return false;
			data.clear();
			data.reserve(size); //TODO: better initial estimate
			_String repeatStr;
			for (size_t i = 0; i < size;)
			{
				if (isspace(text[i])) //skip " \n\r\t"
				{
					i++;
					continue;
				}
				auto high = hex2int(text[i++]); //eat high nibble
				if (i >= size) //not enough data
					return false;
				auto low = hex2int(text[i++]); //eat low nibble
				if (high == -1 || low == -1) //invalid character
					return false;
				auto lastCh = (high << 4) | low;
				data.push_back(lastCh);

				if (i >= size) //end of buffer
					break;

				if (text[i] == '{')
				{
					repeatStr.clear();
					i++; //eat '{'
					while (text[i] != '}')
					{
						repeatStr.push_back(text[i++]); //eat character
						if (i >= size) //unexpected end of buffer (missing '}')
							return false;
					}
					i++; //eat '}'

					size_t repeat = 0;
					if (!convertNumber(repeatStr.c_str(), repeat, 16) || !repeat) //conversion failed or repeat zero times
						return false;
					for (size_t j = 1; j < repeat; j++)
						data.push_back(lastCh);
				}
			}
			return true;
		}

		int StrTool::hackicmp(const char* s1, const char* s2)
		{
			unsigned char c1, c2;
			while ((c1 = *s1++) == (c2 = *s2++))
				if (c1 == '\0')
					return 0;
			s1--, s2--;
			while ((c1 = tolower(*s1++)) == (c2 = tolower(*s2++)))
				if (c1 == '\0')
					return 0;
			return c1 - c2;
		}

		template<typename T>
		_String StrTool::ToFloatingString(void* buffer)
		{
			auto value = *(T*)buffer;
			std::stringstream wFloatingStr;
			wFloatingStr << std::setprecision(std::numeric_limits<T>::digits10) << value;
			return wFloatingStr.str();
		}

		template<typename T>
		_String StrTool::ToIntegralString(void* buffer)
		{
			auto value = *(T*)buffer;
			return ToHex(value);
		}
		inline bool StrTool::convertLongLongNumber(const char* str, unsigned long long & result, int radix)
		{
			errno = 0;
			char* end;
			result = strtoull(str, &end, radix);
			if (!result && end == str)
				return false;
			if (result == ULLONG_MAX && errno)
				return false;
			if (*end)
				return false;
			return true;
		}

		inline bool StrTool::convertNumber(const char* str, size_t & result, int radix)
		{
			unsigned long long llr;
			if (!convertLongLongNumber(str, llr, radix))
				return false;
			result = size_t(llr);
			return true;
		}

		size_t StrTool::HexToNumber(const char* str)
		{
			unsigned long long llr;
			llr = std::stoll(str, 0, 16);
			return llr;
		}




}




