#ifndef _JSON_UTIL_H
#define _JSON_UTIL_H
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif // _WIN32

#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"
#include <memory>
#include <list>
#include<type_traits>
#include<string>
#include <sstream>
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
#include "WString.hpp"
#include "StrTool.hpp"
#include "DataSet.hpp"
#include "KeyMap.hpp"

using namespace rapidjson;
using namespace object;
namespace object {


	// <summary>
	// author:huangguoheng
	// email:470136534@qq.com
	// date:2020-06-18
	// description:description
	// </summary>
	class Json {
		Document d;
		

		/*static*/ bool value2Object(Value& d, Object &o);

		//static bool  _Json2BaseArray(Value* v, std::shared_ptr<Array> arr);


		/*static*/ bool value2Object2(Value* v, Object &o);


		static bool object2Value(Object& o, Value &val, rapidjson::Document::AllocatorType &allocator,
			DataType type= UNKOWN);

		static void toJsonObject(Value& v2, rapidjson::Document::AllocatorType &allocator, Object& data);



		/*static*/ std::shared_ptr<Object> GetByBaseType(Value &vale);

		/*static*/ void json2KeyMap(Object & o, Value &val);

	public:
		Json();

		Json& operator=(const Json &) = delete;

		Json(const Json&) = delete;
		Json(const std::string &);
		
		bool Parse(const std::string &data);

		template<typename T>
		bool GetArray(const std::string &key, std::list<T> & datas) {

			//T data;

			if (d.HasParseError()) {
				return false;
			}

			auto itr = StrTool::Split(key, "\\.");

			auto b = itr.begin();
			auto e = itr.end();
			Value *v = &d;
			for (; b != e; b++) {
				if (!v->HasMember(b->c_str())) {
					return false;
				}
				v = &(*v)[b->c_str()];
			}

			if (!v->IsArray()) {
				return false;
			}

			auto b2 = v->Begin();

			auto e2 = v->End();

			for (; b2 != e2; b2++) {
				if (!b2->IsObject()) {
					continue;
				}
				T data;
				if (data.getDataType() == DataType::OKeyMap_H) {
					json2KeyMap(data, *b2);
				}
				else
				{
					value2Object(*b2, data);
				}

				datas.push_back(data);
			}

			return true;

		}

		//template<typename T>
		//bool GetArray(const std::string &key, std::list<T> & datas);

		/*static*/ bool Get(const std::string & key, object::Object & outVal);

		//static std::shared_ptr<object::DataSet> ToObject(const std::string& datasetJson);
		/*static*/ bool ToObject(/*const std::string json,*/ object::Object &o, const  std::string  key = "");



		static std::string ToString(Object& data);
	};
}


#endif
