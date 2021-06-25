#include "../include/Int16.hpp"

namespace object {

	Int16::operator int16_t() {
		return this->_value;
	}
	//Int16::Int16() {
	//	this->_value.UINT64 = 0;
	//}
	Int16::Int16(int16_t value) {
		this->_value = value;
	}

	std::string Int16::identify() const {
		return "Int16";
	}

	bool const Int16::operator ==(const Int16 & o) {
		return this->_value == o._value;
	}

	//virtual const size_t GetHashCode() {
	//	std::hash<std::string> h;
	//	return h(this->toString());
	//}

	DataType Int16::getDataType() {
		return DataType::OInt16_H;
	}
	std::string Int16::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}



}
