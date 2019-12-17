#include "omp.h"`
#include <random>
#include <iostream>
#include <string>
#include <chrono>

int main()
{

	int arrSize = 4;
	//int arrSize = atoi(argv[1]);
	//выделяем память для двух массивов
	int* a = new int[arrSize];
	int* b = new int[arrSize];

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 4); // [1, 20] диапазон

																		   //заполняем их случайными значениями
	std::cout << "Array A " << std::endl;
	for (int i = 0; i < arrSize; ++i)
	{
		a[i] = dist6(rng);
		std::cout << a[i] << " ";//выводим при необходимости
	}
	std::cout << std::endl;

	std::cout << "Array B " << std::endl;
	for (int i = 0; i < arrSize; ++i)
	{
		b[i] = dist6(rng);
		std::cout << b[i] << " ";
	}
	std::cout << std::endl;

	std::chrono::steady_clock sc;

	
	auto start = sc.now();
	int numOfThreads = omp_get_num_procs();//узнаем число процессоров
	int totalSum = 0;
	omp_lock_t lock;
	omp_init_lock(&lock);
#pragma omp parallel num_threads(numOfThreads) //a, b, totalSum - shared по умолчанию
	{
#pragma omp for reduction(+ : totalSum) schedule(static) //i - private по умолчанию
		for (int i = 0; i < arrSize; ++i)
		{
			int value1 = a[i] + b[i];
			int value2 = 4 * a[i] - b[i];
			if (value2 > value1) value1 = value2;//присваиваем value1 макс значение
			if (value1 > 1) {
				omp_set_lock(&lock);
				totalSum += value1;
				omp_unset_lock(&lock);
			}
				
		}
		//std::string str = "I'm thread N" + std::to_string(omp_get_thread_num());
		//std::cout << str << std::endl;
	}

	omp_destroy_lock(&lock);
	auto end = sc.now();

	std::cout << "Total sum: " << totalSum << std::endl;//выводим итоговую сумму
	auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Time: " << durationTime << std::endl;

	

	//2 способ

	/*
	auto start = sc.now();
	int numOfThreads = omp_get_num_procs();//узнаем число процессоров
	int totalSum = 0;
	int* v1_arr = new int[arrSize];
	int* v2_arr = new int[arrSize];

#pragma omp parallel num_threads(numOfThreads) //a, b, totalSum - shared по умолчанию
	{
#pragma omp for 
		for (int i = 0; i < arrSize; ++i)
		{
			v1_arr[i] = a[i] + b[i];
			v2_arr[i] = 4 * a[i] - b[i];
		}

#pragma omp master
		{
			for (int i = 0; i < arrSize; ++i)
			{
				if (v2_arr[i] > v1_arr[i])
					v1_arr[i] = v2_arr[i]; // в v1_arr будут все максимальные значения
			}
		}

#pragma omp barrier

#pragma omp for reduction(+ : totalSum) schedule(static) //i - private по умолчанию
		for (int i = 0; i < arrSize; ++i)
		{
			if (v1_arr[i] > 1) totalSum += v1_arr[i];
		}

	}

	delete[] v1_arr;
	delete[] v2_arr;

	auto end = sc.now();

	std::cout << "Total sum: " << totalSum << std::endl;//выводим итоговую сумму
	auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Time: " << durationTime << std::endl;
	*/

	//очищаем память
	delete[] a;
	delete[] b;

	getchar();

}