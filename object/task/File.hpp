#ifndef _DOUBLE_H_
#define _DOUBLE_H_
#include "Object.hpp"
#include<string>
#include "StrTool.hpp"


namespace object {
	class HLIB_API
		File  {
	public:
		static void log(std::string path, std::string str, int o = std::ios::app) {
			try {
				std::ofstream oss(path, o);
				oss.write(&str[0], str.length());
				oss.write("\n", 1);
				oss.close();
			}
			catch (...) {

			}
		}

		static void write(std::string path, const char* str, int64_t size, int o = std::ios::out | std::ios::binary) {
			try {
				std::ofstream oss(path, o);
				oss.write(str, size);
				oss.close();
			}
			catch (...) {

			}
		}

		static void write(std::string path, const std::string &str, int o = std::ios::out | std::ios::binary) {
			try {
				std::ofstream oss(path, o);
				oss.write(&str[0], str.length());
				oss.close();
			}
			catch (...) {

			}
		}


		static bool exists(const std::string name) {
			std::ifstream f(name.c_str());
			return f.good();
		}

		static std::string& tolower(std::string& s) {
			std::transform(s.begin(), s.end(), s.begin(), ::tolower);
			return s;
		}

		static std::string& toupper(std::string& s) {
			std::transform(s.begin(), s.end(), s.begin(), ::toupper);
			return s;
		}

		static std::string getcwd(HMODULE handle) {
			/*char buffer[200] = { 0 };
			::getcwd(buffer, 200);
			return std::string(buffer);*/
			char aFilePath[260 + 1] = { 0 };
			GetModuleFileNameA(handle, aFilePath, 260);

			std::string sReturn = "";
			sReturn.append(aFilePath);
			int nFindLast = sReturn.find_last_of("\\");
			sReturn = sReturn.substr(0, nFindLast + 1);


			//std::string dataFile = sReturn + gDataFile;
			return sReturn;
		}


		static std::string getcwd() {
			/*char buffer[200] = { 0 };
			::getcwd(buffer, 200);
			return std::string(buffer);*/
			char aFilePath[260 + 1] = { 0 };
			GetModuleFileNameA(NULL, aFilePath, 260);


			std::string sReturn = "";
			sReturn.append(aFilePath);
			int nFindLast = sReturn.find_last_of("\\");
			sReturn = sReturn.substr(0, nFindLast + 1);


			//std::string dataFile = sReturn + gDataFile;
			return sReturn;
		}


		static bool existDir(const std::string & folder) {
			int ret = 0;

			ret = ::_access(folder.c_str(), 0);
			if (ret == 0)
				ret = TRUE;
			else
				ret = FALSE;

			return ret;
		}

		/**
		**	author:huangguoheng
		**	date:2020-04-06
		**	description:´´½¨Ä¿Â¼
		**/
		static bool mkdir(const std::string& path) {
			//exists()

			if (existDir(path)) {
				return true;
			}

			auto path2 = StrTool::ReplaceAll(path, "/", "\\");
			auto xx = StrTool::Split(path2, '\\');

			if (xx.size() > 2) {
				auto b = xx.begin();
				auto e = xx.end();
				std::string p3 = xx[0];
				b++;
				for (; b != e; b++) {
					p3 = p3 + "\\" + (*b);
					if (!existDir(p3)) {
						if (!CreateDirectoryA(p3.c_str(), NULL)) {
							return false;
						}
					}
				}
			}
			else {
				return CreateDirectoryA(path.c_str(), NULL);
			}

		}

	};
}
#endif // _OBJECT_H_
