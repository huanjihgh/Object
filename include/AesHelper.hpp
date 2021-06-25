#ifndef _AES_H_20210603
#define _AES_H_20210603
#include "Object.hpp"
#include "aes/AES.h"


namespace object {

	

	class HLIB_API AesHelper{		
		
		static std::string m_key;
		
	public:
	
		static std::string Encrypt(const std::string& str,std::string key="");

		static std::string Decrypt(const std::string& str, std::string key="");

	};

}
#endif // _OBJECT_H_
