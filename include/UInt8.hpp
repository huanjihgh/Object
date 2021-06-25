#ifndef _UINT8_H_
#define _UINT8_H_
#include "Object.hpp"


namespace object {
	class HLIB_API  UInt8 :public Object {
		uint8_t _value;
	public:

		//UInt8();
		UInt8(uint8_t value);
		std::string identify() const;

		virtual DataType getDataType();

		operator uint8_t();

		virtual std::string toString();
		BeginMapField(UInt8, Object)
			EndMapField
	};
}
#endif // _OBJECT_H_
