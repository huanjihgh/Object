#ifndef _BOOL_H_
#define _BOOL_H_
#include "Object.hpp"


namespace object {
	class HLIB_API Bool :public Object {
		bool _value;
	public:
		operator bool();
		//Bool();
		Bool(bool value);

		std::string identify() const;

		virtual DataType getDataType();
		virtual std::string toString();
		BeginMapField(Bool, Object)
		EndMapField
	};

}
#endif // _OBJECT_H_
