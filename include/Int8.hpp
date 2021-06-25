#ifndef _INT8_H_
#define _INT8_H_
#include "Object.hpp"


namespace object {
	class HLIB_API Int8 :public Object {
		int8_t _value;
	public:
		operator int8_t();
		//Int8();
		Int8(int8_t value);

		std::string identify() const;

		virtual DataType getDataType();
		virtual std::string toString();

		BeginMapField(Int8, Object)
		EndMapField
};
}
#endif // _OBJECT_H_
