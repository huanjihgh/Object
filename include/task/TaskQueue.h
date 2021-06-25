#ifndef __TASKQUEUE_H__1
#define __TASKQUEUE_H__1
#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include <assert.h>
#include "../Object.hpp"

namespace object {


	struct HLIB_API Task
	{
		bool mustExecute;   // 结束任务队列时，是否执行完毕
		std::function<void()> executor;
	};

	class HLIB_API TaskQueue
	{
		//private static TaskQueue *_instance;


	public:


		/*static TaskQueue* Instance() {

		}*/

		TaskQueue();

		virtual ~TaskQueue();

		size_t size();

		void quit();

		void wait();
		void post(std::function<void()> task);
		void post(bool mustExecute, std::function<void()> task);
	private:
		void handle();
	private:
		volatile bool m_quit;
		std::mutex m_mutex;
		std::condition_variable m_condition;
		std::queue<Task> m_queue;
		std::unique_ptr<std::thread> m_thread;
	};



	// <summary>
	// author:huangguoheng
	// email:470136534@qq.com
	// date:2020-09-10
	// description:description
	// </summary>
	class HLIB_API ThreadPool {

		ThreadPool(int size = 3);
	public:

		static ThreadPool* Instance(int size = 3);

		int rand;

		//struct tmsort
		//{
		//	int i;
		//	int k;
		//};


		virtual ~ThreadPool();

		void quit();

		void post(std::function<void()> task);
		void post(bool mustExecute, std::function<void()> task, int thread = -1);

	private:
		std::vector<TaskQueue*> m_taskqueue_list;
		volatile bool m_quit;
	};
}
#endif /* __TASKQUEUE_H__ */