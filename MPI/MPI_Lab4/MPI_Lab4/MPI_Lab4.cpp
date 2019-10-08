// MPI_Lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include "mpi.h"

int main(int argc, char* argv[])
{
	int polynom_size = 3;
	int number_of_plnms = 4;
	int proc_num, proc_rank;
		
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

	double** polynoms;
	if (proc_rank == 0) { //только в 0 процессе генерируем все полиномы
		polynoms = new double* [number_of_plnms];
		for (int i = 0; i < number_of_plnms; ++i)
		{
			//нужно зарезервировать больше места, так как степени полиномов буду увеличиваться
			polynoms[i] = new double[polynom_size * number_of_plnms];
		}
		//Генерируем рандомные коэффициенты
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 20); // [1, 20] диапазон

		//заполняем их случайными значениями
		std::cout << "Polynoms: " << std::endl;
		for (int i = 0; i < number_of_plnms; ++i)
		{
			std::cout << i << ": ";
			//заполняем последние polynom_size коэффициентов числами
			for (int j = polynom_size - 1; j >= 0; --j)
			{
				polynoms[i][j] = dist6(rng);
				std::cout << polynoms[i][j] << " ";//выводим при необходимости
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	
	if (proc_rank == 0) {//процесс с рангом 0 отправляет другим процессам полиномы
							// которые нужно перемножить 
		int number_of_steps = number_of_plnms / 2;
		if (number_of_plnms % 2 == 0) --number_of_steps;
		for (int i = number_of_steps; i > 0; --i) {

		}
	}
	else {

	}
	
	
	if (proc_rank == 0) {
		//Очищаем память
		for (int i = 0; i < number_of_plnms; ++i)
		{
			delete[] polynoms[i];
		}
		delete[] polynoms;
	}
}


