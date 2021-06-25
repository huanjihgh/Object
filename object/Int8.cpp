#include "../include/Int8.hpp"
namespace object {

	Int8::operator int8_t() {
		return this->_value;
	}
	//Int8::Int8() {
	//	this->_value.INT8 = 0;
	//}
	Int8::Int8(int8_t value) {
		this->_value = value;
	}

	std::string Int8::identify() const {
		return "Int8";
	}

	DataType Int8::getDataType() {
		return DataType::OInt8_H;
	}
	std::string Int8::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}




}
