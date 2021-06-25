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
	///ǰ������

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
		*�������
		*�ɹ�����true�����򷵻�false
		*/
		bool Finish();


	public:
		std::function<void()> task;

		task_type Opcode();
		/**
		*����ȡ��
		*�ɹ�����true�����򷵻�false
		*/
		bool Cancel();
		//using Task = std::function<void()>;

		//cancel=4 Ϊ���ڶ�ʱ����
		TimerTask(uint64_t fInterval, std::function<void()> executor, int type = task_type::normal);

		TimerTask(const TimerTask &) = delete;

		TimerTask& operator=(const TimerTask&) = delete;




		bool IsLoop();

		~TimerTask();
		///����һ����������ƿ���29���ַ�
		void SetTaskName(std::string name);

		std::string GetTaskName();
		uint64_t GetInterVal();



		///�жϸ������Ƿ��Ѿ�����
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
		*�ı������ֹͣ״̬
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