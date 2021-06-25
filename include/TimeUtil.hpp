#include <chrono>
#include <ctime>
#include <string>
#include <regex>
#include <cstdlib>
#include <strstream>
#include <map>
#ifndef _TIME_UTIL_H_
#define _TIME_UTIL_H_

namespace object {

	class TimeUtil
	{
	public:

		/*
		author:huangguoheng
		date:20190219
		*/
		static uint64_t getTimeStamp()
		{
			std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
			auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
			uint64_t timestamp = tmp.count();
			//std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
			return timestamp;
		}



		static std::tm* gettm(uint64_t timestamp)
		{
			uint64_t milli = timestamp + (uint64_t)8 * 60 * 60 * 1000;//此处转化为东八区北京时间，如果是其它时区需要按需求修改
			auto mTime = std::chrono::milliseconds(milli);
			auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
			auto tt = std::chrono::system_clock::to_time_t(tp);
			std::tm* now;
			gmtime_s(now, &tt);

			return now;
		}

		

		static std::string timestamp2date(time_t timestamp, std::string format = "%Y-%m-%d %H:%M:%S") {
			struct tm *ttime;
			localtime_s(ttime,&timestamp);
			char now[40] = { 0 };
			strftime(now, 64, format.c_str(), ttime);
			return std::string(now);
		}


		static std::string format(std::string format = "%Y-%m-%d %H:%M:%S") {
			//return timestamp2date(getTimeStamp(), format);

			struct tm *ttime = gettm(getTimeStamp());
			char now[40] = { 0 };
			strftime(now, 64, format.c_str(), ttime);
			return std::string(now);
		}


	};

}
#endif // !_TIME_UTIL_H_
