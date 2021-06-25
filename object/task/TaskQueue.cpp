
#include <thread>
#include <mutex>
#include <functional>
#include <queue>
#include <assert.h>
#include"../../include/task/TaskQueue.h"

namespace object {



	TaskQueue::TaskQueue() : m_quit(false)
		, m_mutex()
		, m_condition()
		, m_queue()
		, m_thread(new std::thread(&TaskQueue::handle, this))
	{

	}

	TaskQueue::~TaskQueue()
	{

	}

	size_t TaskQueue::size() {
		std::lock_guard<std::mutex> lock(m_mutex);
		return this->m_queue.size();
	}

	void TaskQueue::quit() {
		std::lock_guard<std::mutex> lock(m_mutex);
		m_quit = true;
		m_condition.notify_all();
	}

	void TaskQueue::wait()
	{
		assert(true == m_quit && true == m_thread->joinable());
		m_thread->join();
	}
	void TaskQueue::post(std::function<void()> task) {
		post(false, task);
	}
	void TaskQueue::post(bool mustExecute, std::function<void()> task) {
		std::lock_guard<std::mutex> lock(m_mutex);
		if (false == m_quit)
		{
			m_queue.push({ mustExecute, task });
			m_condition.notify_all();
		}
	}

	void TaskQueue::handle() {
		while (true)
		{
			Task task;
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				m_condition.wait(lock, [this]() {
					return (m_quit || false == m_queue.empty());
				});

				if (false == m_queue.empty())
				{
					task = m_queue.front();
					m_queue.pop();
				}
			}

			if ((false == m_quit || true == task.mustExecute) && task.executor)
			{
#if !defined(_DEBUG) && !defined(DEBUG)
				try
				{
					task.executor();
				}
				catch (const std::exception&)
				{

				}
#else
				task.executor();
#endif
			}

			{
				std::unique_lock<std::mutex> lock(m_mutex);
				if (true == m_quit && true == m_queue.empty())
				{
					break;
				}
			}
		}
	}




	ThreadPool::ThreadPool(int size) : m_quit(false), rand(0)
	{
		for (int i = 0; i < size; i++)
		{
			this->m_taskqueue_list.push_back(new TaskQueue());
		}
	}
	ThreadPool* ThreadPool::Instance(int size) {
		static ThreadPool* t = nullptr;
		if (!t) {

			object::Lock l;
			if (!t)
				t = new ThreadPool(size);
		}
		return t;
	}




	ThreadPool::~ThreadPool()
	{

	}

	void ThreadPool::quit() {
		//auto b=this->m_taskqueue_list
		int i = 0;
		int size = this->m_taskqueue_list.size();
		i = size - 1;
		for (; size >= 0; size--, i--)
		{
			this->m_taskqueue_list[i]->quit();
			this->m_taskqueue_list[i]->wait();
			delete this->m_taskqueue_list[i];

		}
		this->m_taskqueue_list.clear();
	}

	void ThreadPool::post(std::function<void()> task) {
		post(false, task);
	}
	void ThreadPool::post(bool mustExecute, std::function<void()> task, int thread) {

		if (thread == -1) {
			size_t size = this->m_taskqueue_list.size();

			//std::vector<tmsort> x(size);

			for (size_t i = 0; i < size; i++)
			{
				thread = this->m_taskqueue_list[i]->size();
				if (thread < 1) {
					this->m_taskqueue_list[i]->post(mustExecute, task);
					return;
				}
				/*	tmsort f;
					f.i = i;
					f.k = thread;
					x.push_back(f);*/
			}

			rand = rand + 1;
			rand = rand % size;

			this->m_taskqueue_list[rand]->post(mustExecute, task);
		}
		else {
			this->m_taskqueue_list[thread]->post(mustExecute, task);
		}
	}

}