#include<string>
#include "../include/Util.hpp"



namespace object {

	/**
	*author:huangguoheng
	*date:2019-07-31
	*description:拼接成url参数对arg=val&arg2=val2
	*/
	std::string Util::joinParams(Object & obj) {
		auto t =cast<Type>( obj.getType());
		auto fields = t->getFields();

		auto begin = fields->begin();
		auto end = fields->end();
		std::ostringstream str;

		for (; begin != end; begin++) {

			DataType n = begin->second->type;
			switch (n)
			{
			case DataType::OBool_H:
			{
				bool b3;
				t->get(begin->first, b3);
				//encode2(begin->first, str, utf8);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::ODouble_H:
			{

				double b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OFloat_H:
			{
				float b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OInt16_H:
			{
				int16_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OInt8_H:
			{
				int8_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OInt32_H:
			{
				int32_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OInt64_H:
			{
				int64_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OUInt16_H:
			{
				uint16_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OUInt8_H:
			{
				uint8_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OUInt32_H:
			{
				uint32_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OUInt64_H:
			{
				uint64_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OSTRING_H:
			{

				std::string  b3;
				t->get(begin->first, b3);
				/*v.SetString(b3.c_str(), allocator);*/
				if (!b3.empty()) {
					str << begin->first;
					str << "=" << b3;
					str << "&";
				}
			}
			break;

			//////////////////////////
			case DataType::Bool_H:
			{
				bool b3;
				t->get(begin->first, b3);
				//encode2(begin->first, str, utf8);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::Double_H:
			{

				double b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::Float_H:
			{
				float b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::Int16_H:
			{
				int16_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::Int8_H:
			{
				int8_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::Int32_H:
			{
				int32_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::Int64_H:
			{
				int64_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::UInt16_H:
			{
				uint16_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::UInt8_H:
			{
				uint8_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::UInt32_H:
			{
				uint32_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::UInt64_H:
			{
				uint64_t b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::STRING_H:
			{

				std::string  b3;
				t->get(begin->first, b3);
				/*v.SetString(b3.c_str(), allocator);*/
				if (!b3.empty()) {
					str << begin->first;
					str << "=" << b3;
					str << "&";
				}
			}
			break;
			}


		}
		std::string s = str.str();
		return s.substr(0, s.length() - 1) + "\0";
	}

	/**
	*author:huangguoheng
	*date:2019-07-31
	*description:通过对象的key排序
	*组合成一个字符串
	*/
	std::string Util::ksort(Object & obj) {
		auto t = cast<Type>(obj.getType());
		auto fields = t->getFields();

		auto begin = fields->begin();
		auto end = fields->end();
		std::ostringstream str;

		std::vector<std::string> strArray;


		for (; begin != end; begin++) {
			strArray.push_back(begin->first);
		}



		sort(strArray.begin(), strArray.end());

		auto begin1 = strArray.begin();
		auto end2 = strArray.end();


		for (; begin1 != end2; begin1++) {
			begin = fields->begin();
			end = fields->end();
			for (; begin != end; begin++) {

				if (begin->first != *begin1) {
					continue;
				}

				DataType n = begin->second->type;
				switch (n)
				{
				case DataType::OBool_H:
				{
					bool b3;
					t->get(begin->first, b3);
					//encode2(begin->first, str, utf8);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::ODouble_H:
				{

					double b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OFloat_H:
				{
					float b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OInt16_H:
				{
					int16_t b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OInt8_H:
				{
					int8_t b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OInt32_H:
				{
					int32_t b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OInt64_H:
				{
					int64_t b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OUInt16_H:
				{
					uint16_t b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OUInt8_H:
				{
					uint8_t b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OUInt32_H:
				{
					uint32_t b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OUInt64_H:
				{
					uint64_t b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OSTRING_H:
				{

					std::string  b3;
					t->get(begin->first, b3);
					/*v.SetString(b3.c_str(), allocator);*/
					if (!b3.empty()) {
						str << begin->first;
						str << "=" << b3;
						str << "&";
					}
				}
				break;
				}


				//跳出循环
				break;
			}
		}
		std::string s = str.str();
		return s.substr(0, s.length() - 1);
	}
}

