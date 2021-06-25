#ifndef _INT32_H_
#define _INT32_H_
#include "Object.hpp"


namespace object {
	class HLIB_API  Int32 :public Object {
		int32_t _value;
	public:

		//Int32();
		Int32(int32_t value);

		operator int32_t();

		virtual std::string identify() const;
		virtual DataType getDataType();
		virtual std::string toString();
		BeginMapField(Int32, Object)
		EndMapField
	};
}
#endif // _OBJECT_H_
