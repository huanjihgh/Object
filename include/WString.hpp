#ifndef _WSTRING_H_
#define _WSTRING_H_
#include "Object.hpp"


namespace object {
	class HLIB_API WString :public Object {
	public:
		std::wstring value;
		WString(std::wstring value);

		WString(const wchar_t* value);

		virtual bool const operator ==(const object::Object & o);

		operator std::wstring();

		std::string identify() const;
		virtual DataType getDataType();

		virtual std::string toString();
		BeginMapField(WString, Object)
		EndMapField
	};

}
#endif // _OBJECT_H_
