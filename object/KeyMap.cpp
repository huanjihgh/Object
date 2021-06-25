#include"../include/KeyMap.hpp"

namespace object {

	KeyMap::KeyMap():_map() {		
	}


	KeyMap::KeyMap(int childSize, int baseSize):Object(childSize,baseSize),_map(){}


	std::string KeyMap::identify() const {
		return "KeyMap";
	}

	DataType KeyMap::getDataType() {
		return DataType::OKeyMap_H;
	}
	
	std::string KeyMap::toString() {
		std::stringstream ss;
		ss <<"[KEYMAP]";
		return ss.str();
	}

	size_t KeyMap::size() {
		return this->_map.size();
	}


	std::shared_ptr<Object> KeyMap::operator [](const std::string& key) {
		auto v= this->_map.find(key);

		if (v == this->_map.end()) {
			return nullptr;
		}
		return v->second;		
	}

	std::shared_ptr<Object> KeyMap::operator [](const char * key) {
		auto v = this->_map.find(key);

		if (v == this->_map.end()) {
			return nullptr;
		}
		return v->second;
	}


	std::map<std::string, std::shared_ptr<Object>>::iterator KeyMap::begin() {
		return this->_map.begin();
	}

	std::map<std::string, std::shared_ptr<Object>>::iterator KeyMap::end() {
		return this->_map.end();
	}

	//void KeyMap::set(const std::string& key, Object& value) {
	//	this->set(key, std::make_shared<Object>(value));
	//}
	//void KeyMap::set(const char * key, Object& value) {
	//	this->set(key, std::make_shared<Object>(value));
	//}


	void KeyMap::set(const std::string& key, std::shared_ptr<Object> value) {
		this->_map.emplace(key, value);
	}
	void KeyMap::set(const char * key, std::shared_ptr<Object> value) {
		this->_map.emplace(key, value);
	}


}
