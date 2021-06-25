#include "../../include/Heap.h"
#include "../../include/Object.hpp"
#include <thread>
#include<mutex>
#include<atomic>
#include<chrono>
#include "../../include/task/TaskQueue.h"
#include "../../include/task/Scheduled.h"


namespace object {



	/**
	*�������
	*�ɹ�����true�����򷵻�false
	*/
	bool TimerTask::Finish() {
		return this->opcode == task_type::finish;
	}


	task_type TimerTask::Opcode() {
		return this->opcode;
	}
	/**
	*����ȡ��
	*�ɹ�����true�����򷵻�false
	*/
	bool TimerTask::Cancel() {
		/*signed char ok = 0;
		return cancel.compare_exchange_strong(ok, 1)*/;
	this->opcode = task_type::cancel;
	return true;
	}
	//using Task = std::function<void()>;

	//cancel=4 Ϊ���ڶ�ʱ����
	TimerTask::TimerTask(uint64_t fInterval, std::function<void()> executor, int type) : opcode((task_type)type), fTime(fInterval) {

		this->task = executor;
		//fTimer = fInterval*1000;

		this->fInterval = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() + fInterval;
	}





	bool TimerTask::IsLoop() {
		return this->opcode == task_type::loop;
	}

	TimerTask::~TimerTask() {

	}
	///����һ����������ƿ���29���ַ�
	void TimerTask::SetTaskName(std::string name) {
		this->taskName = name;
	}

	std::string TimerTask::GetTaskName() {
		return this->taskName;
	}
	uint64_t TimerTask::GetInterVal() {
		return this->fInterval;
	}



	///�жϸ������Ƿ��Ѿ�����
	bool TimerTask::IsCancel() {
		return this->opcode == task_type::cancel;
	}

	bool TimerTask::Running() {
		return !this->Finish();
	}


	bool TimerTask::IsFinish() {
		return this->opcode == task_type::finish;
	}



	int32_t Scheduled::TIMEOUT=INT32_MAX;


	Scheduled::Scheduled() :stop(true), cond(), mutex(), fHeap(
		new Heap<std::shared_ptr<TimerTask>>([](std::shared_ptr<TimerTask> & A, std::shared_ptr<TimerTask> & B) {
		return A->GetInterVal() < B->GetInterVal();
	})
	), thread(new std::thread(&Scheduled::Handle, this))
	{
		/*this->fHeap = new Heap<std::shared_ptr<TimerTask>>([](std::shared_ptr<TimerTask> & A, std::shared_ptr<TimerTask> & B) {
			return A->GetInterVal() < B->GetInterVal();
		});*/
	}

	Scheduled* Scheduled::Instance() {
		static Scheduled* schd = nullptr;
		if (!schd) {
			Lock lock;
			if (!schd)
				schd = new Scheduled();
		}
		return schd;
	}

	/**
	*�ı������ֹͣ״̬
	*/
	void Scheduled::Quit() {
		std::lock_guard<std::mutex> lock(this->mutex);
		m_quit = true;
		this->cond.notify_all();
	}




	void Scheduled::Post(std::shared_ptr<TimerTask> task) {
		{
			std::unique_lock<std::mutex> lock(this->mutex);
			this->fHeap->addEl(task);
			this->cond.notify_one();
		}
	}

	std::shared_ptr<TimerTask> Scheduled::Post(uint64_t timeout, std::function<void()> taskFn, task_type type ) {

		std::shared_ptr<TimerTask> task = std::make_shared<TimerTask>(timeout, taskFn, type);
		this->Post(task);
		return task;
	}

	bool Scheduled::Remove(std::shared_ptr<TimerTask> task) {
		{
			std::unique_lock<std::mutex> lock(this->mutex);
			return this->fHeap->removeEl(task);
		}
		return false;
	}


	void Scheduled::Detach() {
		this->thread->detach();
	}

	void Scheduled::Join() {
		this->thread->join();
	}

	void Scheduled::Handle() {
		while (true) {
			bool loop = false;


			std::shared_ptr< TimerTask> task = NULL;
			{
				//����
				std::unique_lock<std::mutex> lock(this->mutex);

				if (this->fHeap->Size() < 1 && !this->m_quit) {//�ȵ����µ��������
					this->cond.wait_for(lock, std::chrono::milliseconds(TIMEOUT));
					continue;
				}
				else if (this->m_quit) {//����
					break;
				}
				task = this->fHeap->peekEl(0);
				uint64_t theCurrentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

				if (!task) {
					continue;
				}


				if (task->GetInterVal() <= theCurrentTime) {

					this->fHeap->removeAt(0);
					if (task->IsLoop()) {
						loop = true;
						this->fHeap->addEl(std::make_shared<TimerTask>(task->fTime, task->task, task->Opcode()));
						//this->fHeap->addEl(task);
					}
					this->cond.notify_one();
				}
				else {
					uint64_t theTimeout = task->GetInterVal() - theCurrentTime;
					if (theTimeout < 10) {
						theTimeout = 10;
					}

					this->cond.wait_for(lock, std::chrono::milliseconds(theTimeout));
					continue;//��һ�γ��Ի�ȡ����
				}

			}


			//�ж��Ƿ��Ѿ�ȡ������
			if (task->IsCancel()) {
				continue;
			}

			//�����̳߳�����ִ��
			if (this->m_quit == false && task->task) {
				ThreadPool::Instance()->post(task->task);

			/*	std::thread([task] {
					task->task();
				});*/

			}

			{
				std::unique_lock<std::mutex> lock(this->mutex);
				if (true == m_quit && this->fHeap->Size() == 0)
				{
					break;
				}
			}


		}
	}



}