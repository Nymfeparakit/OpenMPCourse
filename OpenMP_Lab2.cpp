#include <omp.h>
#include "stdio.h"
#include <chrono>
#include <iostream>
const int NMAX = 50;
const int LIMIT = 20;
void main()
{
	int i, j;
	float sum;
	float a[NMAX][NMAX];

	for (i = 0; i < NMAX; i++)
		for (j = 0; j < NMAX; j++)
			a[i][j] = i + j;

	std::chrono::steady_clock sc;
	auto start = sc.now();     // запускаем таймер
#pragma omp parallel shared(a) if (NMAX>LIMIT)
	{
#pragma omp for private(i,j,sum) 
		for (i = 0; i < NMAX; i++)
		{
			sum = 0;
			for (j = 0; j < NMAX; j++)
				sum += a[i][j];
			printf("Сумма элементов строки %d равна %f\n", i, sum);
		}
	} /* Завершение параллельного фрагмента */

	auto end = sc.now();     // останавливаем таймер
	auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Time: " << durationTime << std::endl;
	getchar();
}