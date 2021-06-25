#include "../include/CommonHelper.hpp"
#include<strstream>

namespace object {

	/// <summary>
   /// author:huangguoheng
   /// date:2020-12-13
   /// email:470136534@qq.com
   /// description:Éú³ÉËæ»ú×Ö·û´®
   /// </summary>
	std::string CommonHelper::RandomStr(int length)
	{
		std::string str = "qwertyuiopasdfghjklzxcvbnm1234567890";

		int len = str.length();
		//std::string result = "";
		int index = 0;

		std::ostringstream s;
		
		for (int k = 0; k < length; k++)
		{
			index = std::rand()%len;
			s << str[index];
			//result += str[index];
		}

		return s.str();
	}
}
