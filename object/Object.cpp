#include "../include/Object.hpp"
#include "../include/Int8.hpp"
#include "../include/Int16.hpp"
#include "../include/Int32.hpp"
#include "../include/Int64.hpp"
#include "../include/UInt8.hpp"
#include "../include/UInt16.hpp"
#include "../include/UInt32.hpp"
#include "../include/UInt64.hpp"
#include "../include/Float.hpp"
#include "../include/Double.hpp"
#include "../include/Bool.hpp"
#include "../include/Null.hpp"
#include "../include/Blob.hpp"
#include "../include/Array.hpp"
#include "../include/String"
#include "../include/WString.hpp"
#include "../include/DataSet.hpp"
#include "../include/KeyMap.hpp"

namespace object {
	std::mutex _lock_003;

	void _lock() {
		_lock_003.lock();
	}

	void _unlock() {
		_lock_003.unlock();
	}

	


		HashIdentifyKey1::HashIdentifyKey1() {
		this->key = "";
	}

	const bool 	HashIdentifyKey1::operator ==(const HashIdentifyKey1 &o) {
		return (o.key == this->key);

	}

	HashIdentifyKey1::operator std::string() {
		return this->key;
	}

	HashIdentifyKey1::HashIdentifyKey1(std::string key) {
		this->key = key;
	}

	const size_t	HashIdentifyKey1::GetHashCode() {
		std::hash<std::string> t;
		return t(this->key);
	}


	HashKey1::HashKey1() {
		this->key = 0;
	}

	const bool 	HashKey1::operator ==(const HashKey1 &o) {
		return (o.key == this->key);

	}

	HashKey1::operator size_t() {
		return this->key;
	}

	HashKey1::HashKey1(size_t key) {
		this->key = key;
	}

	const size_t 	HashKey1::GetHashCode() {
		return this->key;
	}

	Lock::Lock() :_owner(false) {
		_lock();
		this->_owner = true;
	}

	Lock::~Lock() {
		if (this->_owner) {
			_unlock();
		}
	}

	Field::Field(std::string field , std::uint16_t offset, DataType type /*,
		std::function<std::shared_ptr<Object>()> fn*/) {
		this->field = field;
		this->offset = offset;
		this->type = type;
		//this->momory_size = momory_size;
		//this->fn = fn;
	}

	DataType EnumHelper::getEnumType(size_t identify) {
		static bool inited = false;
		if (!inited) {
			typeMap.Add(typeid(int8_t).hash_code(), new int(DataType::Int8_H));
			typeMap.Add(typeid(int16_t).hash_code(), new int(DataType::Int16_H));
			typeMap.Add(typeid(int32_t).hash_code(), new int(DataType::Int32_H));
			typeMap.Add(typeid(int64_t).hash_code(), new int(DataType::Int64_H));
			typeMap.Add(typeid(uint8_t).hash_code(), new int(DataType::UInt8_H));
			typeMap.Add(typeid(uint16_t).hash_code(), new int(DataType::UInt16_H));
			typeMap.Add(typeid(uint32_t).hash_code(), new int(DataType::UInt32_H));
			typeMap.Add(typeid(uint64_t).hash_code(), new int(DataType::UInt64_H));
			typeMap.Add(typeid(float_t).hash_code(), new int(DataType::Float_H));
			typeMap.Add(typeid(double_t).hash_code(), new int(DataType::Double_H));
			typeMap.Add(typeid(std::string).hash_code(), new int(DataType::STRING_H));
			typeMap.Add(typeid(std::wstring).hash_code(), new int(DataType::WSTRING_H));
			typeMap.Add(typeid(bool).hash_code(), new int(DataType::Bool_H));

			typeMap.Add(typeid(UInt8).hash_code(), new int(DataType::OUInt8_H));
			typeMap.Add(typeid(UInt16).hash_code(), new int(DataType::OUInt16_H));
			typeMap.Add(typeid(UInt32).hash_code(), new int(DataType::OUInt32_H));
			typeMap.Add(typeid(UInt64).hash_code(), new int(DataType::OUInt64_H));
			typeMap.Add(typeid(Int8).hash_code(), new int(DataType::OInt8_H));
			typeMap.Add(typeid(Int16).hash_code(), new int(DataType::OInt16_H));
			typeMap.Add(typeid(Int32).hash_code(), new int(DataType::OInt32_H));

			typeMap.Add(typeid(Int64).hash_code(), new int(DataType::OInt64_H));
			typeMap.Add(typeid(Float).hash_code(), new int(DataType::OFloat_H));
			typeMap.Add(typeid(Double).hash_code(), new int(DataType::ODouble_H));
			typeMap.Add(typeid(Bool).hash_code(), new int(DataType::OBool_H));

			typeMap.Add(typeid(object::String).hash_code(), new int(DataType::OSTRING_H));
			typeMap.Add(typeid(object::WString).hash_code(), new int(DataType::OWSTRING_H));
			typeMap.Add(typeid(object::Array).hash_code(), new int(DataType::OARRAY_H));
			typeMap.Add((size_t)DataType::OARRAY_H, new int(DataType::OARRAY_H));
			typeMap.Add((size_t)DataType::OTable_H, new int(DataType::OTable_H));
			typeMap.Add(typeid(Object).hash_code(), new int(DataType::OBJECT_H));
			typeMap.Add(typeid(KeyMap).hash_code(), new int(DataType::OKeyMap_H));
			typeMap.Add(_OBJECT_H_, new int(DataType::OBJECT_H));
			typeMap.Add(typeid(object::Null).hash_code(), new int(DataType::ONULL_H));

			typeMap.Add(typeid(wchar_t*).hash_code(), new int(DataType::WCHARPTR_H));
			typeMap.Add(typeid(char*).hash_code(), new int(DataType::CHARPTR_H));

	/*		typeMap.Add(typeid(DataSet).hash_code(), new int(DataType::DATASET_H));
			typeMap.Add(typeid(Blob).hash_code(), new int(DataType::OBLOB_H));*/

			inited = true;
		}
		HashKey1 k;
		k.key = identify;
		auto it = typeMap.Get(k);
		if (it) {
			return (DataType)*it->value;
		}

		return DataType::OBJECT_H;
	}


