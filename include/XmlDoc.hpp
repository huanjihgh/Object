#ifndef _XmlDoc_
#define _XmlDoc_
#include "Object.hpp"
#include "xml/tinystr.h"
#include "xml/tinyxml.h"
#include <vector>

namespace object {
	class HLIB_API XmlDoc {
		TiXmlDocument doc;

		TiXmlElement* select(std::vector<std::string> & paths,int index, TiXmlElement *elem);
		
		void _Each(std::vector<std::string> & paths, int index, TiXmlElement *elem,std::function<void(TiXmlElement *elem, XmlDoc *_this)>& call);

	public:
		XmlDoc();

		XmlDoc(std::string filename);

		void Parse(std::string xmlContent);

		


		// <summary>
		// author:huangguoheng
		// email:470136534@qq.com
		// date:2021-06-02
		// description:选择一个元素的值
		// </summary>
		// <param name="path">root/content</param>
		// <returns></returns>
		std::string Get(const std::string & path, TiXmlElement* node=nullptr);

		//std::string Get(const std::string &path, TiXmlDocument* node);


		void Each(const std::string & path,std::function<void(TiXmlElement *elem, XmlDoc *_this)> call, TiXmlElement *elem=nullptr);

		TiXmlElement* Select(const std::string & path, TiXmlElement* node = nullptr, int index=0);

		std::wstring GetW(const char* path, TiXmlElement *elem=nullptr);

	};

}
#endif // _OBJECT_H_
