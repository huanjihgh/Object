#ifndef _CONVERT_H_
#define _CONVERT_H_
#include "Object.hpp"


namespace object {
	class HLIB_API Convert {
	public:
		static int64_t ToInt64(const char* s);
		static int64_t ToInt64(const wchar_t* s);
		
		static int32_t ToInt32(const char* s);
		static int32_t ToInt32(const wchar_t* s);

		static int16_t ToInt16(const char* s);
		static int16_t ToInt16(const wchar_t* s);

		static int8_t ToInt8(const char* s);
		static int8_t ToInt8(const wchar_t* s);

		static uint64_t ToUInt64(const char* s);
		static uint64_t ToUInt64(const wchar_t* s);

		static uint32_t ToUInt32(const char* s);
		static uint32_t ToUInt32(const wchar_t* s);

		static uint16_t ToUInt16(const char* s);
		static uint16_t ToUInt16(const wchar_t* s);

		static uint8_t ToUInt8(const char* s);
		static uint8_t ToUInt8(const wchar_t* s);


		static float ToFloat(const char* s);
		static float ToFloat(const wchar_t* s);


		static double ToDouble(const char* s);
		static double ToDouble(const wchar_t* s);

		static bool ToBool(const char* s);
		static bool ToBool(const wchar_t* s);

		template<typename T>
		static std::shared_ptr<T> ToObject(std::shared_ptr<Object> data);
	};

}
#endif // _OBJECT_H_