	Object::~Object() {}
	Object::Object(int childSize, int baseSize) {

		intptr_t s = sizeof(intptr_t); //offsetof(Object, _value);
		memset(((char*)this) + s, 0, childSize - s);
	}

	intptr_t  Object::Offset() {
		//return offsetof(Object, _value)+sizeof(object::Object::Variable);
		return sizeof(intptr_t);
	}
	Object::Object() {
		/*this->_value.UINT64 = 0;
		this->_value.DOUBLE = 0;*/

		//跳过一个指针
		intptr_t s = sizeof(intptr_t); // offsetof(Object, _value);
		memset(((char*)this) + s, 0, sizeof(*this) - s);
	}

	bool const Object::operator == (const Object & o) {
		//return this->_value.UINT64 == o._value.UINT64;
		return &o == this;
	}

	const size_t Object::GetHashCode() {
		std::hash<std::string> h;
		return h(toString());
	}

	Object::operator std::string() {
		return "";
	}

	std::string Object::toString() {
		return "";
	}


	std::string Object::identify() const {
		return "_object";
	};

	std::shared_ptr<InnerType> Object::getType() {
		if (this == nullptr)
			return nullptr;
		if (!*(intptr_t*)(this)) {
			return nullptr;
		}
		std::string id = this->identify();
		auto item = this->fields.Get(id);
		if (!item)
			this->registerFields();
		return std::make_shared<Type>(this);
	}

	DataType Object::getDataType() {
		//std::string id = this->identify();

		size_t id = typeid(*this).hash_code();

		return EnumHelper::getEnumType(id);

	}
	bool Object::isList(const std::string &name) {
		bool b = name.find("object::Array") != -1;
		return b;
	}




	void Object::registerFields() {
		std::string id = this->identify();

		auto item = this->fields.Get(id);
		std::shared_ptr<FieldMap> f = nullptr;


		if (item) {
			f = item->value;
		}
		else {
			f = std::make_shared<FieldMap>();
			this->fields.Add(id, f);
		}
	}

	//	
	//bool EnumHelper::inited = false;
	//std::pair<size_t, DataType> EnumHelper::pairArray2[] = {
	//		std::make_pair(-1,DataType::UNKOWN),
	//		std::make_pair(typeid(int8_t).hash_code(),DataType::OInt8_H),
	//		std::make_pair(typeid(int16_t).hash_code(),DataType::OInt16_H),
	//		std::make_pair(typeid(int32_t).hash_code(),DataType::OInt32_H),
	//		std::make_pair(typeid(int64_t).hash_code(),DataType::OInt64_H),

	//		std::make_pair(typeid(uint8_t).hash_code(),DataType::OUInt8_H),
	//		std::make_pair(typeid(uint16_t).hash_code(),DataType::OUInt16_H),
	//		std::make_pair(typeid(uint32_t).hash_code(),DataType::OUInt32_H),
	//		std::make_pair(typeid(uint64_t).hash_code(),DataType::OUInt64_H),
	//		std::make_pair(typeid(float_t).hash_code(),DataType::OFloat_H),

	//		std::make_pair(typeid(double_t).hash_code(),DataType::ODouble_H),
	//		std::make_pair(typeid(std::string).hash_code(),DataType::OSTRING_H),
	//		std::make_pair(typeid(std::wstring).hash_code(),DataType::OSTRING_H),
	//		std::make_pair(typeid(bool).hash_code(),DataType::OBool_H),
	//		std::make_pair(typeid(UInt8).hash_code(),DataType::OUInt8_H),
	//		std::make_pair(typeid(UInt16).hash_code(),DataType::OUInt16_H),

	//		std::make_pair(typeid(UInt32).hash_code(),DataType::OUInt32_H),
	//		std::make_pair(typeid(UInt64).hash_code(),DataType::OUInt64_H),
	//		std::make_pair(typeid(Int8).hash_code(),DataType::OInt8_H),
	//		std::make_pair(typeid(Int16).hash_code(),DataType::OInt16_H),
	//		std::make_pair(typeid(Int32).hash_code(),DataType::OInt32_H),

