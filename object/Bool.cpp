#include"../include/Bool.hpp"
#include "../include/StrTool.hpp"

namespace object {
	Bool::operator bool() {
		return this->_value;
	}
	/*Bool::Bool() {
		this->_value.UINT64 = 0;
	}*/
	Bool::Bool(bool value) {
		this->_value = value;
	}

	std::string Bool::identify() const {
		return "_1_BOOL";
	}



	DataType Bool::getDataType() {
		return DataType::OBool_H;
	}
	std::string Bool::toString() {
		std::stringstream ss;
		ss << *this;
		return ss.str();
	}
}
