#include "omp.h"
#include <random>
#include <iostream>
#include <chrono>
//вычисляет нужную сумму частично
int calc_partial_sum(int* a, int* b, int begin, int end);

int main()
{
	int arrSize = 20;
	//int arrSize = atoi(argv[1]);
	//выделяем память для двух массивов
	int* a = new int[arrSize];
	int* b = new int[arrSize];

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10); // [1, 20] диапазон

																		   //заполняем их случайными значениями
	std::cout << "Array A " << std::endl;
	for (int i = 0; i < arrSize; ++i)
	{
		a[i] = dist6(rng);
		//a[i] = i + 1;
		std::cout << a[i] << " ";//выводим при необходимости
	}
	std::cout << std::endl;

	std::cout << "Array B " << std::endl;
	for (int i = 0; i < arrSize; ++i)
	{
		b[i] = dist6(rng);
		//b[i] = i + 1;
		std::cout << b[i] << " ";
	}
	std::cout << std::endl;

	std::chrono::steady_clock sc;
	auto start = sc.now();
	int num_of_procs = omp_get_num_procs();//узнаем число процессоров

	//1 способ
	int total_sum = 0;
	int chunk_size = arrSize / 4;//число элементов для каждого потока
	int offsets[4];
	for (short i = 0; i < 4; ++i) {
		offsets[i] = chunk_size * i;
	}
	int partial_sum1, partial_sum2, partial_sum3, partial_sum4;
#pragma omp parallel sections num_threads(4) reduction(+ : total_sum) firstprivate(chunk_size, a, b)
	//каждый поток имеет свою копию a, b но они все указывают на один и тот же адрес
//#pragma omp parallel sections num_threads(4) firstprivate(chunk_size, a, b)
	{
#pragma omp section
		{
			partial_sum1 = calc_partial_sum(a, b, offsets[0], offsets[0] + chunk_size);
			total_sum += partial_sum1;
			//total_sum = calc_partial_sum(a, b, offsets[0], offsets[0] + chunk_size);
		}
#pragma omp section
		{
			partial_sum2 = calc_partial_sum(a, b, offsets[1], offsets[1] + chunk_size);
			total_sum += partial_sum2;
			//total_sum = calc_partial_sum(a, b, offsets[1], offsets[1] + chunk_size);
		}
#pragma omp section
		{
			partial_sum3 = calc_partial_sum(a, b, offsets[2], offsets[2] + chunk_size);
			total_sum += partial_sum3;
			//total_sum = calc_partial_sum(a, b, offsets[2], offsets[2] + chunk_size);
		}
#pragma omp section
		{
			partial_sum4 = calc_partial_sum(a, b, offsets[3], arrSize);
			total_sum += partial_sum4;
			//total_sum = calc_partial_sum(a, b, offsets[3], arrSize);
		}
	}
	//total_sum = partial_sum1 + partial_sum2 + partial_sum3 + partial_sum4;

	auto end = sc.now();
	std::cout << "Total sum parallel first way: " << total_sum << std::endl;//выводим итоговую сумму
	auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Time: " << durationTime << std::endl;

	//2 способ
	start = sc.now();
	int* v1_arr = new int[arrSize];
	int* v2_arr = new int[arrSize];

	omp_set_nested(true);
	int num_of_nested_threads = num_of_procs / 2;
#pragma omp parallel sections num_threads(2) 
	{
#pragma omp section
		{
#pragma omp parallel num_threads(num_of_nested_threads)
			{
				#pragma omp for
					for (int i = 0; i < arrSize / 2; ++i) {
						v1_arr[i] = a[i] + b[i];
					}
					//std::cout << "thread1" << std::endl;
			}
		}
#pragma omp section
		{
#pragma omp parallel num_threads(num_of_nested_threads) 
			{
#pragma omp for
				for (int i = arrSize / 2; i < arrSize; ++i) {
					v2_arr[i] = 4 * a[i] - b[i];
				}
			
			//std::cout << "thread2" << std::endl;
			}
		}
	}

#pragma omp parallel sections num_threads(2) 
	{
#pragma omp section
		{
#pragma omp parallel num_threads(num_of_nested_threads)
			{
#pragma omp for
				for (int i = arrSize / 2; i < arrSize; ++i) {
					v1_arr[i] = a[i] + b[i];
				}
				//std::cout << "thread1" << std::endl;
			}
		}
#pragma omp section
		{
#pragma omp parallel num_threads(num_of_nested_threads) 
			{
#pragma omp for
				for (int i = 0; i < arrSize / 2; ++i) {
					v2_arr[i] = 4 * a[i] - b[i];
				}

				//std::cout << "thread2" << std::endl;
			}
		}
	}

	total_sum = 0;
#pragma omp parallel for reduction(+ : total_sum)
	for (int i = 0; i < arrSize; ++i) {
		if (v2_arr[i] > v1_arr[i]) v1_arr[i] = v2_arr[i];//присваиваем value1 макс значение
		if (v1_arr[i] > 1) total_sum += v1_arr[i];
	}
	
	delete[] v1_arr;
	delete[] v2_arr;

	end = sc.now();
	std::cout << "Total sum parallel second way: " << total_sum << std::endl;//выводим итоговую сумму
	durationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Time: " << durationTime << std::endl;
 

	total_sum = calc_partial_sum(a, b, 0, arrSize);
	std::cout << "Total sum: " << total_sum << std::endl;//выводим итоговую сумму

	delete[] a;
	delete[] b;

	getchar();
    return 0;
}

int calc_partial_sum(int* a, int* b, int begin, int end)
{
	int partial_sum = 0;
	for (int i = begin; i < end; ++i) {
		int value1 = a[i] + b[i];
		int value2 = 4 * a[i] - b[i];
		if (value2 > value1) value1 = value2;//присваиваем value1 макс значение
		if (value1 > 1) partial_sum += value1;
	}
	//std::cout << "Partial sum: " << partial_sum << std::endl;
	return partial_sum;
}

