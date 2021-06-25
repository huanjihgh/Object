#include "../include/WString.hpp"
#include "../include/StrTool.hpp"
#include "../include/StrTool.hpp"
namespace object {
	WString::WString(std::wstring value) {
		this->value = value;
	}

	WString::WString(const wchar_t* value):value(value, lstrlenW(value)) {
	}

	bool const WString::operator ==(const object::Object & o) {
		auto x = (object::WString*)&o;
		return this->value == x->value;
	}

	WString::operator std::wstring() {
		return this->value;
	}

	std::string WString::identify() const {
		return "WSTRING";
	}
	DataType WString::getDataType() {
		return DataType::OWSTRING_H;
	}

	std::string WString::toString() {
		std::wstringstream ss;
		ss << this->value;
	return StrTool::Wide2UTF8(ss.str());
	}
	
}
