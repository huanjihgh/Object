#pragma once
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
//#include "db/MysqlDb.hpp"
#include "Object.hpp"
#include "Int8.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Int64.hpp"
#include "UInt8.hpp"
#include "UInt16.hpp"
#include "UInt32.hpp"
#include "UInt64.hpp"
#include "Float.hpp"
#include "Double.hpp"
#include "Bool.hpp"
#include "Null.hpp"
#include "Blob.hpp"
#include "Array.hpp"
#include "String"
#include "DataSet.hpp"
#include "Json.hpp"
#include "Hook.h"
#include "task/Scheduled.h"
#include "task/TaskQueue.h"
#include "File.hpp"
#include "CommonHelper.hpp"
#include "db/SqliteHelper.hpp"
#include "TimeUtil.hpp"
#include "Format.hpp"
#include "XmlDoc.hpp"
#include "xml/tinystr.h"
#include "xml/tinyxml.h"
#include "AesHelper.hpp"
#include "crypto/Base64.hpp"
#include "crypto/crypto.hpp"
#include "FieldHelper.hpp"
#include "Convert.hpp"