#ifndef _FORMATE_2021_06_01_H_
#define _FORMATE_2021_06_01_H_
#include "Object.hpp"
#include <vector>
#include <map>
#include"KeyMap.hpp"

namespace object {

	// <summary>
	// author:huangguoheng
	// email:470136534@qq.com
	// date:2021-06-01
	// description:格式化字符串
	// </summary>
	// <param name="arg1">参数</param>
	// <returns></returns>
	class HLIB_API Format {
	public:
		static std::string format(std::string ftm, object::KeyMap& args);


		static std::string format(std::string ftm, std::vector<std::string>& args);

		static std::wstring format(std::wstring ftm, std::vector<std::wstring>& args);

		static std::string format(std::string ftm,std::map<std::string,std::string> & args);

		static std::wstring format(std::wstring ftm, std::map<std::wstring, std::wstring>& args);
	};

}
#endif // _OBJECT_H_
