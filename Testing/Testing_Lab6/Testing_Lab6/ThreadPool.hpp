#include <thread>
#include <atomic>
#include "ThreadSafeQueue.hpp"
using namespace std;

vector<int> factor(int n)
{
	vector<int> factors;
	if (n == 1) {
		factors.push_back(1);
	}
	else {
		int div = 2;
		while (n > 1) {

			while (n % div == 0) {
				factors.push_back(div);
				n = n / div;
			}
			++div;

		}
	}
	int a = 0;
	return factors;
}

class ThreadPool
{
	atomic_bool done;
	ThreadSafeQueue tasks_queue;
	vector<thread> threads;
	//TODO threads joiner ???
	bool stopped = false;

	

	void work() {

		while (!done) { //���� �� ������ ����
			FactorTask factor_t;
			if (tasks_queue.try_pop(factor_t)) { //�������� ������� ������ �� �������
				//vector<int> factors = factor(factor_t.number); //���� ������� ������� �� ��������� ��
				//int a = 0;
				factor_t.task(factor_t.number);
			} 
			else {
				this_thread::yield();
			}
		}

	}

	

public:
	ThreadPool() :
		done(false)
	{
		
	}

	void start() {

		//������ ����������� ��������� ����� �������
		unsigned int thread_count = thread::hardware_concurrency();
		try {
			for (int i = 0; i < thread_count; ++i) {
				threads.push_back(thread(&ThreadPool::work, this));
			}
		}
		catch (...) { //������ ������ ����� ����������� �����������
			done = true;
			throw;
		}

	}

	//void submit(function<vector<int>(int n)> func)
	//vector<int> submit(int n)
	future<vector<int>> submit(int n)
	{
		packaged_task<vector<int>(int)> t(factor);
		FactorTask factor_task;
		factor_task.task = move(t);
		factor_task.number = n;
		future<vector<int>> res(factor_task.task.get_future());
		tasks_queue.push(move(factor_task));
		return res;
	}

	void shutdown()
	{
		done = true;
		for (int i = 0; i < threads.size(); ++i) {
			if (threads[i].joinable()) {
				threads[i].join();
			}
		}
		stopped = true;
	}

	~ThreadPool() 
	{
		if (!stopped) shutdown();
	}


};