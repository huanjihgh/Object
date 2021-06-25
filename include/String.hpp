#ifndef _STRING_H_
#define _STRING_H_
#include "Object.hpp"


namespace object {
	class HLIB_API String :public Object {
	public:
		std::string value;
		String(std::string value);

		String(const char* value);

		virtual bool const operator ==(const object::Object & o);

		operator std::string();

		operator std::wstring();


		std::string identify() const;
		virtual DataType getDataType();

		virtual std::string toString();
		BeginMapField(String, Object)
		EndMapField

#ifndef _UNICODE

		std::string str();
#else
		std::wstring str();
#endif


	};

}
#endif // _OBJECT_H_
