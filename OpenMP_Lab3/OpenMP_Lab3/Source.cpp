#include "omp.h"
#include <random>
#include <iostream>
#include <string>
#include <chrono>

int main(int argc, char *argv[])
{
	//int arrSize = 100;
	int arrSize = atoi(argv[1]);
	//выделяем память для двух массивов
	int* a = new int[arrSize];
	int* b = new int[arrSize];

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 20); // [1, 20] диапазон

	//заполняем их случайными значениями
	std::cout << "Array A " << std::endl;
	for (int i = 0; i < arrSize; ++i)
	{
		a[i] = dist6(rng);
		//std::cout << a[i] << " ";//выводим при необходимости
	}
	std::cout << std::endl;

	std::cout << "Array B " << std::endl;
	for (int i = 0; i < arrSize; ++i)
	{
		b[i] = dist6(rng);
		//std::cout << b[i] << " ";
	}
	std::cout << std::endl;

	std::chrono::steady_clock sc;
	auto start = sc.now();
	int numOfThreads = omp_get_num_procs();//узнаем число процессоров
	int totalSum = 0;
#pragma omp parallel num_threads(numOfThreads) //a, b, totalSum - shared по умолчанию
//#pragma omp parallel //по умолчанию он тоже создает число потоков по числу процессоров
	{
#pragma omp for reduction(+ : totalSum) schedule(static) //i - private по умолчанию
		for (int i = 0; i < arrSize; ++i)
		{
			int value1 = a[i] + b[i];
			int value2 = 4 * a[i] - b[i];
			if (value2 > value1) value1 = value2;//присваиваем value1 макс значение
			if (value1 > 1) totalSum += value1;
		}
		//std::string str = "I'm thread N" + std::to_string(omp_get_thread_num());
		//std::cout << str << std::endl;
	}
	auto end = sc.now();

	std::cout << "Total sum: " << totalSum << std::endl;//выводим итоговую сумму
	auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Time: " << durationTime << std::endl;

	//очищаем память
	delete[] a;
	delete[] b;

	getchar();
}


