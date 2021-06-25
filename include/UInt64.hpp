#ifndef _UINT64_H_
#define _UINT64_H_
#include "Object.hpp"


namespace object {
	class HLIB_API
		UInt64 :public Object {
		uint64_t _value;
		public:
			operator uint64_t();
			//UInt64();
			UInt64(uint64_t value);

			virtual DataType getDataType();
			std::string identify() const;
			virtual std::string toString();
			BeginMapField(UInt64, Object)
			EndMapField
	};

}
#endif // _OBJECT_H_