	//		std::make_pair(typeid(Int64).hash_code(),DataType::OInt64_H),
	//		std::make_pair(typeid(Float).hash_code(),DataType::OFloat_H),
	//		std::make_pair(typeid(Double).hash_code(),DataType::ODouble_H),
	//		std::make_pair(typeid(Bool).hash_code(),DataType::OBool_H),

	//		std::make_pair(typeid(object::String).hash_code(),DataType::OSTRING_H),
	//		std::make_pair(typeid(object::Array).hash_code(),DataType::OARRAY_H),
	//		std::make_pair((size_t)DataType::OARRAY_H,DataType::OARRAY_H),
	//		std::make_pair((size_t)DataType::OTable_H,DataType::OTable_H),
	//		std::make_pair(typeid(Object).hash_code(),DataType::OBJECT_H),
	//		std::make_pair(9999,DataType::OBJECT_H),
	//		std::make_pair(typeid(object::Null).hash_code(),DataType::ONULL_H),	
	//		std::make_pair(typeid(DataSet).hash_code(),DataType::DATASET_H),
	//		std::make_pair(typeid(Blob).hash_code(),DataType::OBLOB_H),

	//};



	InnerType::InnerType(Object*  obj) {
		auto item = obj->fields.Get(obj->identify());
		if (item ) {
			this->fieldMap = item->value;
		}
		this->obj = obj;
	}
	void InnerType::setObject(Object *obj) {
		this->obj = obj;
	}

	Field* InnerType::GetField(const char* name) {
		auto x = this->fieldMap->find(name);
		if (x != this->fieldMap->end()) {
			return x->second;
		}
		return nullptr;
	}

	Field* InnerType::GetField(const std::string& name) {
		return this->GetField(name.c_str());
	}

	std::shared_ptr<FieldMap> InnerType::getFields() {
		return this->fieldMap;
	}

	std::shared_ptr< std::list<std::string>> InnerType::getFieldNames() {
		std::shared_ptr< std::list<std::string>> ll = std::make_shared< std::list<std::string>>();

		auto b = fieldMap->begin();
		auto e = fieldMap->end();

		for (; b != e; b++) {
			ll->push_back(b->first);
		}

		return ll;
	}

	bool InnerType::getObject(Field *field, object::Object* value) {
		char* b = (char*)this->obj;
		value = ((Object*)(b + field->offset));
		return true;
	}

	std::shared_ptr<Object> InnerType::get(Field *field) {
		char* ptr = (char*)this->obj;
		ptr = ptr + field->offset;

		std::shared_ptr<Object> retVal = *(std::shared_ptr<Object>*)(ptr);// object::cast<Object>();;
		return retVal;
	}


	std::shared_ptr<Object> InnerType::create(const std::string &fieldName) {
		auto field = this->fieldMap->find(fieldName);
		if (field != this->fieldMap->end()) {

			if (field->second->fn)
				return field->second->fn();
		}
		return nullptr;
	}


	std::shared_ptr<Object> InnerType::construct(const std::string & identify) {
		auto x= Object::_typeCtcMap.Get(identify);
		return x->value();
	}

	void InnerType::registerType(const std::string & key, std::function<std::shared_ptr<object::Object>()> ctc) {
		auto x = Object::_typeCtcMap.Add(key, ctc);
	}



	std::shared_ptr<Object> InnerType::create(Field* field) {

		if (field->fn)
			return field->fn();
		return nullptr;
	}

	


	
	/*	size_t getVarSize() {

		}*/


	DataType InnerType::dateType(const std::string& field) {
		return this->fieldMap->find(field)->second->type;
	}





	void InnerType::set(Field *field, std::shared_ptr<Object> value) {
		char* ptr = (char*)this->obj;
		ptr = ptr + field->offset;

		(*(std::shared_ptr<Object>*)(ptr)) = value;
	}


	char* InnerType::ptr(std::string name) {
		auto field = this->fieldMap->find(name);
		if (field != this->fieldMap->end()) {
			char* b = (char*)this->obj;
			/*	if(std::cla)*/
			return (b + field->second->offset);
		}
		return nullptr;
	}

	char* InnerType::ptr(Field *field) {
		try {
			char* b = (char*)this->obj;
			return (b + field->offset);
		}
		catch (...) {

		}
		return nullptr;
	}


	///初始化静态变量
	FieldListMap Object::fields(10);
	TypeCtcMap Object::_typeCtcMap(10);

	TypeEnumMap EnumHelper::typeMap(50);

	DataType Object::DType(size_t t)
	{
		return EnumHelper::getEnumType(t);
	}

	void InnerType::initStaticType(std::function<void()> other) {
		Int8().getType();
		Int16().getType();
		Int32().getType();
		Int64().getType();
		UInt8().getType();
		UInt16().getType();
		UInt32().getType();
		UInt64().getType();
		Float().getType();
		Double().getType();
		Bool().getType();
		Null().getType();
		//Blob().getType();
		Array().getType();
		object::String().getType();
		object::WString().getType();

		object::Array().getType();
	}
	
}

