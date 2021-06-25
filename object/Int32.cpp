#include "../include/Int32.hpp"

namespace object {

	//Int32::Int32() {
	//	this->_value.UINT64 = 0;
	//}
	Int32::Int32(int32_t value) {
		this->_value = value;
	}

	
	Int32::operator int32_t() {
		return this->_value;
	}

	std::string Int32::identify() const {
		return "Int32";
	}
	DataType 	Int32::getDataType() {
		return DataType::OInt32_H;
	}
	std::string Int32::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}

}
