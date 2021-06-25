#include"../include/UInt32.hpp"
namespace object {

	//UInt32::UInt32() {
	//	this->_value.UINT32 = 0;
	//}
	UInt32::UInt32(uint32_t value) {
		this->_value = value;
	}
	std::string UInt32::identify() const {
		return "UInt32";
	}
	DataType 	UInt32::getDataType() {
		return DataType::OUInt32_H;

	}
	UInt32::operator uint32_t() {
		return this->_value;
	}
	std::string 	UInt32::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}



}
