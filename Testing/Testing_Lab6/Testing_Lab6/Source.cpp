#include "ThreadPool.hpp"
#include <map>
#include <iostream>

int main() {
	int N = 500000;
	ThreadPool pool;
	vector<future<vector<int>>> futures(N);
	map<int, vector<int>> factors;

	for (int i = 1; i <= N; ++i) {
		futures[i - 1] = pool.submit(i);
	}
		
	pool.start();

	int b = 0;

	for (int i = 1; i <= N; ++i) {
		try {
		vector<int> v;
		//v = futures[i].get();
		factors.insert(pair<int, vector<int>>(i, futures[i - 1].get()));
		int c = 0;
	}
				catch (const std::future_error& e) {
					std::cout << "Caught a future_error with code \"" << e.code()
						<< "\"\nMessage: \"" << e.what() << "\"\n";
				}
		}
	
	//system("pause");
	int a = 0;

}