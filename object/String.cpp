#include "../include/String.hpp"
#include "../include/StrTool.hpp"

namespace object {
	String::String(std::string value) {
		this->value = value;
	}

	String::String(const char* value) :value(value, strlen(value)) {
		//this->value = value;
	}

	bool const String::operator ==(const object::Object & o) {
		auto x = (object::String*)&o;
		return this->value == x->value;
	}

	String::operator std::string() {
		return this->value;
	}

	std::string String::identify() const {
		return "STRING";
	}
	DataType String::getDataType() {
		return DataType::OSTRING_H;
	}

	std::string String::toString() {
		std::stringstream ss;
		ss << this->value;

		//auto xx = StrTool::UTF82Wide(this->value);
		return ss.str();
	}




}
