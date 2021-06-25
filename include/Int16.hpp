#ifndef _INT16_H_
#define _INT16_H_
#include "Object.hpp"


namespace object {
	class HLIB_API Int16 :public Object {
		int16_t _value;
	public:
		operator int16_t();
		//Int16();
		Int16(int16_t value);

		std::string identify() const;

		virtual bool const operator ==(const Int16 & o);
	
		virtual DataType getDataType();
		virtual std::string toString();
		BeginMapField(Int16, Object)
		EndMapField
	};

}
#endif // _OBJECT_H_
