#ifndef _KEYMAP_H_
#define _KEYMAP_H_
#include "Object.hpp"
#include <map>

namespace object {
	class HLIB_API  KeyMap :public Object {
		std::map<std::string, std::shared_ptr<Object>> _map;
	public:
		KeyMap();

		KeyMap(int childSize,int baseSize);
		size_t size();

		std::shared_ptr<Object> operator [](const std::string& key);

		std::shared_ptr<Object> operator [](const char * key);

		void set(const std::string& key,std::shared_ptr<Object> value);
		void set(const char * key, std::shared_ptr<Object> value);
		//void set(const std::string& key,Object& value);
		//void set(const char * key, Object& value);

		std::map<std::string, std::shared_ptr<Object>>::iterator begin();

		std::map<std::string, std::shared_ptr<Object>>::iterator end();

		std::string identify() const;

		virtual DataType getDataType();
		virtual std::string toString();
	/*	BeginMapField(KeyMap, Object)
		EndMapField*/
	};

}
#endif // _OBJECT_H_
