#include"../include/Int64.hpp"

namespace object {
	//Int64::Int64() {
	//	this->_value.INT64 = 0;
	//}
	Int64::Int64(int64_t value) {
		this->_value = value;
	}

	std::string Int64::identify() const {
		return "Int64";
	}
	DataType Int64::getDataType() {
		return DataType::OInt64_H;
	}

	Int64::operator int64_t() {
		return this->_value;
	}
	std::string Int64::toString() {
		std::stringstream ss;
		ss << this->_value;
		return ss.str();
	}

	//virtual const size_t GetHashCode() {
	//	std::hash<std::string> h;
	//	return h(toString());
	//}

}
