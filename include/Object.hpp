#ifndef _OBJECT_H_001
#define _OBJECT_H_001
#include<string>
#include<map>
#include<stddef.h>
#include<type_traits>
#include<list>
#include "HashTable.h"
#include <functional>
#include <stdio.h>
#include <direct.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <mutex>
#include  <io.h> //_access fun



#ifndef _OBJECT_H_
#define _OBJECT_H_ 999
#endif

#ifdef HLIB_STATIC
#define HLIB_API 
#else
#if defined(HLIB_EXPORTS)
#    if defined(_MSC_VER)
#        define HLIB_API __declspec(dllexport)
#    else
#        define HLIB_API 
#    endif
#else
#    if defined(_MSC_VER)
#        define HLIB_API __declspec(dllimport)
#    else
#        define HLIB_API 
#    endif
#endif
#endif

#ifndef _HGH_FIELD_
#define _HGH_FIELD_

/***
** author:huangguoheng
** date:2019-10-01
** type:属性类型
** name:属性名称
** description: 声明类的属性和方法
**/
#define FIELD(type, name) private: type name;\
    public:type get##name(void)\
    {\
        return name;\
    }\
	void set##name(type name##1) \
	{\
		name=name##1;\
	}


#define FIELD_W2U8(type, name) private: type name;\
    public:type get##name(void)\
    {\
        return name;\
    }\
	void set##name(const wchar_t* name##1) \
	{\
		if(name##1)\
		name=object::StrTool::Wide2UTF8(name##1);\
	}

/***
** author:huangguoheng
** date:2021-05-04
** type:属性类型
** name:属性名称
** description: 声明类的属性和方法
**/
#define FIELD_FILL(type, name,size) private: type name[size];\
    public:type* get##name(void)\
    {\
        return &name[0];\
    }\
	void set##name(type* name##1) \
	{\
		for(int i=0;i<size;i++)	\
		name[i]=*(name##1+i);\
	}


/***
** author:huangguoheng
** date:2019-10-01
** type:属性类型
** name:属性名称
** description: 声明类的属性和方法
**/
#define PtrFIELD(type, name) private: std::shared_ptr<type> name;\
    public:std::shared_ptr<type> get##name(void)\
    {\
        return name;\
    }\
	void set##name(std::shared_ptr<type> name##1) \
	{\
		name=name##1;\
	}


/***
** author:huangguoheng
** date:2019-10-01
** 映射类的属性到动态发射
** description:映射注册域的开始
**/
#define BeginMapField(ChildClass,BaseClass) \
public:\
ChildClass(int childSize,int baseSize):BaseClass(childSize,baseSize){}\
ChildClass():BaseClass(sizeof(ChildClass),sizeof(BaseClass)){}\
protected:\
virtual void registerFields() {\
BaseClass::registerFields();\
std::string id = this->identify();\
static bool init_ = false;\
if (!init_) {\
	\
		_typeCtcMap.Add(id, [] {\
			return std::make_shared<ChildClass>(); \
	})\
		;init_ = true; \
}\
\
auto  item = this->fields.Get(id); \
std::shared_ptr<object::FieldMap> f = item->value;


#define MapField(CLASS,fieldType,field) \
		f->emplace(\
	u8#field,\
		new object::Field(u8#field,\
			offsetof(CLASS,\
				field),\
				object::Object::DType(typeid(fieldType).hash_code())\
		));

/**
** author:huangguoheng
** CLASS：类名
** fieldType:字段类型，
** field： 字段名称
**/
#define MapPtrField(CLASS,fieldType,field,CreateFn) \
		f->emplace(\
	u8#field,\
		new object::Field(u8#field,\
			offsetof(CLASS,\
				field),\
				object::Object::DType(typeid(std::shared_ptr<fieldType>).hash_code())\
		));


/**
** author:huangguoheng
** CLASS：类名
** fieldType:字段类型，
** field： 字段名称
**/
#define MapObject(CLASS,fieldType,field,CreateFn) \
		f->emplace(\
	u8#field,\
		new object::Field(u8#field,\
			offsetof(CLASS,\
				field),\
			object::OBJECT_H\
		));
/***
** author:huangguoheng
** date:2019-10-01
** description:映射域的结束
**/
#define EndMapField \
		this->fields.Add(id, f);\
	}\




#endif // !_HGH_FIELD_

namespace object {


	

	extern  std::mutex _lock_003;




	
	class HLIB_API  HashKey1 {
	public:
		size_t key;

		HashKey1(size_t key);
		HashKey1();

		const bool operator ==(const HashKey1 &o);

		operator size_t();

		const size_t GetHashCode();

	};

	class HLIB_API  HashIdentifyKey1 {
	public:
		std::string key;

		HashIdentifyKey1(std::string key);
		HashIdentifyKey1();

		const bool operator ==(const HashIdentifyKey1 &o);

		operator std::string();

		const size_t GetHashCode();

	};



	enum DataType
	{
		UNKOWN,
		STRING_H,
		WSTRING_H,	
		UInt8_H,
		UInt16_H,
		UInt32_H,
		UInt64_H,
		Int8_H,
		Int16_H,
		Int32_H,
		Int64_H,
		Float_H,
		Double_H,
		Bool_H,

		OSTRING_H,
		OWSTRING_H,
		OUInt8_H,
		OUInt16_H,
		OUInt32_H,
		OUInt64_H,
		OInt8_H,
		OInt16_H,
		OInt32_H,
		OInt64_H,
		OFloat_H,
		ODouble_H,
		OBool_H,

		OKeyMap_H,
		OBJECT_H,
		OARRAY_H,
		OTable_H,//这是用来区分table对象的
		ONULL_H,
		DATASET_H,
		OBLOB_H,
		OPTR_H,//指针类型
		
		WCHARPTR_H,
		CHARPTR_H,
	};




	//HLIB_API typedef HashTable<HashKey1,int *> TypeEnumMap;
	


	void _lock();

	void _unlock();

	class HLIB_API Lock {
		
		bool _owner;
	public:
		
		Lock(const Lock &) = delete;

		const Lock & operator=(const Lock&) = delete;

		Lock();
		~Lock();

	};
	class InnerType;
	class Type;
	class Object;
	class Int8;
	class Int16;
	class Int32;
	class Int64;
	class UInt8;
	class UInt16;
	class UInt32;
	class UInt64;
	class Float;
	class Double;
	class Bool;
	class String;
	class Array;
	class Null;


	class HLIB_API Field
	{
	public:
		//域的名称
		std::string field;

		DataType type;

		//地址偏移量字节
		std::uint16_t offset;

		std::function<std::shared_ptr<Object>()> fn;


		Field(std::string field = "", std::uint16_t offset = 0, DataType type = DataType::UNKOWN);


	};

	
	



	typedef std::map<std::string, Field*> FieldMap;

	typedef  HashTable<HashIdentifyKey1, std::shared_ptr<FieldMap>> FieldListMap;


	typedef HashTable<HashKey1, int*> TypeEnumMap;
	class  EnumHelper {
		static TypeEnumMap typeMap;
	public:

		static std::pair<size_t, DataType> pairArray2[51];
		static DataType getEnumType(size_t identify);
		
	};


	/*construct*/
	typedef HashTable< HashIdentifyKey1, std::function<std::shared_ptr<object::Object>()>> TypeCtcMap;

	class HLIB_API Object {
		///用来保存基本类型
		union Variable {
			bool	BOOL;
			int8_t	INT8;
			int16_t	INT16;
			int32_t INT32;
			int64_t INT64;
			uint8_t	UINT8;
			uint16_t	UINT16;
			uint32_t	UINT32;
			uint64_t	UINT64;
			float	FLOAT;
			double	DOUBLE;
			void * ptr;
			//STRING,
		};
		
		friend class Type;
		friend class InnerType;
	protected:
		static TypeCtcMap _typeCtcMap;
		static FieldListMap fields;
	public:
		virtual ~Object();
		Object(int childSize, int baseSize);
		Object();
		static intptr_t Offset();
		
		virtual bool const operator == (const Object & o);

		virtual const size_t GetHashCode();

		virtual operator std::string();

		virtual std::string toString();

		
		virtual std::string identify() const;

		std::shared_ptr<InnerType> getType();

		virtual DataType getDataType();
		
	protected:
		//Variable _value;
		bool isList(const std::string &name);

		static DataType DType(size_t t);

		virtual void registerFields();
		
	};

	




	template<typename T>
	std::shared_ptr<T> HLIB_API cast(std::shared_ptr<Object> b) {
		std::shared_ptr<T> dd = std::dynamic_pointer_cast<T>(b);
		return dd;
	}

	template<typename T>
	std::shared_ptr<T> HLIB_API cast(std::shared_ptr<InnerType> b) {
		std::shared_ptr<T> dd = std::dynamic_pointer_cast<T>(b);
		return dd;
	}


	template<typename T>
	std::shared_ptr<T> HLIB_API create() {
		return std::make_shared<T>();
	}

	template<typename T>
	std::shared_ptr<T> HLIB_API create(const T &o) {
		return std::make_shared<T>(o);
	}



	class HLIB_API InnerType
	{
	protected:

		std::shared_ptr<FieldMap> fieldMap;

		Object  * obj;

	public:
		InnerType(Object*  obj);
		void setObject(Object *obj);

		Field* GetField(const char* name);

		Field* GetField(const std::string& name);

		std::shared_ptr<FieldMap> getFields();
		std::shared_ptr< std::list<std::string>> getFieldNames();

		bool getObject(Field *field, Object* value);

		virtual std::shared_ptr<Object> get(Field *field);

		std::shared_ptr<Object> create(const std::string &fieldName);

		static std::shared_ptr<Object> construct(const std::string & identify);


		// <summary>
		// author:huangguoheng
		// email:470136534@qq.com
		// date:2021-05-28
		// description:注册类到map里面
		// </summary>
		// <param name="arg1">参数</param>
		// <returns></returns>
		static void registerType(const std::string & key, std::function<std::shared_ptr<object::Object>()> ctc);


		std::shared_ptr<Object> create(Field* field);

	

		// <summary>
		// author:huangguoheng
		// email:470136534@qq.com
		// date:2021-05-28
		// description:初始化基本静态变量
		// </summary>
		// <param name="arg1">参数</param>
		// <returns></returns>
		void static initStaticType(std::function<void()> other = nullptr);

		//std::string str(Field *field);



		DataType dateType(const std::string& field);


	

		void set(Field *field, std::shared_ptr<Object> value);


		char* ptr(std::string name);

		char* ptr(Field *field);
		//virtual std::string str(Field *field);
	};




	class Type:public InnerType
	{
	private:
		//std::shared_ptr< InnerType> innerType;
		

	public:
		Type(Object*  obj):InnerType(obj){
		
		}
		

		template<class T>
		bool get(const std::string& name, T & value) {
			auto field = this->fieldMap->find(name);
			if (field != this->fieldMap->end()) {
				char* b = (char*)this->obj;
				value = *((T*)(b + field->second->offset));
				return true;
			}
			return false;
		}

		template<typename T>
		bool get(Field *field, T & value) {
			try {
				char* ptr = (char*)this->obj;
				ptr = ptr + field->offset;
				value = *(T*)(ptr);
				return true;
			}
			catch (...) {
				return false;
			}
		}

		virtual std::shared_ptr<Object> get(Field *field) {
			return InnerType::get(field);
		}

		template<class T>
		bool set(std::string name, T value) {
			auto field = this->fieldMap->find(name);
			if (field != this->fieldMap->end()) {
				char* b = (char*)this->obj;
				/*	if(std::cla)*/
				*((T*)(b + field->second->offset)) = value;
				return true;
			}
			return false;
		}

		template<class T>
		void set(Field *field, T value) {
			char* ptr = (char*)this->obj;
			ptr = ptr + field->offset;
			(*(T*)(ptr)) = value;
		}
	};


	
	

}
#endif // _OBJECT_H_
