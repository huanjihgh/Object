
#include "../include/XmlDoc.hpp"
#include "../include/StrTool.hpp"
#include <queue>

namespace object{
		XmlDoc::XmlDoc() :doc() {}

		XmlDoc::XmlDoc(std::string filename) : doc(filename.c_str()) {
			this->doc.LoadFile();
		}

		void XmlDoc::Parse(std::string xmlContent) {
			this->doc.Parse(xmlContent.c_str());
		}

		void XmlDoc::_Each(std::vector<std::string> & paths, int index, TiXmlElement *elem, std::function<void(TiXmlElement *elem, XmlDoc *_this)> &call) {
			if (paths.size() <= index) {
				return;
			}
			std::string str = paths[index];
			TiXmlElement* rs = nullptr;
			TiXmlElement* node = elem->FirstChildElement();
			for (; node; node = node->NextSiblingElement()) {
				if (str == node->Value()) {
					if (index + 1 == paths.size()) {//找到节点了
						call(node,this);
					}
					else {
						this->_Each(paths, index + 1, node, call);
					}
				}
			}
		}

		TiXmlElement* XmlDoc::select(std::vector<std::string> & paths, int index, TiXmlElement *elem) {

			if (paths.size() <= index) {
				return nullptr;
			}
			std::string str = paths[index];
			TiXmlElement* rs = nullptr;
			TiXmlElement* node = elem->FirstChildElement();
			for (; node; node = node->NextSiblingElement()) {
				if (str == node->Value()) {
					if (index + 1 == paths.size()) {//找到节点了
						return node;
					}
					rs= this->select(paths, index + 1, node);
					if (rs) {
						break;
					}
				}				
			}
			return rs;
		}


		void XmlDoc::Each(const std::string & path, std::function<void(TiXmlElement *elem, XmlDoc *_this)> call, TiXmlElement *elem) {
			auto elems = StrTool::Split(path, "/");
			if (elem) {
				this->_Each(elems, 0, elem, call);
				return;
			}
			auto x = this->doc.RootElement();
			this->_Each(elems, 0,x, call);
		}


		std::wstring XmlDoc::GetW(const char* path, TiXmlElement *elem) {
			auto x = this->Get(path,elem);
			if (x.size() < 1) {
				return L"";
			}
			return StrTool::UTF82Wide(x);
		}

		TiXmlElement* XmlDoc::Select(const std::string & path, TiXmlElement* node ,int indexx) {
			
			TiXmlElement * rs;
			int index = 0;
			this->Each(path, [&index, &indexx,&rs](TiXmlElement* el, XmlDoc *self) {
				if (index == indexx) {
					rs = el;
				}
			});
			return rs;
		}

		std::string XmlDoc::Get(const std::string & path, TiXmlElement* node) {
			auto elems = StrTool::Split(path, "/");
		
			TiXmlElement* x;

			if(!node)
				x = this->doc.RootElement();
			else {
				x = node;
			}

			
			
			auto rs=this->select(elems, 0, x);
			
			if (rs) {
				/*std::string s= rs->Value();
				if (!s.empty()) {
					return s;
				}*/
				//有可能是 【<![CDATA[]]>】元素
				return rs->FirstChild()->Value();
			}
			return "";
		}

}