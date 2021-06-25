#include "../include/Null.hpp"

namespace object {

	//Null::Null() {
	//	this->_value.ptr = nullptr;
	//}
	std::string Null::identify() const {
		return "Null";
	}
	DataType Null::getDataType() {

		//Object::getDataType()
		return DataType::ONULL_H;

	}
	std::string Null::toString() {
		return "null";
	}

}
