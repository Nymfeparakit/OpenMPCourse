#include <mutex>
#include <queue>
#include <thread>
#include <future>
using namespace std;

struct FactorTask
{
	packaged_task<vector<int>(int)> task;
	int number;

	/*FactorTask(packaged_task<vector<int>(int)> t, int n)
		:task(move(t)), number(n)
	{

	}*/
};

class ThreadSafeQueue
{
private:
	mutable mutex mut;
	//queue<function<vector<int>()>> q;
	//queue<int> q;
	queue<FactorTask> q;
	//TODO condition variable?
public:

	void push(FactorTask fact_task)
	{
		lock_guard<mutex> lg(mut);
		//q.push(func);
		q.push(move(fact_task));
	}

	bool try_pop(FactorTask& fact_task)
	{
		lock_guard<mutex> lg(mut);
		if (q.empty()) {
			return false;
		}
		fact_task = move(q.front());
		q.pop();
		return true;
	}


};