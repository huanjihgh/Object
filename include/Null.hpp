#ifndef _NULL_H_
#define _NULL_H_
#include "Object.hpp"
#include <string>


namespace object {
	class HLIB_API  Null :public Object {
	public:
		//Null();
		virtual std::string identify() const;
		virtual DataType getDataType();
		virtual std::string toString();
		BeginMapField(Null, Object)
		EndMapField
	};

}
#endif // _OBJECT_H_
