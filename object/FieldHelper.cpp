#include"../include/FieldHelper.hpp"
#include "../include/StrTool.hpp"
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
#include "../include/String.hpp"
#include "../include/WString.hpp"

namespace object {



	std::string FieldHelper::KeySort(object::Object & obj) {
		auto t =object::cast<Type>( obj.getType());
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
				case DataType::WSTRING_H:
				{

					std::wstring  b3;
					t->get(begin->first, b3);
					/*v.SetString(b3.c_str(), allocator);*/
					if (!b3.empty()) {
						str << begin->first;
						str << "=" << StrTool::Wide2UTF8(b3);
						str << "&";
					}
				}
				break;
				case DataType::CHARPTR_H:
				{
					char* b3;
					t->get(begin->first, b3);
					/*v.SetString(b3.c_str(), allocator);*/
					if (b3) {
						str << begin->first;
						str << "=" << b3;
						str << "&";
					}
				}
				break;
				case DataType::WCHARPTR_H:
				{
					wchar_t* b3;
					t->get(begin->first, b3);
					/*v.SetString(b3.c_str(), allocator);*/
					if (b3) {
						str << begin->first;
						str << "=" << StrTool::Wide2UTF8(b3);
						str << "&";
					}
				}
				break;

				/////////////////////////////////////
				case DataType::OBool_H:
				{
					Bool b3;
					t->get(begin->first, b3);
					//encode2(begin->first, str, utf8);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::ODouble_H:
				{

					Double b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OFloat_H:
				{
					Float b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OInt16_H:
				{
					Int16 b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OInt8_H:
				{
					Int8 b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OInt32_H:
				{
					Int32 b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OInt64_H:
				{
					Int64 b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OUInt16_H:
				{
					UInt16 b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OUInt8_H:
				{
					UInt8 b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OUInt32_H:
				{
					UInt32 b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OUInt64_H:
				{
					UInt64 b3;
					t->get(begin->first, b3);
					str << begin->first;
					str << "=";
					str << b3 << "&";
				}
				break;
				case DataType::OSTRING_H:
				{
					String  b3;
					t->get(begin->first, b3);
					/*v.SetString(b3.c_str(), allocator);*/
					if (!b3.operator std::string().empty()) {
						str << begin->first;
						str << "=" << b3.operator std::string();
						str << "&";
					}
				}
				break;
				case DataType::OWSTRING_H:
				{

					WString b3;
					t->get(begin->first, b3);
					/*v.SetString(b3.c_str(), allocator);*/
					if (b3.operator std::string().length() > 0) {
						str << begin->first;
						str << "=" << StrTool::Wide2UTF8(b3);
						str << "&";
					}
				}
				break;
				}


				//Ìø³öÑ­»·
				break;
			}
		}
		std::string s = str.str();
		return s.substr(0, s.length() - 1);
	}

	std::string FieldHelper::JoinParams(object::Object & obj) {
		auto t = object::cast<Type>( obj.getType());
		auto fields = t->getFields();

		auto begin = fields->begin();
		auto end = fields->end();
		std::ostringstream str;

		for (; begin != end; begin++) {

			DataType n = begin->second->type;
			switch (n)
			{
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
			case DataType::WSTRING_H:
			{

				std::wstring  b3;
				t->get(begin->first, b3);
				/*v.SetString(b3.c_str(), allocator);*/
				if (!b3.empty()) {
					str << begin->first;
					str << "=" << StrTool::Wide2UTF8(b3);
					str << "&";
				}
			}
			break;
			case DataType::CHARPTR_H:
			{
				char* b3;
				t->get(begin->first, b3);
				/*v.SetString(b3.c_str(), allocator);*/
				if (b3) {
					str << begin->first;
					str << "=" << b3;
					str << "&";
				}
			}
			break;
			case DataType::WCHARPTR_H:
			{
				wchar_t* b3;
				t->get(begin->first, b3);
				/*v.SetString(b3.c_str(), allocator);*/
				if (b3) {
					str << begin->first;
					str << "=" << StrTool::Wide2UTF8(b3);
					str << "&";
				}
			}
			break;

			/////////////////////////////////////
			case DataType::OBool_H:
			{
				Bool b3;
				t->get(begin->first, b3);
				//encode2(begin->first, str, utf8);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::ODouble_H:
			{

				Double b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OFloat_H:
			{
				Float b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OInt16_H:
			{
				Int16 b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OInt8_H:
			{
				Int8 b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OInt32_H:
			{
				Int32 b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OInt64_H:
			{
				Int64 b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OUInt16_H:
			{
				UInt16 b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OUInt8_H:
			{
				UInt8 b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OUInt32_H:
			{
				UInt32 b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OUInt64_H:
			{
				UInt64 b3;
				t->get(begin->first, b3);
				str << begin->first;
				str << "=";
				str << b3 << "&";
			}
			break;
			case DataType::OSTRING_H:
			{
				String  b3;
				t->get(begin->first, b3);
				/*v.SetString(b3.c_str(), allocator);*/
				if (!b3.operator std::string().empty()) {
					str << begin->first;
					str << "=" << b3.operator std::string();
					str << "&";
				}
			}
			break;
			case DataType::OWSTRING_H:
			{

				WString b3;
				t->get(begin->first, b3);
				/*v.SetString(b3.c_str(), allocator);*/
				if (b3.operator std::string().length()>0) {
					str << begin->first;
					str << "=" << StrTool::Wide2UTF8(b3);
					str << "&";
				}
			}
			break;
			}


		}
		std::string s = str.str();
		return s.substr(0, s.length() - 1);
	}

}
