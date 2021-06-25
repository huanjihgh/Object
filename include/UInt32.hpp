#ifndef _UINT32_H_
#define _UINT32_H_
#include "Object.hpp"


namespace object {
	class HLIB_API UInt32 :public Object {
		uint32_t _value;
	public:
		//UInt32();
		UInt32(uint32_t value);
		std::string identify() const;
		virtual DataType getDataType();
		operator uint32_t();
		virtual std::string toString();
		BeginMapField(UInt32, Object)
		EndMapField
	};
}
#endif // _OBJECT_H_
