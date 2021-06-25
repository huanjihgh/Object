#ifndef _FieldHelper_H_20210603
#define _FieldHelper_H_20210603
#include "Object.hpp"


namespace object {

	

	class HLIB_API FieldHelper{
		
		
		
	public:
	
		static std::string KeySort(object::Object & obj);

		static std::string JoinParams(object::Object & obj);

	};

}
#endif // _OBJECT_H_
