
#include "../include/Json.hpp"
namespace object {

	


		 bool Json::value2Object(Value& d, Object &o) {

	

			std::shared_ptr< Type> t =object::cast<Type>( o.getType());

			auto fields = t->getFields();

			if (fields->size() < 1) {
			   return value2Object2(&d, o);
			}

			auto begin = fields->begin();
			auto end = fields->end();


			for (; begin != end; begin++) {

				DataType n = begin->second->type;

				if (!d.HasMember(begin->first.c_str())) {
					continue;
				}

				Value *v = &d[begin->first.c_str()];

				if (v->IsNull()) {
					continue;
				}

				switch (n)
				{

				case DataType::Int8_H:
				{
					int8_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int8_t)v->GetInt();
					}
					t->set(begin->second, b3);
				}
				break;
				case DataType::Int16_H:
				{
					int16_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int16_t)v->GetInt();
					}
					t->set(begin->second, b3);
				}
				break;

				case DataType::Int32_H:
				{
					int32_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int32_t)v->GetInt64();
					}
					t->set(begin->second, b3);
				}
				break;

				case DataType::Int64_H:
				{
					int64_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int64_t)v->GetInt64();
					}
					t->set(begin->second, b3);
				}
				break;


				case DataType::UInt8_H:

				{
					//uint8_t b3 = (uint8_t)v->GetUint64();
					uint8_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (uint32_t)v->GetUint64();
					}
					t->set(begin->second, b3);
				}
				break;
				case DataType::UInt16_H:
				{

					uint16_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (uint32_t)v->GetUint64();
					}
					t->set(begin->second, b3);
				}
				break;

				case DataType::UInt32_H:

				{
					uint32_t b3;
					if (v->IsString()) {
						b3 = std::stoull(std::string(v->GetString()));
					}
					else {
						b3 = (uint32_t)v->GetUint64();
					}
					t->set(begin->second, b3);
				}
				break;

				case DataType::UInt64_H:

				{
					/*	uint64_t b3 = (uint64_t)v->GetUint64();
						t->set(begin->first, b3);*/
					uint64_t b3;
					if (v->IsString()) {
						b3 = std::stoull(std::string(v->GetString()));
					}
					else {
						b3 = (uint64_t)v->GetUint64();
					}
					t->set(begin->second, b3);
				}
				break;
				case DataType::Float_H:

				{
					/*float b3 = v->GetFloat();
					t->set(begin->first, b3);*/
					float b3;
					if (v->IsString()) {
						b3 = std::stof(std::string(v->GetString()));
					}
					else {
						b3 = (float)v->GetFloat();
					}
					t->set(begin->second, b3);
				}
				break;

				case DataType::Double_H:
				{


					double b3;
					if (v->IsString()) {
						b3 = std::stod(std::string(v->GetString()));
					}
					else {
						b3 = (double)v->GetDouble();
					}
					t->set(begin->second, b3);
				}
				break;
				case DataType::Bool_H:
				{
					if (v->IsString()) {

						if (std::string(v->GetString()) == "0") {
							t->set(begin->second, false);
						}
						else {
							t->set(begin->second, true);
						}
					}
					else if (!v->IsBool()) {
						auto m = v->GetInt64();
						if (m == 0) {
							t->set(begin->second, false);
						}
						else {
							t->set(begin->second, true);
						}
					}
					else {
						bool b3 = v->GetBool();
						t->set(begin->second, b3);
					}

				}
				break;
				case DataType::STRING_H:
				{
					/*std::string s=v->GetString();
					t->set(begin->first, s);*/
					if (v->IsString()) {
						std::string s = v->GetString();
						/*t->set(begin->first, s);*/
						t->set(begin->second, s);
					}
					else if (v->IsBool()) {
						std::stringstream sb;
						sb << v->GetBool();
						//t->set(begin->first, sb.str());
						t->set(begin->second, sb.str());
					}
					else if (v->IsDouble()) {
						std::stringstream sb;
						sb << v->GetDouble();
						//t->set(begin->first, sb.str());
						t->set(begin->second, sb.str());
					}
					else if (v->IsInt64()) {
						std::stringstream sb;
						sb << v->GetInt64();
						//t->set(begin->first, sb.str());
						t->set(begin->second, sb.str());
					}
					else {
						std::stringstream sb;
						sb << v->GetInt64();
						//t->set(begin->first, sb.str());
						t->set(begin->second, sb.str());
					}
				}
				break;
				case DataType::WSTRING_H:
				{

					if (v->IsString()) {
						std::wstring s = StrTool::UTF82Wide(v->GetString());
						t->set(begin->second, s);
					}
					else if (v->IsBool()) {
						std::wstringstream sb;
						sb << v->GetBool();
						t->set(begin->second, sb.str());
					}
					else if (v->IsDouble()) {
						std::wstringstream sb;
						sb << v->GetDouble();
						t->set(begin->second, sb.str());
					}
					else if (v->IsInt64()) {
						std::wstringstream sb;
						sb << v->GetInt64();
						t->set(begin->second, sb.str());
					}
					else {
						std::wstringstream sb;
						sb << v->GetInt64();
						t->set(begin->second, sb.str());
					}
				}
				break;
				/////////////////////////
									
				case DataType::OInt8_H:
				{

					int8_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int8_t)v->GetInt();
					}
					t->set(begin->second,(Int8)b3);
				}
				break;
				case DataType::OInt16_H:
				{
					/*int16_t b3 = (int16_t)v->GetInt64();
					t->set(begin->first, b3);*/
					int16_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int16_t)v->GetInt();
					}
					t->set(begin->second, (Int16)b3);
				}
				break;

				case DataType::OInt32_H:
				{
					int32_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int32_t)v->GetInt64();
					}
					t->set(begin->second,(Int32) b3);
				}
				break;

				case DataType::OInt64_H:
				{
					int64_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int64_t)v->GetInt64();
					}
					t->set(begin->second,(Int64) b3);
				}
				break;

				
				case DataType::OUInt8_H:
				
				{
					//uint8_t b3 = (uint8_t)v->GetUint64();
					uint8_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (uint32_t)v->GetUint64();
					}
					t->set(begin->second,(UInt8) b3);
				}
				break;
				case DataType::OUInt16_H:
				{

					uint16_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (uint32_t)v->GetUint64();
					}
					t->set(begin->second,(UInt16) b3);
				}
				break;

				case DataType::OUInt32_H:
			
				{
					uint32_t b3;
					if (v->IsString()) {
						b3 = std::stoull(std::string(v->GetString()));
					}
					else {
						b3 = (uint32_t)v->GetUint64();
					}
					t->set(begin->second, (UInt32)b3);
				}
				break;

				case DataType::OUInt64_H:
				
				{
					uint64_t b3;
					if (v->IsString()) {
						b3 = std::stoull(std::string(v->GetString()));
					}
					else {
						b3 = (uint64_t)v->GetUint64();
					}
					t->set(begin->second,(UInt64) b3);
				}
				break;
				case DataType::OFloat_H:

				{
					/*float b3 = v->GetFloat();
					t->set(begin->first, b3);*/
					float b3;
					if (v->IsString()) {
						b3 = std::stof(std::string(v->GetString()));
					}
					else {
						b3 = (float)v->GetFloat();
					}
					t->set(begin->second, (Float)b3);
				}
				break;

				case DataType::ODouble_H:
				{


					double b3;
					if (v->IsString()) {
						b3 = std::stod(std::string(v->GetString()));
					}
					else {
						b3 = (double)v->GetDouble();
					}
					t->set(begin->second,(Double) b3);
				}
				break;
				case DataType::OBool_H:
				{
					if (v->IsString()) {

						if (std::string(v->GetString()) == "0") {
							t->set(begin->second,(Bool) false);
						}
						else {
							t->set(begin->second, (Bool)true);
						}
					}
					else if (!v->IsBool()) {
						auto m = v->GetInt64();
						if (m == 0) {
							t->set(begin->second, (Bool)false);
						}
						else {
							t->set(begin->second, (Bool)true);
						}
					}
					else {
						bool b3 = v->GetBool();
						t->set(begin->second, (Bool)b3);
					}

				}
				break;
				case DataType::OSTRING_H:
				{
					/*std::string s=v->GetString();
					t->set(begin->first, s);*/
					if (v->IsString()) {
						std::string s = v->GetString();
						/*t->set(begin->first, s);*/
						t->set(begin->second,(String) s);
					}
					else if (v->IsBool()) {
						std::stringstream sb;
						sb << v->GetBool();
						//t->set(begin->first, sb.str());
						t->set(begin->second, (String)sb.str());
					}
					else if (v->IsDouble()) {
						std::stringstream sb;
						sb << v->GetDouble();
						//t->set(begin->first, sb.str());
						t->set(begin->second, (String)sb.str());
					}
					else if (v->IsInt64()) {
						std::stringstream sb;
						sb << v->GetInt64();
						//t->set(begin->first, sb.str());
						t->set(begin->second, (String)sb.str());
					}
					else {
						std::stringstream sb;
						sb << v->GetInt64();
						//t->set(begin->first, sb.str());
						t->set(begin->second, (String)sb.str());
					}
				}
				break;
				case DataType::OWSTRING_H:
				{
	
					if (v->IsString()) {
						std::wstring s = StrTool::UTF82Wide( v->GetString());
						t->set(begin->second, (WString)s);
					}
					else if (v->IsBool()) {
						std::wstringstream sb;
						sb << v->GetBool();
						t->set(begin->second, (WString)sb.str());
					}
					else if (v->IsDouble()) {
						std::wstringstream sb;
						sb << v->GetDouble();
						t->set(begin->second, (WString)sb.str());
					}
					else if (v->IsInt64()) {
						std::wstringstream sb;
						sb << v->GetInt64();
						t->set(begin->second, (WString)sb.str());
					}
					else {
						std::wstringstream sb;
						sb << v->GetInt64();
						t->set(begin->second, (WString)sb.str());
					}
				}
				break;
				case DataType::OARRAY_H:
				{

					if (v->IsArray()) {//如果是数组把数据转换为数组

						object::Array* bp=(object::Array*)	t->ptr(begin->second);
						object::Array b3;
						if (!bp) {
							bp = &b3;
							t->set(begin->second, b3);
						}
						//if (bp) {

							auto b = v->Begin();

							auto e = v->End();

							for (; b != e; b++) {

								if (b->IsObject()) { //直接装keymap

									auto Km = std::make_shared<KeyMap>();
									json2KeyMap(*Km, *b);
									bp->push(Km);
								}
								else if (b->IsArray()) {
									auto ar=std::make_shared< object::Array>();
									value2Object(*b, *ar);
									bp->push(ar);
								}
								else {//当做字符串处理
									auto vb= GetByBaseType(*b);
									bp->push(vb);
								}

						/*		value2Object2(b, *obj);
								bp->push(obj);
								obj = t->create(begin->second);*/
							}


							
						//}
						//else {
						//	object::Array b3;
						//	//创建数据项
						//	auto obj = t->create(begin->second);
						//	t->set(begin->second, b3);
						//	if (obj) {
						//		auto b = v->Begin();

						//		auto e = v->End();

						//		for (; b != e; b++) {
						//			value2Object2(b, *obj);
						//			b3.push(obj);
						//			obj = t->create(begin->second);
						//		}
						//	}
						//	else {
						//	/*	if (_Json2BaseArray(v, std::make_shared<Array>(b3))) {
						//			t->set(begin->second, b3);
						//		}*/
						//	}
						//}
					}

				}
				break;
			
				case DataType::OKeyMap_H:
				{
					auto km =(KeyMap*) t->ptr(begin->second);
					if(km)
						json2KeyMap(*km, *v);
				}
				break;
				case DataType::OBJECT_H:
				{
					if (!v->IsObject()) {
						continue;
					}

					Object* obj = (Object *) t->ptr(begin->second);
					if (obj) {
					
						value2Object(*v, *obj);
					}
				
				}
				break;
				case DataType::OPTR_H:
				{
					auto km = t->get(begin->second);
					value2Object(*v, *km);
				}
				break;
				}
			}
			return true;
		}




		std::shared_ptr<Object> Json::GetByBaseType(Value &v) {
			if (v.IsBool()) {
				return std::make_shared<Bool>(v.GetBool());
			}else if (v.IsInt()) {
				return std::make_shared<Int32>(v.GetInt());
			}
			else if (v.IsInt64()) {
				return std::make_shared<Int64>(v.GetInt64());
			}
			else if (v.IsUint()) {
				return std::make_shared<UInt32>(v.GetUint());
			}
			else if (v.IsUint64()) {
				return std::make_shared<UInt64>(v.GetUint64());
			}
			else if (v.IsFloat()) {
				return std::make_shared<Float>(v.GetFloat());
			}
			else if (v.IsDouble()) {
				return std::make_shared<Double>(v.GetDouble());
			}
			else if (v.IsString()) {
				return std::make_shared<String>(v.GetString());
			}
			return nullptr;
		}

		 bool Json::value2Object2(Value* v, Object &o) {
		

				if (v->IsNull()) {
					return false;
				}

				switch (o.getDataType())
				{

		

				case DataType::OBool_H:
					//case DataType::OBoolPTR_H:
				{
					if (v->IsString()) {

						if (std::string(v->GetString()) == "0") {
						  Bool*b=(Bool*)&o;
						  *b = false;
						}
						else {
							Bool*b = (Bool*)&o;
							*b = true;
						}
					}
					else if (!v->IsBool()) {
						auto m = v->GetInt64();
						if (m == 0) {
							Bool*b = (Bool*)&o;
							*b = false;
						}
						else {
							Bool*b = (Bool*)&o;
							*b = true;
						}
					}
					else {
						bool b3 = v->GetBool();
						Bool*b = (Bool*)&o;
						*b = b3;
					}

				}
				break;
				case DataType::ODouble_H:
				{


					double b3;
					if (v->IsString()) {
						b3 = std::stod(std::string(v->GetString()));
					}
					else {
						b3 = (double)v->GetDouble();
					}
					Double*b = (Double*)&o;
					*b = b3;
				}
				break;
				case DataType::OFloat_H:

				{
					/*float b3 = v->GetFloat();
					t->set(begin->first, b3);*/
					float b3;
					if (v->IsString()) {
						b3 = std::stof(std::string(v->GetString()));
					}
					else {
						b3 = (float)v->GetFloat();
					}
					Float*b = (Float*)&o;
					*b = b3;
				}
				break;
				case DataType::OInt16_H:
				{
					/*int16_t b3 = (int16_t)v->GetInt64();
					t->set(begin->first, b3);*/
					int16_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int16_t)v->GetInt();
					}
					Int16*b = (Int16*)&o;
					*b = b3;
				}
				break;
				case DataType::OInt8_H:
				{

					int8_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int8_t)v->GetInt();
					}
					Int8*b = (Int8*)&o;
					*b = b3;
				}
				break;


				case DataType::OInt32_H:
				{
					int32_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int32_t)v->GetInt64();
					}
					Int32*b = (Int32*)&o;
					*b = b3;
				}
				break;

				case DataType::OInt64_H:
				{
					int64_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (int64_t)v->GetInt64();
					}
					Int64*b = (Int64*)&o;
					*b = b3;
				}
				break;

				case DataType::OUInt16_H:
				{

					uint16_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (uint32_t)v->GetUint64();
					}
					UInt16*b = (UInt16*)&o;
					*b = b3;
				}
				break;

				case DataType::OUInt8_H:
				{
					//uint8_t b3 = (uint8_t)v->GetUint64();
					uint8_t b3;
					if (v->IsString()) {
						b3 = std::stoul(std::string(v->GetString()));
					}
					else {
						b3 = (uint32_t)v->GetUint64();
					}
					UInt8*b = (UInt8*)&o;
					*b = b3;
				}
				break;
				case DataType::OUInt32_H:

				{
					uint32_t b3;
					if (v->IsString()) {
						b3 = std::stoull(std::string(v->GetString()));
					}
					else {
						b3 = (uint32_t)v->GetUint64();
					}
					UInt32*b = (UInt32*)&o;
					*b = b3;
				}
				break;

				case DataType::OUInt64_H:
				{
					uint64_t b3;
					if (v->IsString()) {
						b3 = std::stoull(std::string(v->GetString()));
					}
					else {
						b3 = (uint64_t)v->GetUint64();
					}
					UInt64*b = (UInt64*)&o;
					*b = b3;
				}
				break;

				case DataType::OSTRING_H:
				{
					/*std::string s=v->GetString();
					t->set(begin->first, s);*/
					if (v->IsString()) {
						std::string s = v->GetString();
						/*t->set(begin->first, s);*/
						object::String*b = (object::String*)&o;
						*b = s;
					}
					else if (v->IsBool()) {
						std::stringstream sb;
						sb << v->GetBool();
						//t->set(begin->first, sb.str());
						object::String*b = (object::String*)&o;
						*b = sb.str();
					}
					else if (v->IsDouble()) {
						std::stringstream sb;
						sb << v->GetDouble();
						//t->set(begin->first, sb.str());
						object::String*b = (object::String*)&o;
						*b = sb.str();
					}
					else if (v->IsInt64()) {
						std::stringstream sb;
						sb << v->GetInt64();
						//t->set(begin->first, sb.str());
						object::String*b = (object::String*)&o;
						*b = sb.str();
					}
					else {
						std::stringstream sb;
						sb << v->GetInt64();
						//t->set(begin->first, sb.str());
						object::String*b = (object::String*)&o;
						*b = sb.str();
					}
				}
				break;
				case DataType::OWSTRING_H:
				{
					/*std::string s=v->GetString();
					t->set(begin->first, s);*/
					if (v->IsString()) {
						std::wstring s = StrTool::UTF82Wide(v->GetString());
					
						object::WString*b = (object::WString*)&o;
						*b = s;
					}
					else if (v->IsBool()) {
						std::wstringstream sb;
						sb << v->GetBool();
						//t->set(begin->first, sb.str());
						object::WString*b = (object::WString*)&o;
						*b = sb.str();
					}
					else if (v->IsDouble()) {
						std::wstringstream sb;
						sb << v->GetDouble();
						//t->set(begin->first, sb.str());
						object::WString*b = (object::WString*)&o;
						*b = sb.str();
					}
					else if (v->IsInt64()) {
						std::wstringstream sb;
						sb << v->GetInt64();
						//t->set(begin->first, sb.str());
						object::WString*b = (object::WString*)&o;
						*b = sb.str();
					}
					else {
						std::wstringstream sb;
						sb << v->GetInt64();
						//t->set(begin->first, sb.str());
						object::WString*b = (object::WString*)&o;
						*b = sb.str();
					}
				}
				break;
				case DataType::OARRAY_H:
				{
					if (v->IsArray()) {//如果是数组把数据转换为数组

						object::Array* bp = (object::Array*)&o;
						object::Array b3;


						auto b = v->Begin();

						auto e = v->End();

						for (; b != e; b++) {

							if (b->IsObject()) { //直接装keymap

								auto Km = std::make_shared<KeyMap>();
								json2KeyMap(*Km, *b);
								bp->push(Km);
							}
							else if (b->IsArray()) {
								auto ar = std::make_shared< object::Array>();
								value2Object(*b, *ar);
								bp->push(ar);
							}
							else {//当做字符串处理
								auto vb = GetByBaseType(*b);
								bp->push(vb);
							}

						}

					}

				}
				break;

				
				case DataType::OBJECT_H:
				{
					if (!v->IsObject()) {
						return false;
					}
					value2Object(*v, o);
				}
				break;
				}
			return true;
		}



		 bool Json::object2Value(Object& o, Value &val, rapidjson::Document::AllocatorType &allocator, DataType type) {

			if (type == UNKOWN)
				type = o.getDataType();
			/*if (!o) {
				val.SetNull();
				return true;
			}*/
			switch (type)
			{

			
			///////////////////////////////////
			case object::OInt8_H:
			{
				Int8 b = *(object::Int8*)&o;
				val.SetInt(b);
			}
			break;
			case object::OInt16_H:
			{
				Int16 b = *(object::Int16*)&o;
				val.SetInt(b);
			}
			break;
			case object::OInt32_H:
			{
				Int32 b = *(object::Int32*)&o;
				val.SetInt(b);
			}
			break;
			case object::OInt64_H:
			{
				Int64 b = *(object::Int64*)&o;
				val.SetInt(b);
			}
			break;
			case object::OUInt8_H:
			{
				UInt8 b = *(object::UInt8*)&o;
				val.SetInt(b);
			}
			break;
			case object::OUInt16_H:
			{
				UInt16 b = *(object::UInt16*)&o;
				val.SetInt(b);
			}
			break;
			case object::OUInt32_H:
			{
				UInt32 b = *(object::UInt32*)&o;
				val.SetInt(b);
			}
			break;
			case object::OUInt64_H:
			{
				uint64_t b = *(object::UInt64*)&o;
				val.SetInt(b);
			}
			break;
			case object::OFloat_H:
			{
				float_t b = *(object::Float*)&o;
				val.SetInt(b);
			}
			break;
			case object::ODouble_H:
			{
				double_t b = *(object::Double*)&o;
				val.SetInt(b);
			}
			break;
			case object::OBool_H:
			{
				bool b = *(object::Bool*)&o;
				val.SetBool(b);
			}
			break;
			case object::OSTRING_H:
			{
				std::string b = *(object::String*)&o;
				val.SetString(b.c_str(), allocator);
			}
			break;
			case object::OWSTRING_H:
			{
				std::wstring b = *(object::WString*)&o;
				auto u8= StrTool::Wide2UTF8(b);
				val.SetString(u8.c_str(), allocator);
			}
			break;
		
			case DataType::OARRAY_H:
			{

				object::Array* b3 = (object::Array*)&o;
				val.SetArray();
				if (b3) {//拷贝数组的值到 b3
					auto b = b3->begin();
					auto e = b3->end();
					for (; b != e; b++) {
						Value v2;
						auto oo = (*b).get();
						object2Value(*oo,v2, allocator);
						val.PushBack(v2, allocator);
					}
				}
			}
			break;
			case object::OKeyMap_H:
			{
				object::KeyMap * km = (object::KeyMap*)&o;

				val.SetObject();
				if (km) {
					auto b = km->begin();
					auto e = km->end();
					for (; b != e; b++) {
						Value v2;
						auto oo = b->second;
						object2Value(*oo,v2, allocator);
						auto ax = StringRef(b->first.c_str());
						val.AddMember(ax, v2, allocator);
					}
				}
			}

			break;

			case  object::OBJECT_H:
			{
				toJsonObject(val, allocator, o);

			}break;

		
			case object::ONULL_H:
				val.SetNull();
				break;
			}
			
			return true;
		}

		 void Json::toJsonObject(Value& v2, rapidjson::Document::AllocatorType &allocator, Object& data) {

			if (data.getDataType() == object::OSTRING_H) {
				std::string  b3 =*((object::String*)& data);
				v2.SetString(b3.c_str(), allocator);
				return;
			}

			if (data.getDataType() == object::OWSTRING_H) {
				std::wstring  b3 = *((object::WString*)& data);
				auto u8 = StrTool::Wide2UTF8(b3);
				v2.SetString(u8.c_str(), allocator);
				return;
			}

			auto t = object::cast<Type>( data.getType());
			if (t == nullptr) {
				v2.SetNull();
				return;
			}

			auto fields = t->getFields();

			auto begin = fields->begin();
			auto end = fields->end();


			v2.SetObject();


			for (; begin != end; begin++) {
			
				Value v;
				DataType n = begin->second->type;



				switch (n)
				{
				
				
				
				case DataType::Int8_H:
				{
					int8_t b3;
					t->get(begin->second, b3);
					v.SetInt(b3);
				}
				break;
				case DataType::Int16_H:
				{
					int16_t b3;
					t->get(begin->second, b3);
					v.SetInt64(b3);
				}
				break;
				case DataType::Int32_H:
				{
					int32_t b3;
					t->get(begin->second, b3);
					v.SetInt64(b3);
				}
				break;
				case DataType::Int64_H:
				{
					int64_t b3;
					t->get(begin->second, b3);
					v.SetInt64(b3);
				}
				break;
				case DataType::UInt8_H:
				{
					uint8_t b3;
					t->get(begin->second, b3);
					v.SetUint(b3);
				}
				break;
				case DataType::UInt16_H:
				{
					uint16_t b3;
					t->get(begin->second, b3);
					v.SetUint64(b3);
				}
				break;
				
				case DataType::UInt32_H:
				{
					uint32_t b3;
					t->get(begin->second, b3);
					v.SetUint64(b3);
				}
				break;
				case DataType::UInt64_H:
				{
					uint64_t b3;
					t->get(begin->second, b3);
					v.SetUint64(b3);
				}
				break;
				

				
				case DataType::Float_H:
				{
					float b3;
					t->get(begin->second, b3);
					v.SetFloat(b3);
				}
				break;
				case DataType::Double_H:
				{

					double b3;
					t->get(begin->second, b3);
					v.SetDouble(b3);
				}
				break;
				case DataType::STRING_H:
				{
					std::string  b3;
					t->get(begin->second, b3);
					v.SetString(b3.c_str(), allocator);
				}
				break;
				case object::WSTRING_H:
				{
					std::wstring  b3;
					t->get(begin->second, b3);
					auto u8 = StrTool::Wide2UTF8(b3);
					v.SetString(u8.c_str(), allocator);
				}
				break;
				case object::WCHARPTR_H:
				{
					wchar_t*  b3=0;
					t->get(begin->second, b3);
					if (b3) {
						auto u8 = StrTool::Wide2UTF8(b3);
						v.SetString(u8.c_str(), allocator);
					}
					else {
						v.SetString(u8"", allocator);
					}
					
				}
				break;
				case object::CHARPTR_H:
				{
					char*  b3=0;
					t->get(begin->second, b3);
					if (b3) {
						v.SetString(b3, allocator);
					}
					else {
						v.SetString(u8"", allocator);
					}
					
				}
				break;
				case DataType::Bool_H:
				{
					bool b3;
					t->get(begin->second, b3);
					v.SetBool(b3);
				}
				break;

				/////////////////////////////////////
			
				
				case DataType::OInt8_H:
				{
					Int8 b3;
					t->get(begin->second, b3);
					v.SetInt(b3);
				}
				break;
				case DataType::OInt16_H:
				{
					Int16 b3;
					t->get(begin->second, b3);
					v.SetInt64(b3);
				}
				break;
				
				case DataType::OInt32_H:
				{
					Int32 b3;
					t->get(begin->second, b3);
					v.SetInt64(b3);
				}
				break;
				case DataType::OInt64_H:
				{
					Int64 b3;
					t->get(begin->second, b3);
					v.SetInt64(b3);
				}
				break;
				
				case DataType::OUInt8_H:
				{
					UInt8 b3;
					t->get(begin->second, b3);
					v.SetUint(b3);
				}
				break;
				case DataType::OUInt16_H:
				{
					UInt16 b3;
					t->get(begin->second, b3);
					v.SetUint64(b3);
				}
				break;
				case DataType::OUInt32_H:
				{
					UInt32 b3;
					t->get(begin->second, b3);
					v.SetUint64(b3);
				}
				break;
				case DataType::OUInt64_H:
				{
					UInt64 b3;
					t->get(begin->second, b3);
					v.SetUint64(b3);
				}
				break;
			
				case DataType::OFloat_H:
				{
					Float b3;
					t->get(begin->second, b3);
					v.SetFloat(b3);
				}
				break;
				case DataType::ODouble_H:
				{

					Double b3;
					t->get(begin->second, b3);
					v.SetDouble(b3);
				}
				break;
				case DataType::OSTRING_H:
				{
					object::String  b3;
					t->get(begin->second, b3);
					v.SetString(b3.toString().c_str(), allocator);
				}
				break;
				case object::OWSTRING_H:
				{
					object::WString b3;
					t->get(begin->second, b3);
					auto u8 = StrTool::Wide2UTF8(b3);
					v.SetString(u8.c_str(), allocator);
				}
				break;
				case DataType::OBool_H:
				{
					Bool b3;
					t->get(begin->first, b3);
					v.SetBool(b3);
				}
				break;
				case DataType::OARRAY_H:
				{
					object::Array* b3= (object::Array*)t->ptr(begin->second);				

					if (b3) {//拷贝数组的值到 b3
						auto b = b3->begin();
						auto e = b3->end();
						v.SetArray();
						for (; b != e; b++) {
							Value v2;
							auto oo = (*b).get();
							if (!oo) {
								continue;
							}
							object2Value(*oo, v2, allocator);
							v.PushBack(v2, allocator);
						}
					}
				}
				break;

				case object::OKeyMap_H:
				{
					object::KeyMap * km = (object::KeyMap*)t->ptr(begin->second);

					v.SetObject();
					if (km) {
						auto b = km->begin();
						auto e = km->end();
						for (; b != e; b++) {
							Value v2;
							auto oo = b->second;
							object2Value(*oo,v2, allocator);
							auto ax = StringRef(b->first.c_str());
							v.AddMember(ax, v2, allocator);
						}
					}
				}

				break;
				case DataType::OBJECT_H:
				{
					Object* p=(Object*) t->ptr(begin->second);
					if (p) {					
						toJsonObject(v, allocator, *p);
					}
				}
				break;			
				case DataType::OPTR_H:
				{
					std::shared_ptr<Object> p = t->get(begin->second);
					if (p) {
						toJsonObject(v, allocator, *p);
					}

				}

				break;
				case object::ONULL_H:
					v.SetNull();
					break;
				}

				auto ax = StringRef(begin->first.c_str());
				v2.AddMember(ax, v, allocator);

			}
		}

		


		 Json::Json():d(){}

		 Json::Json(const std::string & data) : d() {
			 d.Parse(StringRef(data.c_str()));
		 }
		
	
		 bool Json::Get(const std::string & key, object::Object & outVal) {
		/*	Document d;
			d.Parse(StringRef(data.c_str()));*/

			if (d.HasParseError()) {				
				return false;
			}

			auto itr= StrTool::Split(key, "\\.");

			auto b= itr.begin();
			auto e = itr.end();
			Value *v = &d;
			for (; b != e; b++) {
				if (!v->HasMember(b->c_str())) {
					return false;
				}
				v = &(*v)[b->c_str()];
			}
			if (outVal.getDataType() == object::OKeyMap_H) {
				json2KeyMap(outVal, *v);
				return true;
			}else
			return value2Object2(v, outVal);
		}

		 //template<typename T>
		 //bool Json::GetArray(const std::string &key, std::list<T> & datas) {

			// //T data;

			// if (d.HasParseError()) {
			//	 return false;
			// }

			// auto itr = StrTool::Split(key, "\\.");

			// auto b = itr.begin();
			// auto e = itr.end();
			// Value *v = &d;
			// for (; b != e; b++) {
			//	 if (!v->HasMember(b->c_str())) {
			//		 return false;
			//	 }
			//	 v = &(*v)[b->c_str()];
			// }

			// if (!v->IsArray()) {
			//	 return false;
			// }

			// auto b2= v->Begin();

			// auto e2 = v->End();

			// for (; b2 != e2; b2++) {
			//	 if (!b2->IsObject()) {
			//		 continue;
			//	 }
			//	 T data;
			//	 if (data.getDataType() == DataType::OKeyMap_H) {
			//		 json2KeyMap(data, *b2);					 
			//	 }
			//	 else
			//	 {
			//		 value2Object(*b2, data);
			//	 }

			//	 datas.push_back(data);
			// }

			// return true;

		 //}

		 void Json::json2KeyMap(Object & o, Value &d) {
			 KeyMap * km = (KeyMap*)&o;
			 for (rapidjson::Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); itr++)
			 {
				 Value jKey;
				 Value jValue;
				 Document::AllocatorType allocator;
				 jKey.CopyFrom(itr->name, allocator);
				 //jValue.CopyFrom(itr->value, allocator);

				 if (itr->value.IsBool()) {
					 km->set(itr->name.GetString(), std::make_shared<Bool>(itr->value.GetBool()));
				 }
				 else if (itr->value.IsInt()) {
					 km->set(itr->name.GetString(), std::make_shared<Int32>(itr->value.GetInt()));
				 }
				 else if (itr->value.IsInt64()) {
					 km->set(itr->name.GetString(), std::make_shared<Int64>(itr->value.GetInt64()));
				 }
				 else if (itr->value.IsFloat()) {
					 km->set(itr->name.GetString(), std::make_shared<Float>(itr->value.GetFloat()));
				 }
				 else if (itr->value.IsDouble()) {
					 km->set(itr->name.GetString(), std::make_shared<Double>(itr->value.GetDouble()));
				 }
				 else if (itr->value.IsNull()) {
					 km->set(itr->name.GetString(), std::make_shared<Null>());
				 }
				 else if (itr->value.IsUint64()) {
					 km->set(itr->name.GetString(), std::make_shared<UInt64>(itr->value.GetUint64()));
				 }
				 else if (itr->value.IsUint()) {
					 km->set(itr->name.GetString(), std::make_shared<UInt32>(itr->value.GetUint()));
				 }
				 else if (itr->value.IsString()) {
					 km->set(itr->name.GetString(), std::make_shared<String>(itr->value.GetString()));
				 }
				 else if (itr->value.IsObject()) {
					 auto km2 = std::make_shared<KeyMap>();
					 km->set(itr->name.GetString(), km2);
					 auto x = (Value*)&itr->value;
					 json2KeyMap( *km2, *x);
				 }
				 else if (itr->value.IsArray()) {
					 auto km2 = std::make_shared<Array>();
					 km->set(itr->name.GetString(), km2);
					 auto x = (Value*)&itr->value;
					 value2Object(*x, *km2);
				 }

			 }
		 }

		 bool Json::ToObject(/*const std::string json,*/ object::Object &o,const  std::string key) {
		/*	Document d;
			d.Parse(StringRef(json.c_str()));*/

			 if (key.empty()) {

				 if (d.HasParseError()) {
					 return false;
				 }

				 if (o.getDataType() == DataType::OKeyMap_H && d.IsObject()) {
					 json2KeyMap(o, d);
					 return true;
				 }

				 return value2Object(d, o);
			 }
			 else {
				 return this->Get(key, o);
			 }
		}

		 bool Json::Parse(const std::string &json) {
			 d.Parse(StringRef(json.c_str()));
			 return !d.HasParseError();
		 }


		 std::string Json::ToString(Object& data) {

			Document doc;
			rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();

			if (data.getDataType() != object::DataType::OARRAY_H) {
				doc.SetObject();
			}
			else {
				doc.SetArray();
			}

		

			object2Value(data, doc, allocator);


			StringBuffer buffer2;
			Writer<StringBuffer> writer2(buffer2);
			doc.Accept(writer2);
			std::string x(buffer2.GetString());
			return x;
		}
}


