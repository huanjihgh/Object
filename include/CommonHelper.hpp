#ifndef _CommonHelper_H_
#define _CommonHelper_H_
#include "Object.hpp"
#include<string>
#include "StrTool.hpp"


namespace object {
	class HLIB_API CommonHelper {
	public:
		/// <summary>
	   /// author:huangguoheng
	   /// date:2020-12-13
	   /// email:470136534@qq.com
	   /// description:Éú³ÉËæ»ú×Ö·û´®
	   /// </summary>
		static std::string RandomStr(int length = 4);
	};
}
#endif // _OBJECT_H_
