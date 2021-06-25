#include "../include/UInt8.hpp"
namespace object {

	//UInt8::UInt8() {
	//	this->_value.UINT64 = 0;
	//}
	UInt8::UInt8(uint8_t value) {
		this->_value = value;
	}

	std::string UInt8::identify() const {
		return "UInt8";
	}

	DataType UInt8::getDataType() {
		return DataType::OUInt8_H;

	}

	UInt8::operator uint8_t() {
		return this->_value;
	}

	std::string UInt8::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}

}
