#include"../include/Float.hpp"

namespace object {
	Float::operator float_t() {
		return this->_value;
	}
	//Float::Float() {
	//	this->_value.FLOAT = 0;
	//}
	Float::Float(float_t value) {
		this->_value = value;
	}

	std::string Float::identify() const {
		return "_1_Float";
	}

	DataType Float::getDataType() {
		return DataType::OFloat_H;

	}
	std::string Float::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}

}
