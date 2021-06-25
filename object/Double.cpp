#include"../include/Double.hpp"

namespace object {

	Double::operator double_t() {
		return this->_value;
	}
	//Double::Double() {
	//	this->_value.DOUBLE = 0;
	//}
	Double::Double(double_t value) {
		this->_value = value;
	}

	std::string Double::identify() const {
		return "_1_Double";
	}
	DataType Double::getDataType() {
		return DataType::ODouble_H;
	}
	std::string Double::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}

}
