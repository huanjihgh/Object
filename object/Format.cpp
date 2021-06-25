#include "../include/Format.hpp"
#include "../include/StrTool.hpp"

namespace object {


	std::string Format::format(std::string ftm,KeyMap& args) {

		auto b = args.begin();
		auto e = args.end();
		int index = 0;

		for (; b != e; b++, index++) {
			auto b = args.begin();
			auto e = args.end();

			for (; b != e; b++) {
				std::string fm = StrTool::sprintf("{%s}", b->first.c_str());
				ftm = StrTool::ReplaceAll(ftm, fm, b->second->toString());
			}
			return ftm;
		}
		return ftm;
	}




	std::string Format::format(std::string ftm, std::vector<std::string>& args) {

		auto b = args.begin();
		auto e = args.end();
		int index = 0;

		for (; b != e; b++,index++) {
			std::string fm = StrTool::sprintf("{%d}",index);
			ftm= StrTool::ReplaceAll(ftm,fm , *b);
		}
		return ftm;
	}

	std::wstring Format::format(std::wstring ftm, std::vector<std::wstring>& args) {
		auto b = args.begin();
		auto e = args.end();
		int index = 0;

		for (; b != e; b++, index++) {
			std::wstring fm = StrTool::sprintf(L"{%d}", index);
			ftm = StrTool::ReplaceAll(ftm, fm, *b);
		}
		return ftm;
	}

	std::string Format::format(std::string ftm, std::map<std::string, std::string> & args) {
		auto b = args.begin();
		auto e = args.end();

		for (; b != e; b++) {
			std::string fm = StrTool::sprintf("{%s}",b->first.c_str());
			ftm = StrTool::ReplaceAll(ftm, fm, b->second);
		}
		return ftm;
	}

	std::wstring Format::format(std::wstring ftm, std::map<std::wstring, std::wstring>& args) {
		auto b = args.begin();
		auto e = args.end();

		for (; b != e; b++) {
			std::wstring fm = StrTool::sprintf(L"{%s}", b->first.c_str());
			ftm = StrTool::ReplaceAll(ftm, fm, b->second);
		}
		return ftm;
	}




}
