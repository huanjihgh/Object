#include "../Heap.h"
#include "../Object.hpp"
#include <thread>
#include<mutex>
#include<atomic>
#include<chrono>
#include "TaskQueue.h"
#ifndef SCHEDULED_H_1
#define SCHEDULED_H_1


namespace object {
	///前向声明

	class TimerTask;

	enum task_type {
		normal,
		loop,
		queue,
		finish,
		cancel
	};

	class HLIB_API TimerTask {
	protected:

		uint64_t fInterval;

		std::string taskName;
		task_type opcode;

	public:

		uint64_t fTime;
		/**
		*设置完成
		*成功返回true，否则返回false
		*/
		bool Finish();


	public:
		std::function<void()> task;

		task_type Opcode();
		/**
		*设置取消
		*成功返回true，否则返回false
		*/
		bool Cancel();
		//using Task = std::function<void()>;

		//cancel=4 为周期定时任务
		TimerTask(uint64_t fInterval, std::function<void()> executor, int type = task_type::normal);

		TimerTask(const TimerTask &) = delete;

		TimerTask& operator=(const TimerTask&) = delete;




		bool IsLoop();

		~TimerTask();
		///设置一个任务的名称可以29个字符
		void SetTaskName(std::string name);

		std::string GetTaskName();
		uint64_t GetInterVal();



		///判断该任务是否已经结束
		bool IsCancel();

		bool Running();


		bool IsFinish();



	};



	class HLIB_API Scheduled {

	private:
		static int32_t TIMEOUT;
		std::mutex mutex;
		std::condition_variable cond;
		std::atomic<bool> stop;
		Heap<std::shared_ptr<TimerTask>> *fHeap;
		volatile bool m_quit;

		int _threadCount;

		std::unique_ptr<std::thread> thread;
		Scheduled();
	public:


		static Scheduled* Instance();

		/**
		*改变任务的停止状态
		*/
		void Quit();


		Scheduled(const Scheduled&) = delete;

		const Scheduled & operator= (const Scheduled&) = delete;



		void Post(std::shared_ptr<TimerTask> task);

		std::shared_ptr<TimerTask> Post(uint64_t timeout, std::function<void()> taskFn,
			task_type type = task_type::normal);

		bool Remove(std::shared_ptr<TimerTask> task);



		void Detach();
		void Join();

	private:
		void Handle();
	};



}

#endif // !SCHEDULED_H_1