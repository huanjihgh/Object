#ifndef _FLOAT_H_
#define _FLOAT_H_
#include "Object.hpp"


namespace object {
	class HLIB_API Float :public Object {
		float _value;
	public:
		operator float_t();
		//Float();
		Float(float_t value);

		std::string identify() const;

		virtual DataType getDataType();
		virtual std::string toString();
		BeginMapField(Float, Object)
		EndMapField
	};

}
#endif // _OBJECT_H_
