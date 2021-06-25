#include "../include/AesHelper.hpp"
#include "../include/StrTool.hpp"
#include "../include/crypto/Base64.hpp"
namespace object {
	
	std::string AesHelper::m_key="e2u54hgh65132214";

	std::string AesHelper::Encrypt(const std::string& str, std::string key) {
		if (key.empty()) {
			key = m_key;
		}
		AES aes(128);  //128 - key length, can be 128, 192 or 256
		unsigned int outLen = 0;  // out param - bytes in §ãiphertext
		auto c = aes.EncryptECB((unsigned char*)str.c_str(), str.length(),(unsigned char*) key.c_str(), outLen);
	
		return crypto::Base64::encode(c, outLen);
		//return std::string((char*)c, outLen);
	}

	std::string AesHelper::Decrypt(const std::string& str, std::string key) {
		if (key.empty()) {
			key = m_key;
		}
		std::string v= crypto::Base64::decode(str);

		AES aes(128);  //128 - key length, can be 128, 192 or 256
		auto c = aes.DecryptECB((unsigned char*)v.c_str(), v.length(), (unsigned char*)key.c_str());

		return std::string((char*)c);
	}



}
