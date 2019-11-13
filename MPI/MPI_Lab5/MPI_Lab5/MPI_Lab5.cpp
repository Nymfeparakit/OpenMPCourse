#include "mpi.h"
#include <complex>
#include <random>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	const int matrix_size = 2;
	const int number_of_matrices = 30;
	int proc_num, proc_rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
	MPI_Datatype row;
	//строка определяется как последовательность complex коэффициентов
	MPI_Type_contiguous(matrix_size, MPI_DOUBLE_COMPLEX, &row);
	MPI_Type_commit(&row);

	//обяъвляем тип матрица
	MPI_Datatype com_matr;
	MPI_Type_contiguous(matrix_size, row, &com_matr);
	MPI_Type_commit(&com_matr);

	complex<double> matrices[number_of_matrices][matrix_size][matrix_size];
	if (proc_rank == 0) { //только в 0 процессе генерируем все матрицы
						  //Генерируем рандомные коэффициенты
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5); // [1, 20] диапазон

																			  //заполняем их случайными значениями
		std::cout << "Matrices: " << std::endl;
		for (int i = 0; i < number_of_matrices; ++i)
		{
			for (int j = 0; j < matrix_size; ++j)
			{
				for (int k = 0; k < matrix_size; ++k) {
					matrices[i][j][k] = dist6(rng);
					cout << matrices[i][j][k] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

	}



}

