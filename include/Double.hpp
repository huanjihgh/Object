#ifndef _DOUBLE_H_
#define _DOUBLE_H_
#include "Object.hpp"
#include<string>


namespace object {
	class HLIB_API
		Double :public Object {
		double _value;
	public:
		operator double_t();
		//Double();
		Double(double_t value);

		std::string identify() const;
		virtual DataType getDataType();
		virtual std::string toString();
		BeginMapField(Double, Object)
		EndMapField
	};
}
#endif // _OBJECT_H_
