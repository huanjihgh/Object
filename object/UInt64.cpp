#include"../include/UInt64.hpp"

namespace object {


	UInt64::operator uint64_t() {
		return this->_value;
	}
	//UInt64::UInt64() {
	//	this->_value.UINT64 = 0;
	//}
	UInt64::UInt64(uint64_t value) {
		this->_value = value;
	}

	DataType 	UInt64::getDataType() {
		return DataType::OUInt64_H;

	}
	std::string 	UInt64::identify() const {
		return "UInt64";
	}
	std::string 	UInt64::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}



}
