#include "omp.h"
#include <random>
#include <iostream>
#include <string>
#include <chrono>

int main(int argc, char *argv[])
{
	//int arrSize = 100;
	int arrSize = atoi(argv[1]);
	//�������� ������ ��� ���� ��������
	int* a = new int[arrSize];
	int* b = new int[arrSize];

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 20); // [1, 20] ��������

	//��������� �� ���������� ����������
	std::cout << "Array A " << std::endl;
	for (int i = 0; i < arrSize; ++i)
	{
		a[i] = dist6(rng);
		//std::cout << a[i] << " ";//������� ��� �������������
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
	int numOfThreads = omp_get_num_procs();//������ ����� �����������
	int totalSum = 0;
#pragma omp parallel num_threads(numOfThreads) //a, b, totalSum - shared �� ���������
//#pragma omp parallel //�� ��������� �� ���� ������� ����� ������� �� ����� �����������
	{
#pragma omp for reduction(+ : totalSum) schedule(static) //i - private �� ���������
		for (int i = 0; i < arrSize; ++i)
		{
			int value1 = a[i] + b[i];
			int value2 = 4 * a[i] - b[i];
			if (value2 > value1) value1 = value2;//����������� value1 ���� ��������
			if (value1 > 1) totalSum += value1;
		}
		//std::string str = "I'm thread N" + std::to_string(omp_get_thread_num());
		//std::cout << str << std::endl;
	}
	auto end = sc.now();

	std::cout << "Total sum: " << totalSum << std::endl;//������� �������� �����
	auto durationTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Time: " << durationTime << std::endl;

	//������� ������
	delete[] a;
	delete[] b;

	getchar();
}


