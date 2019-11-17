#include "mpi.h"
#include <complex>
#include <random>
#include <iostream>

using namespace std;

#define print_once(x, proc_rank) if (proc_rank == 0) cout << #x << ": " << x << endl;
#define print_for_proc(x, proc_rank) cout << "rank " << proc_rank << ", " << #x << ": " << x << endl;

void print_arr(int *arr, int size) { 
	for (int i = 0; i < size; ++i) {cout << to_string(arr[i]) << " ";}
	cout << endl;
}

int main(int argc, char* argv[])
{
	const int matrix_size = 2;
	const int number_of_matrices = 20;
	int proc_num, proc_rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
	MPI_Datatype row;
	//TODO сделать для динамических массивов?
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

	print_once(proc_num, proc_rank);
	//определяем изначальное число групп
	int num_groups = proc_num / 3;
	//print_once(num_groups, proc_rank);
	bool last_group_has_2 = proc_num % 3 == 2 ? 1 : 0;//в последней группе 2 процесса
	bool last_proc_in_work = proc_num % 3 == 1 ? 0 : 1; //остался ли лишний 1 процесс
	print_once(last_group_has_2, proc_rank);
	print_once(last_proc_in_work, proc_rank);

	int num_used_groups = num_groups;//определяем реальное число используемых групп
	if (!last_proc_in_work) --num_used_groups; //не используем последнюю группу с одним процессом
	else if (last_group_has_2) ++num_used_groups;//добавляем в число изначальных групп еще одну
	print_once(num_used_groups, proc_rank);

	int default_chunk_size = number_of_matrices / num_used_groups;//количество матриц, которое получает каждый  главный процесс
														//в группе
	print_once(default_chunk_size, proc_rank);
														//число матриц, которые нужно будет докинуть
	int num_remaining_matr = number_of_matrices % num_used_groups;
	print_once(num_remaining_matr, proc_rank);
	//число первых групп, которым будет прислано default_chunk_size матриц
	int nmbr_of_frst_groups = num_used_groups - num_remaining_matr;
	print_once(nmbr_of_frst_groups, proc_rank);

	//выделяем группу, которая необходима для рассылки матриц
	//определяем ранги процессов, которые будут в этой группе
	int group_ranks;
	int* displs;
	int* send_counts;
	if (proc_rank == 0) {//процесс с рангом 0 отправляет другим процессам матрицы
						 // которые нужно перемножить
						 //выделяем память
		displs = new int[num_used_groups];
		send_counts = new int[num_used_groups];

		//определяем, какое число элементов должно быть отправлено
		//каждому из процессов
		for (int i = 0; i < nmbr_of_frst_groups; ++i) {
			send_counts[i] = default_chunk_size;
			displs[i] = default_chunk_size * i;
		}
		//Остальным процессам отправим на 1 элемент больше
		for (int i = nmbr_of_frst_groups; i < num_used_groups; ++i) {
			send_counts[i] = default_chunk_size + 1;
			displs[i] = (default_chunk_size + 1) * (i - nmbr_of_frst_groups)
				+ nmbr_of_frst_groups * default_chunk_size;
		}
		print_once(*displs, 0);
		print_arr(displs, num_used_groups);
		print_once(*send_counts, 0);
		print_arr(send_counts, num_used_groups);
	
	}

	int color = proc_rank / 3;//color можно считать и как номер группы
	int recv_count = -1;
	//определяем для каждого группы отдельно, сколько элементов она получит
	if (color < nmbr_of_frst_groups) {
		recv_count = default_chunk_size;
	}
	else {
		recv_count = default_chunk_size + 1;
	}
	print_for_proc(recv_count, proc_rank);

	
	//int MPI_Scatterv(const void* sendbuf, const int sendcounts[],
	//const int displs[], MPI_Datatype sendtype, void* recvbuf,
	//int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

	//матрицы получат 0,3,6 .. процессы
	MPI_Group world_group;
	MPI_Comm_group(MPI_COMM_WORLD, &world_group);
	int* ranks = new int[num_used_groups];
	int i = 0;
	for (int i = 0; i < num_used_groups; ++i) {
		ranks[i] = i * 3;
	}
	MPI_Group masters_group;
	MPI_Comm masters_comm;
	MPI_Group_incl(world_group, num_used_groups, ranks, &masters_group);
	delete[] ranks;
	MPI_Comm_create(MPI_COMM_WORLD, masters_group, &masters_comm);

	if (proc_rank % 3 == 0) {
		complex<double> recv_matrices[number_of_matrices][matrix_size][matrix_size];
		MPI_Scatterv(matrices, send_counts, displs, com_matr, recv_matrices, recv_count, com_matr, 0,
			masters_comm);

		/*if (proc_rank == 6) {

			cout << "matr for rank " + proc_rank << endl;
			for (int i = 0; i < recv_count; ++i) {
				for (int j = 0; j < matrix_size; ++j) {
					for (int k = 0; k < matrix_size; ++k) {
						cout << recv_matrices[i][j][k] << " ";
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;

		}*/

		MPI_Comm_free(&masters_comm);//больше этот коммуникатор не нужен

	}

	//теперь делим все число процессов на группы по 3-2 процесса
	MPI_Comm сomm2;
	MPI_Comm_split(MPI_COMM_WORLD, color, proc_rank, &сomm2);
	int rank2, size2;
	MPI_Comm_rank(сomm2, &rank2);
	MPI_Comm_size(сomm2, &size2);

	if (rank2 == 0) { //это тот процесс, который ранее получил матрицы

	}

	MPI_Comm_free(&сomm2);
	
	MPI_Group_free(&world_group);
	MPI_Group_free(&masters_group);
	
	/*
	MPI_Comm comm2; 
	MPI_Comm_split(MPI_COMM_WORLD, color, proc_rank, &comm2);
	int size2, rank2;
	MPI_Comm_rank(comm2, &rank2);
	MPI_Comm_size(comm2, &size2);*/
	//0 поток имеет 2 матрицы
	//используем bcast для передачи первому и второму подматриц
	//для перемножения двух матриц:
	//делим каждую из матриц на 4 подматрицы
	//вычисляем p1, p2 .. p7
	//2 и 3 поток в группе отправляет p 1му потоку в группе
	//тот вычисляет все элементы, используя сложение

	MPI_Finalize();

}

