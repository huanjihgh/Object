#include"../include/UInt16.hpp"

namespace object {


	//UInt16::UInt16() {
	//	this->_value.UINT64 = 0;
	//}
	UInt16::UInt16(uint16_t value) {
		this->_value = value;
	}

	std::string UInt16::identify() const {
		return "UInt16";
	}

	DataType UInt16::getDataType() {
		return DataType::OUInt16_H;

	}
	UInt16::operator uint16_t() {
		return this->_value;
	}
	std::string UInt16::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}




}
