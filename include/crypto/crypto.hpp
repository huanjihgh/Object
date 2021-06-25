
#ifndef  __Crypto_H_
#define __Crypto_H_
#include<string>
#include "sha1.hpp"
#include "md5.h"
#include "Base64.hpp"

namespace crypto {

	class Crypto
	{
		/*static inline int Min(int a, int b) {
			return a > b ? b : a;*/
		//}
		public:
		static std::string sha1(const std::string & data) {
		/*	SHA1 s;
			return s.sha1(data);*/
		/*	SHA1 checksum;
			checksum.update(data);
			return checksum.final();*/
			/*crypt_sha1 sha;
			sha.Reset();
			sha << data.c_str();
			sha.Result(iDigSet);*/
			char buf[20];
			int len;
			crypt_sha1((uint8_t*)data.c_str(), data.length(), (uint8_t*)buf, len);

			return std::string(buf, len);
		}

		static std::string md5(const std::string & data) {
			MD5 m(data);
			return m.md5();
		}

		/**
		*异或加密，或者解密
		*/
		static void Xor(std::string &msg,const std::string key) {
			int len = msg.length();
			int l2= key.length();
			if (l2 < 1 || len<1) {
				return;
			}

			l2 = min(len, l2);
			//计算要异或循环的次数
			int runCount = len / l2+(len%l2 == 0 ? 0 : 1);
			int index = 0;
			for (int i = 0;i < runCount;i++) {
				for (int i2 = 0;i2 < l2;i2++) {
					msg[index] = msg[index] ^ key[i2];
					index++;
					if (index == len) {
						return;
					}
				}
			}		

		}


		/**
		*异或加密，或者解密
		*/
		static void Xor(char* msg,const char* key) {
			int len = std::strlen(msg);
			int l2 = std::strlen(key);
			if (l2 < 1 || len < 1) {
				return;
			}

			l2 =min(len, l2);
			//计算要异或循环的次数
			int runCount = len / l2 + (len%l2 == 0 ? 0 : 1);
			int index = 0;
			for (int i = 0;i < runCount;i++) {
				for (int i2 = 0;i2 < l2;i2++) {
					msg[index] = msg[index] ^ key[i2];
					index++;
					if (index == len) {
						return;
					}
				}
			}

		}

		

	};
}
#endif // ! __Crypto_H_
