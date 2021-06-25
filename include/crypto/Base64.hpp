#ifndef _H_BASE_64_1_0
#define _H_BASE_64_1_0
#include <string>
namespace crypto {
	
	namespace n1_001 {
		std::string const base64_chars =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/";
	}
	class Base64 {
	public:
		static std::string encode(std::string const & input) {
			return encode(
				reinterpret_cast<const unsigned char *>(input.data()),
				input.size()
			);
		}

		static  std::string encode(unsigned char const * input, size_t len) {
			std::string ret;
			int i = 0;
			int j = 0;
			unsigned char char_array_3[3];
			unsigned char char_array_4[4];

			while (len--) {
				char_array_3[i++] = *(input++);
				if (i == 3) {
					char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
					char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
						((char_array_3[1] & 0xf0) >> 4);
					char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
						((char_array_3[2] & 0xc0) >> 6);
					char_array_4[3] = char_array_3[2] & 0x3f;

					for (i = 0; (i < 4); i++) {
						ret += n1_001::base64_chars[char_array_4[i]];
					}
					i = 0;
				}
			}

			if (i) {
				for (j = i; j < 3; j++) {
					char_array_3[j] = '\0';
				}

				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) +
					((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) +
					((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (j = 0; (j < i + 1); j++) {
					ret += n1_001::base64_chars[char_array_4[j]];
				}

				while ((i++ < 3)) {
					ret += '=';
				}
			}

			return ret;
		}

		static std::string decode(std::string const & input) {
			size_t in_len = input.size();
			int i = 0;
			int j = 0;
			int in_ = 0;
			unsigned char char_array_4[4], char_array_3[3];
			std::string ret;

			while (in_len-- && (input[in_] != '=') && is_base64(input[in_])) {
				char_array_4[i++] = input[in_]; in_++;
				if (i == 4) {
					for (i = 0; i < 4; i++) {
						char_array_4[i] = static_cast<unsigned char>(n1_001:: base64_chars.find(char_array_4[i]));
					}

					char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
					char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
					char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

					for (i = 0; (i < 3); i++) {
						ret += char_array_3[i];
					}
					i = 0;
				}
			}

			if (i) {
				for (j = i; j < 4; j++)
					char_array_4[j] = 0;

				for (j = 0; j < 4; j++)
					char_array_4[j] = static_cast<unsigned char>(n1_001::base64_chars.find(char_array_4[j]));

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (j = 0; (j < i - 1); j++) {
					ret += static_cast<std::string::value_type>(char_array_3[j]);
				}
			}

			return ret;
		}
		private:

			//static std::string const base64_chars;

			/// Test whether a character is a valid base64 character
			/**
			 * @param c The character to test
			 * @return true if c is a valid base64 character
			 */
			static inline bool is_base64(unsigned char c) {
				return (c == 43 || // +
					(c >= 47 && c <= 57) || // /-9
					(c >= 65 && c <= 90) || // A-Z
					(c >= 97 && c <= 122)); // a-z
			}
	};

	


}
#endif // !_H_BASE_64_1
