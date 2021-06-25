//#include "../include/Blob.hpp"
//#include "../include/StrTool.hpp"
//#include "../include/databuf.hpp"
//
//namespace object {
//	Blob::Blob(size_t lenght) :length(lenght) {
//		this->_value.ptr = 0;
//	}
//
//	Blob::Blob(std::shared_ptr<buffer::Databuf> buff) {
//			this->length = buff->size();
//			this->_value.ptr = new char[this->length];
//			std::memcpy(this->_value.ptr, buff->begin(), this->length);
//		}
//
//		void* Blob::Ptr() {
//			return this->_value.ptr;
//		}
//
//		Blob::Blob(Blob& b) {
//			this->_value.ptr = b._value.ptr;
//			this->length = b.length;
//			b._value.ptr = nullptr;
//			b.length = 0;
//		}
//
//		Blob & Blob::operator =(Blob& b) {
//			this->_value.ptr = b._value.ptr;
//			this->length = b.length;
//			b._value.ptr = nullptr;
//			b.length = 0;
//			return *this;
//		}
//
//		size_t Blob::size() {
//			return this->length;
//		}
//
//		std::string Blob::identify() const {
//			return "_1_Float";
//		}
//
//		 DataType Blob::getDataType() {
//			return DataType::OBLOB_H;
//		}
//		std::string Blob::toString() {
//			/*std::stringstream ss;
//			ss << (char*)this->_value.ptr;*/
//			//return ss.str();
//			std::string s((char*)this->_value.ptr, length);
//			//return Util::HexToBin(std::string((char*)this->_value.ptr, length));
//			return s;
//		}
//		Blob::~Blob() {
//			if (this->_value.ptr) {
//				delete this->_value.ptr;
//			}
//		}
//
//		std::string Blob::hex2bin() {
//			return StrTool::HexToBin(std::string((char*)this->_value.ptr, length));
//		}
//
//}
