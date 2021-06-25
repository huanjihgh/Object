
#include "../include/Convert.hpp"


namespace object {
	int64_t Convert::ToInt64(const char* s) {
		if (!s) {
			return 0;
		}

		return std::stoll(s);
	}
	int64_t Convert::ToInt64(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return std::stoll(s);
	}

	int32_t Convert::ToInt32(const char* s) {
		if (!s) {
			return 0;
		}
		return std::stoi(s);
	}
	int32_t Convert::ToInt32(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return std::stoi(s);
	}

	int16_t Convert::ToInt16(const char* s) {
		if (!s) {
			return 0;
		}
		return (int16_t)std::stoi(s);
	}
	int16_t Convert::ToInt16(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return (int16_t)std::stoi(s);
	}

	int8_t Convert::ToInt8(const char* s) {
		if (!s) {
			return 0;
		}
		return (int8_t)std::stoi(s);
	}
	int8_t Convert::ToInt8(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return (int8_t)std::stoi(s);
	}

	uint64_t Convert::ToUInt64(const char* s) {
		if (!s) {
			return 0;
		}
		return std::stoull(s);
	}
	uint64_t Convert::ToUInt64(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return std::stoull(s);
	}

	uint32_t Convert::ToUInt32(const char* s) {
		if (!s) {
			return 0;
		}
		return std::stoul(s);
	}
	uint32_t Convert::ToUInt32(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return std::stoul(s);
	}

	uint16_t Convert::ToUInt16(const char* s) {
		if (!s) {
			return 0;
		}
		return (uint16_t)std::stoul(s);
	}
	uint16_t Convert::ToUInt16(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return (uint16_t)std::stoul(s);
	}

	uint8_t Convert::ToUInt8(const char* s) {
		if (!s) {
			return 0;
		}
		return (uint8_t)std::stoul(s);
	}
	uint8_t Convert::ToUInt8(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return (uint8_t)std::stoul(s);
	}


	float Convert::ToFloat(const char* s) {
		if (!s) {
			return 0;
		}
		return std::stof(s);
	}
	float Convert::ToFloat(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return std::stof(s);
	}


	double Convert::ToDouble(const char* s) {
		if (!s) {
			return 0;
		}
		return std::stod(s);
	}
	double Convert::ToDouble(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return std::stod(s);
	}

	bool Convert::ToBool(const char* s) {
		if (!s) {
			return 0;
		}
		return true;
	}
	bool Convert::ToBool(const wchar_t* s) {
		if (!s) {
			return 0;
		}
		return true;
	}

	template<typename T>
	std::shared_ptr<T> Convert::ToObject(std::shared_ptr<Object> data) {
		return object::cast<T>(data);
	}

}
