#ifndef _UINT16_H_
#define _UINT16_H_
#include "Object.hpp"


namespace object {
	class HLIB_API  UInt16 :public Object {
		uint16_t _value;
	public:

		//UInt16();
		UInt16(uint16_t value);

		std::string identify() const;

		virtual DataType getDataType();
		operator uint16_t();
		virtual std::string toString();
		BeginMapField(UInt16, Object)
		EndMapField
	};

}
#endif // _OBJECT_H_
