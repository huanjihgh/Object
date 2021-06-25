#ifndef _INT64_H_
#define _INT64_H_
#include "Object.hpp"


namespace object {
	class HLIB_API

		Int64 :public Object {
		int64_t _value;
		public:
			//Int64();
			Int64(int64_t value);
			std::string identify() const;
			virtual DataType getDataType();

			operator int64_t();
			virtual std::string toString();
			BeginMapField(Int64, Object)
			EndMapField
	};
}
#endif // _OBJECT_H_
