#include "../include/Array.hpp"
#include "../include/StrTool.hpp"

namespace object {
	Array::Array() :_array(std::make_shared<Array_List>()), _new(nullptr) {}

	Array::Array(std::list<object::KeyMap> &data):_array(std::make_shared<Array_List>()) {
		auto b= data.begin();
		auto e = data.end();
		for (; b != e; b++) {
			_array->push_back(std::make_shared<KeyMap>(*b));
		}
	}

	Array::Array(std::function<std::shared_ptr<object::Object>()> _new) :_array(std::make_shared<Array_List>()), _new(_new) {}

	std::shared_ptr<object::Object> Array::createItem() {
		if (this->_new) {
			return _new();
		}
		return nullptr;
	}

	Array::Array(const Array& a) {
		this->_array = a._array;
		this->_new = a._new;
	}

	const Array & Array::operator=(const Array &a) {
		this->_array = a._array;
		this->_new = a._new;
		return  *this;
	}

	const std::shared_ptr<object::Object> Array::operator[](const size_t& index) {
		auto p = this->_array.get();
		return (*p)[index];
	}

	std::string Array::identify() const {
		return "_array";
	};

	DataType Array::getDataType() {
		return object::DataType::OARRAY_H;
	}

	std::string Array::toString() {
		std::stringstream ss;
		return ss.str();
	}

	void Array::push(std::shared_ptr<object::Object> val) {
		this->_array->push_back(val);
	}

	template<typename T>
	void Array::push(std::list<T> vals) {
		auto b = vals.begin();
		auto e = vals.end();
		for (; b != e; b++) {
			this->_array->push_back(std::make_shared<T>(*b));
		}
	}

	void Array::push(const std::string & val) {
		this->_array->push_back(std::make_shared<object::String>(val));
	}

	const size_t  Array::size() {
		return this->_array->size();
	}


	void Array::clear() {
		this->_array->clear();
	}

	const object::Array_List::iterator Array::begin() {
		return this->_array->begin();
	}

	const object::Array_List::iterator Array::end() {
		return this->_array->end();
	}

}
