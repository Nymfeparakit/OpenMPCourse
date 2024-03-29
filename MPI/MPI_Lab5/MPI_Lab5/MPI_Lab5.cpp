#include "mpi.h"
#include <complex>
#include <random>
#include <iostream>
typedef std::complex<double> dcomp;

using namespace std;

#define print_once(x, proc_rank) if (proc_rank == 0) cout << #x << ": " << x << endl;
#define print_for_proc(x, proc_rank) cout << "rank " << proc_rank << ", " << #x << ": " << x << endl;

void print_arr(int *arr, int size) { 
	for (int i = 0; i < size; ++i) {cout << to_string(arr[i]) << " ";}
	cout << endl;
}

void print_arr(dcomp *arr, int size) {
	for (int i = 0; i < size; ++i) { 
		cout << arr[i] << " "; }
	cout << endl;
}

complex<double> **allocate_2d_array(int size) {

	complex<double> *data = new complex<double>[size * size];
	complex<double> **array = new complex<double>*[size];
	for (int i = 0; i<size; i++)
		array[i] = &(data[size*i]);

	return array;

}

void deallocate_2d_array(complex<double> **a, int size) {

	//for (int i = 0; i < size; ++i) {
	delete[] a[0];
	//}
	delete[] a;

}

void print_matr(complex<double>** a, int n) {

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

}

//из общего массива матриц выбирает одну конкретную
void select_matr(complex<double>* matrices, complex<double>**& matr,
	int matr_num, int matr_size)
{
	cout << "call select_matr";
	for (int i = 0; i<matr_size; i++)
		matr[i] = &(matrices[matr_num*matr_size*matr_size + i * matr_size]);
}

int new_size(int size) {
	int new_s = 1;
	while ((size >>= 1) != 0) 
		new_s++;
	return new_s;
}

void divide_matr(complex<double> **a, complex<double>**& a11,
	complex<double>**& a12, complex<double>**& a21,
	complex<double> **& a22, int size)
{

	a11 = allocate_2d_array(size / 2);
	a12 = allocate_2d_array(size / 2);
	a21 = allocate_2d_array(size / 2);
	a22 = allocate_2d_array(size / 2);

	for (int i = 0; i < size / 2; ++i) {
		for (int j = 0; j < size / 2; ++j) {
			a11[i][j] = a[i][j];
		}
	}

	for (int i = 0; i < size / 2; ++i) {
		for (int j = size / 2; j < size; ++j) {
			a12[i][j - size / 2] = a[i][j];
		}
	}

	for (int i = size / 2; i < size; ++i) {
		for (int j = 0; j < size / 2; ++j) {
			a21[i - size / 2][j] = a[i][j];
		}
	}

	for (int i = size / 2; i < size; ++i) {
		for (int j = size / 2; j < size; ++j) {
			a22[i - size / 2][j - size / 2] = a[i][j];
		}
	}

}

void sum_matr(complex<double> **a, complex<double> **b, complex<double> **res, int size)
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			dcomp aa = a[i][j];
			dcomp bb = b[i][j];
			dcomp cc = res[i][j];
			res[i][j] = a[i][j] + b[i][j];
		}
	}
}

void min_matr(complex<double> **a, complex<double> **b, complex<double> **res, int size)
{
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			res[i][j] = a[i][j] - b[i][j];
		}
	}
}

void split_res_matr(dcomp **p[7], dcomp** c, int size)
{
	dcomp **c11; dcomp **c12; dcomp **c21; dcomp **c22;
	c11 = allocate_2d_array(size / 2);
	c12 = allocate_2d_array(size / 2);
	c21 = allocate_2d_array(size / 2);
	c22 = allocate_2d_array(size / 2);

	sum_matr(p[3], p[4], c11, size / 2);
	min_matr(c11, p[1], c11, size / 2);
	sum_matr(c11, p[5], c11, size / 2);

	sum_matr(p[0], p[1], c12, size / 2);

	sum_matr(p[2], p[3], c21, size / 2);

	sum_matr(p[4], p[0], c22, size / 2);
	min_matr(c22, p[2], c22, size / 2);
	min_matr(c22, p[6], c22, size / 2);

	for (int i = 0; i < size / 2; ++i) {
		for (int j = 0; j < size / 2; ++j) {
			c[i][j] = c11[i][j];
		}
	}

	for (int i = 0; i < size / 2; ++i) {
		for (int j = size / 2; j < size; ++j) {
			c[i][j] = c12[i][j - size / 2];
		}
	}

	for (int i = size / 2; i < size; ++i) {
		for (int j = 0; j < size / 2; ++j) {
			c[i][j] = c21[i - size / 2][j];
		}
	}

	for (int i = size / 2; i < size; ++i) {
		for (int j = size / 2; j < size; ++j) {
			c[i][j] = c22[i - size / 2][j - size / 2];
		}
	}

	//cout << "c: " << endl;
	//print_matr(c, size);

	deallocate_2d_array(c11, size / 2);
	deallocate_2d_array(c12, size / 2);
	deallocate_2d_array(c21, size / 2);
	deallocate_2d_array(c22, size / 2);
}

void mul(complex<double> **a, complex <double> **b, complex <double> **c, int n)
{
	if (n == 2) {
		c[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
		c[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
		c[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
		c[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
		return;
	}

	dcomp **s[10];
	for (int i = 0; i < 10; ++i) {
		s[i] = allocate_2d_array(n / 2);
	}

	dcomp **a11; dcomp **a12; dcomp** a21; dcomp** a22;
	dcomp **b11; dcomp **b12; dcomp** b21; dcomp** b22;

	divide_matr(a, a11, a12, a21, a22, n);
	divide_matr(b, b11, b12, b21, b22, n);

	min_matr(b12, b22, s[0], n / 2);
	sum_matr(a11, a12, s[1], n / 2);
	sum_matr(a21, a22, s[2], n / 2);
	min_matr(b21, b11, s[3], n / 2);
	sum_matr(a11, a22, s[4], n / 2);
	sum_matr(b11, b22, s[5], n / 2);
	min_matr(a12, a22, s[6], n / 2);
	sum_matr(b21, b22, s[7], n / 2);
	min_matr(a11, a21, s[8], n / 2);
	sum_matr(b11, b12, s[9], n / 2);

	dcomp** p[7];
	for (int i = 0; i < 7; ++i) {
		p[i] = allocate_2d_array(n / 2);
	}

	mul(a11, s[0], p[0], n / 2);
	mul(s[1], b22, p[1], n / 2);
	mul(s[2], b11, p[2], n / 2);
	mul(a22, s[3], p[3], n / 2);
	mul(s[4], s[5], p[4], n / 2);
	mul(s[6], s[7], p[5], n / 2);
	mul(s[8], s[9], p[6], n / 2);

	/*
	for (int i = 0; i < 7; ++i) {
		cout << "p" << i + 1 << endl;
		print_matr(p[i], n / 2);
		cout << endl;
	}
	*/

	for (int i = 0; i < 10; ++i) {
		deallocate_2d_array(s[i], n / 2);
	}

	split_res_matr(p, c, n);

	for (int i = 0; i < 7; ++i) {
		deallocate_2d_array(p[i], n / 2);
	}

	deallocate_2d_array(a11, n / 2);
	deallocate_2d_array(a12, n / 2);
	deallocate_2d_array(a21, n / 2);
	deallocate_2d_array(a22, n / 2);
	deallocate_2d_array(b11, n / 2);
	deallocate_2d_array(b12, n / 2);
	deallocate_2d_array(b21, n / 2);
	deallocate_2d_array(b22, n / 2);

}

int main(int argc, char* argv[])
{
	const int matrix_size = 8;
	const int new_s = new_size(matrix_size);
	const int number_of_matrices = 20;
	int proc_num, proc_rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
	MPI_Datatype row;
	print_once(new_s, proc_rank);

	//обяъвляем тип матрица
	MPI_Datatype com_matr;
	MPI_Datatype com_matr_half;
	//MPI_Type_contiguous(matrix_size, row, &com_matr);
	MPI_Type_contiguous(matrix_size*matrix_size, MPI_DOUBLE_COMPLEX, &com_matr);
	MPI_Type_contiguous((matrix_size / 2) * (matrix_size / 2), MPI_DOUBLE_COMPLEX, &com_matr_half);
	MPI_Type_commit(&com_matr);
	MPI_Type_commit(&com_matr_half);

	complex<double> *matrices = nullptr;
	if (proc_rank == 0) { //только в 0 процессе генерируем все матрицы
						  //Генерируем рандомные коэффициенты
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5); // [1, 20] диапазон
		matrices = new complex<double>[number_of_matrices*matrix_size*matrix_size];

																			  //заполняем их случайными значениями
		std::cout << "Matrices: " << std::endl;
		complex<double> *data = new complex<double>[number_of_matrices*matrix_size*matrix_size];
		for (int j = 0; j < number_of_matrices*matrix_size*matrix_size; ++j) {
			//data[j] = dist6(rng);
			//matrices[j] = data[j];
			matrices[j] = 1;
			cout << matrices[j] << " ";
			if (j % number_of_matrices == 0)
			{
				cout << endl;
			}
		}
		for (int i = 0; i < number_of_matrices; ++i)
		{
			/*
			for (int j = 0; j < matrix_size; ++j)
			{
				for (int k = 0; k < matrix_size; ++k) {
					matrices[i][j][k] = dist6(rng);
					cout << matrices[i][j][k] << " ";
				}
				std::cout << std::endl;
			}
			*/
			

			/*for (int j = 0; j < matrix_size; ++j) {
				arr[j] = &(data[matrix_size*j]);
			}*/
			//matrices[i] = &(data[matrix_size*matrix_size*i]);
			//std::cout << std::endl;
		}
		//std::cout << std::endl;

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
	//if (!last_proc_in_work) --num_used_groups; //не используем последнюю группу с одним процессом
	if (last_group_has_2) ++num_used_groups;//добавляем в число изначальных групп еще одну
	print_once(num_used_groups, proc_rank);

	if (number_of_matrices < num_used_groups * 2 || proc_num == 1) { //если слишком мало матриц

		//рассчитываем все на одном процессе
		if (proc_rank == 0) {
			dcomp **first_matr = allocate_2d_array(matrix_size);
			dcomp **second_matr = allocate_2d_array(matrix_size);
			for (int i = 1; i < number_of_matrices; ++i) {

				if (i == 1) {
					select_matr(matrices, first_matr, i - 1, matrix_size);
				}
				//dcomp** second_matr = allocate_2d_array(matrix_size);
				select_matr(matrices, second_matr, i, matrix_size);
				mul(first_matr, second_matr, first_matr, matrix_size);

			}

			cout << endl;
			cout << "result: " << endl;
			print_matr(first_matr, matrix_size);
		} 

		MPI_Finalize();
		return 0;

	}

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
	int* displs = nullptr;
	int* send_counts = nullptr;
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


	//матрицы получат 0,3,6 .. процессы
	MPI_Group world_group;
	MPI_Comm_group(MPI_COMM_WORLD, &world_group);
	int* ranks = new int[num_used_groups];
	int i = 0;
	for (int i = 0; i < num_used_groups; ++i) {
		ranks[i] = i * 3;
	}
	print_arr(ranks, num_used_groups);
	MPI_Group masters_group;
	MPI_Comm masters_comm;
	MPI_Group_incl(world_group, num_used_groups, ranks, &masters_group);
	delete[] ranks;
	MPI_Comm_create(MPI_COMM_WORLD, masters_group, &masters_comm);
	int masters_rank;
	if (proc_rank %3 == 0 && !(!last_proc_in_work && proc_rank == proc_num - 1)) 
		MPI_Comm_rank(masters_comm, &masters_rank);

	complex<double> *recv_matrices = nullptr;
	if (proc_rank % 3 == 0 && !(!last_proc_in_work && proc_rank == proc_num - 1))
	{
		cout << "start recieve base data, rank: " << proc_rank << endl;
		//complex<double> recv_matrices[number_of_matrices][matrix_size][matrix_size];


		//complex<double> **recv_matrices[number_of_matrices];
		//complex<double> **recv_matrices = new complex<double>*[number_of_matrices];
		recv_matrices = new complex<double>[number_of_matrices*matrix_size*matrix_size];

		complex<double> *data = new complex<double>[number_of_matrices*matrix_size*matrix_size];
		for (int i = 0; i < number_of_matrices; ++i)
		{

			//complex<double> **arr = new complex<double>*[matrix_size];
			/*for (int j = 0; j < matrix_size; ++j) {
				arr[j] = &(data[matrix_size*j]);
			}*/
			//recv_matrices[i] = &(data[matrix_size*matrix_size*i]);
		}
		int a = 0;
		print_once(a, proc_rank);

		//int MPI_Scatterv(const void* sendbuf, const int sendcounts[],
		//const int displs[], MPI_Datatype sendtype, void* recvbuf,
		//int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

		/*MPI_Scatterv(&(matrices[0][0]), send_counts, displs, com_matr,
		 recv_matrices, recv_count, com_matr, 0,
			masters_comm);*/
		MPI_Barrier(masters_comm);
		MPI_Scatterv(matrices, send_counts, displs, com_matr,
			recv_matrices, recv_count, com_matr, 0,
			masters_comm);

		cout << proc_rank << " get matr ok" << endl;

		/*
		if (proc_rank == 6) {
			for (int jj = 0; jj < number_of_matrices*matrix_size*matrix_size; ++jj) {
				cout << recv_matrices[jj] << " ";
				if (jj % number_of_matrices == 0)
				{
					cout << endl;
				}
			}
		}
		*/

		//MPI_Comm_free(&masters_comm);

	}

	MPI_Comm comm2;
	MPI_Comm_split(MPI_COMM_WORLD, color, proc_rank, &comm2);
	int rank2, size2;
	MPI_Comm_rank(comm2, &rank2);
	MPI_Comm_size(comm2, &size2);

	//cout << "rank_01: " << proc_rank << "  rank_02: " << rank2 << endl;
	MPI_Barrier(comm2);

	dcomp** first_matr = allocate_2d_array(matrix_size);
	if (rank2 == 0 && size2 >= 2) { //это тот процесс, который ранее получил матрицы
		
		
		for (int ii = 1; ii < recv_count; ++ii) {

		/*
		if (proc_rank == 0) {
			cout << "recv_matr" << endl;
			for (int j = 0; j < 2; ++j) {
				for (int k = 0; k < matrix_size; ++k) {
					for (int kk = 0; kk < matrix_size; ++kk) {
						cout << recv_matrices[j*matrix_size*matrix_size + k * matrix_size + kk] << " ";
					}
					cout << endl;
				}
				cout << endl;
				cout << endl;
			}
			cout << endl;
		}
		*/
		

			dcomp **s[10];
			for (int i = 0; i < 10; ++i) {
				s[i] = allocate_2d_array(matrix_size / 2);
			}

			dcomp **a11; dcomp **a12; dcomp** a21; dcomp** a22;
			dcomp **b11; dcomp **b12; dcomp** b21; dcomp** b22;

			//cout << "allocated s" << endl;

			
			//cout << "allocated first_matr";
			if (ii == 1) {
				select_matr(recv_matrices, first_matr, ii - 1, matrix_size);
			}
			dcomp** second_matr = allocate_2d_array(matrix_size);
			select_matr(recv_matrices, second_matr, ii, matrix_size);
			divide_matr(first_matr, a11, a12, a21, a22, matrix_size);
			divide_matr(second_matr, b11, b12, b21, b22, matrix_size);

			/*
			if (proc_rank == 0) {
				cout << "first_matr" << endl;
				print_matr(first_matr, matrix_size);
				cout << "second_matr" << endl;
				print_matr(second_matr, matrix_size);
			}
			*/
		

			min_matr(b12, b22, s[0], matrix_size / 2);
			sum_matr(a11, a12, s[1], matrix_size / 2);
			sum_matr(a21, a22, s[2], matrix_size / 2);
			min_matr(b21, b11, s[3], matrix_size / 2);
			sum_matr(a11, a22, s[4], matrix_size / 2);
			sum_matr(b11, b22, s[5], matrix_size / 2);
			min_matr(a12, a22, s[6], matrix_size / 2);
			sum_matr(b21, b22, s[7], matrix_size / 2);
			min_matr(a11, a21, s[8], matrix_size / 2);
			sum_matr(b11, b12, s[9], matrix_size / 2);

			dcomp** p[7];
			for (int i = 0; i < 7; ++i) {
				p[i] = allocate_2d_array(matrix_size / 2);
			}

			//p1,p2,p3 вычисляем сами
			mul(a11, s[0], p[0], matrix_size / 2);
			mul(s[1], b22, p[1], matrix_size / 2);
			mul(s[2], b11, p[2], matrix_size / 2);
			
			//отправляем нужные матрицы для вычисления остальных p
			MPI_Send(&(a22[0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 1, 0, comm2);
			//cout << "sent a22";
			MPI_Send(&(s[3][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 1, 1, comm2);
			MPI_Send(&(s[4][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 1, 2, comm2);
			MPI_Send(&(s[5][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 1, 3, comm2);
			//cout << "sent s";
			int dest = -1;
			if (size2 == 3)
			{
				dest = 2;
			}
			else
			{
				dest = 1;
			}
			MPI_Send(&(s[6][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, dest, 4, comm2);
			MPI_Send(&(s[7][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, dest, 5, comm2);
			MPI_Send(&(s[8][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, dest, 6, comm2);
			MPI_Send(&(s[9][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, dest, 7, comm2);

			//cout << "sent s" << endl;

			//собираем p от других процессов
			MPI_Status status;
			MPI_Recv(&(p[3][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 1, 0, comm2, &status);
			MPI_Recv(&(p[4][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 1, 1, comm2, &status);
			MPI_Recv(&(p[5][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, dest, 2, comm2, &status);
			MPI_Recv(&(p[6][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, dest, 3, comm2, &status);

			//cout << "receive p" << endl;
			
			split_res_matr(p, first_matr, matrix_size);
		}

		/*if (proc_rank == 6) {
			cout << "first_matr of proc 6" << endl;
			print_matr(first_matr, matrix_size);
		}*/

		cout << "rank 0 out of cycle, proc_rank" << proc_rank << endl;
		

	}
	else if (rank2 == 1 && size2 == 3) {
		
		for (int ii = 1; ii < recv_count; ++ii) {
			//ожмдаем нужные матрицы для вычисления p
			dcomp **a22 = allocate_2d_array(matrix_size / 2);
			dcomp **s4_6[3];
			for (int i = 0; i < 3; ++i) {
				s4_6[i] = allocate_2d_array(matrix_size / 2);
			}

			MPI_Status status;
			MPI_Recv(&(a22[0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 0, comm2, &status);
			//cout << "I ve received a22" << endl;
			//MPI_Recv(&(s4_6[0][0]), 3, com_matr_half, 0, 1, comm2, &status);
			MPI_Recv(&(s4_6[0][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 1, comm2, &status);
			MPI_Recv(&(s4_6[1][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 2, comm2, &status);
			MPI_Recv(&(s4_6[2][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 3, comm2, &status);
			//cout << "I ve received s4_6" << endl;

			dcomp **p[2];
			for (int i = 0; i < 2; ++i) {
				p[i] = allocate_2d_array(matrix_size / 2);
			}

			//вычисляем p
			mul(a22, s4_6[0], p[0], matrix_size / 2);
			mul(s4_6[1], s4_6[2], p[1], matrix_size / 2);

			//отправляем p
			MPI_Send(&(p[0][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 0, comm2);
			MPI_Send(&(p[1][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 1, comm2);

		}

		cout << "rank 1 out of cycle, proc_rank" << proc_rank << endl;

	}
	else if (rank2 == 1 && size2 == 2)
	{
		MPI_Status status;
		for (int ii = 1; ii < recv_count; ++ii)
		{

			dcomp **a22 = allocate_2d_array(matrix_size / 2);
			dcomp **s4_6[3];
			for (int i = 0; i < 3; ++i) {
				s4_6[i] = allocate_2d_array(matrix_size / 2);
			}
			dcomp **s7_10[4];
			for (int i = 0; i < 4; ++i) {
				s7_10[i] = allocate_2d_array(matrix_size / 2);
			}

			dcomp **p[2];
			for (int i = 0; i < 2; ++i) {
				p[i] = allocate_2d_array(matrix_size / 2);
			}

			dcomp **pp[2];
			for (int i = 0; i < 2; ++i) {
				pp[i] = allocate_2d_array(matrix_size / 2);
			}

			MPI_Recv(&(a22[0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 0, comm2, &status);
			MPI_Recv(&(s4_6[0][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 1, comm2, &status);
			MPI_Recv(&(s4_6[1][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 2, comm2, &status);
			MPI_Recv(&(s4_6[2][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 3, comm2, &status);

			/*if (ii == 1) {
				cout << "a22" << endl;
				print_matr(a22, matrix_size / 2);
				cout << "s4 " << endl;
				print_matr(s4_6[0], matrix_size / 2);
			}*/

			//вычисляем p
			mul(a22, s4_6[0], p[0], matrix_size / 2);
			mul(s4_6[1], s4_6[2], p[1], matrix_size / 2);

			MPI_Recv(&(s7_10[0][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 4, comm2, &status);
			MPI_Recv(&(s7_10[1][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 5, comm2, &status);
			MPI_Recv(&(s7_10[2][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 6, comm2, &status);
			MPI_Recv(&(s7_10[3][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 7, comm2, &status);

			//вычисляем p
			mul(s7_10[0], s7_10[1], pp[0], matrix_size / 2);
			mul(s7_10[2], s7_10[3], pp[1], matrix_size / 2);

			//отправляем p
			MPI_Send(&(p[0][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 0, comm2);
			MPI_Send(&(p[1][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 1, comm2);

			//отправляем p
			MPI_Send(&(pp[0][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 2, comm2);
			MPI_Send(&(pp[1][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 3, comm2);
		}
	}
	if (rank2 == 2) 
	{
		for (int ii = 1; ii < recv_count; ++ii) {

			MPI_Status status;
			dcomp **s7_10[4];
			for (int i = 0; i < 4; ++i) {
				s7_10[i] = allocate_2d_array(matrix_size / 2);
			}
			//ожмдаем нужные матрицы для вычисления p
			MPI_Recv(&(s7_10[0][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 4, comm2, &status);
			MPI_Recv(&(s7_10[1][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 5, comm2, &status);
			MPI_Recv(&(s7_10[2][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 6, comm2, &status);
			MPI_Recv(&(s7_10[3][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 7, comm2, &status);

			dcomp **p[2];
			for (int i = 0; i < 2; ++i) {
				p[i] = allocate_2d_array(matrix_size / 2);
			}

			//вычисляем p
			mul(s7_10[0], s7_10[1], p[0], matrix_size / 2);
			mul(s7_10[2], s7_10[3], p[1], matrix_size / 2);

			//отправляем p
			MPI_Send(&(p[0][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 2, comm2);
			MPI_Send(&(p[1][0][0]), (matrix_size / 2)*(matrix_size / 2), MPI_DOUBLE_COMPLEX, 0, 3, comm2);
		}

		cout << "rank 2 out of cycle, proc_rank" << proc_rank << endl;

	}

	MPI_Comm_free(&comm2);

	if (proc_rank % 3 == 0) {
		complex<double>* recv_matrices_final = new complex<double>[num_used_groups*matrix_size*matrix_size];
		complex<double>* first_matrices_final = new complex<double>[matrix_size*matrix_size];
		for (int i = 0; i < matrix_size; ++i)
		{
			for (int j = 0; j < matrix_size; ++j)
			{
				*(first_matrices_final + j + matrix_size * i) = first_matr[i][j];
			}
		}

		/*if (proc_rank == 3) {
			cout << "first matr of rank 3" << endl;
			print_arr(first_matrices_final, matrix_size*matrix_size);
			//print_matr(first_matr, matrix_size);
		}*/

		/*if (proc_rank == 6) {
			cout << "first matr of rank 6" << endl;
			print_matr(first_matr, matrix_size);
		}*/

		if (proc_rank % 3 == 0 && !(!last_proc_in_work && proc_rank == proc_num - 1)) {
			MPI_Barrier(masters_comm);
			MPI_Gather(&(first_matrices_final[0]), matrix_size*matrix_size, MPI_DOUBLE_COMPLEX, recv_matrices_final,
				matrix_size*matrix_size, MPI_DOUBLE_COMPLEX, 0, masters_comm);
			cout << proc_rank << " proc gathered data + num_used_groups: " << num_used_groups << endl;
		}
		

		if (proc_rank == 0)
		{

			/*select_matr(recv_matrices, first_matr, 1, matrix_size);
			cout << "recv 1" << endl;
			print_matr(first_matr, matrix_size);*/

			for (int jj = 0; jj < num_used_groups; ++jj) {
				cout << "recv " << jj << endl;
				select_matr(recv_matrices_final, first_matr, jj, matrix_size);
				print_matr(first_matr, matrix_size);
			}

			// Перемножить массивы
			for (int i = 1; i < num_used_groups; ++i) {

				if (i == 1) {
					select_matr(recv_matrices_final, first_matr, i - 1, matrix_size);
				}
				dcomp** second_matr = allocate_2d_array(matrix_size);
				select_matr(recv_matrices_final, second_matr, i, matrix_size);
				mul(first_matr, second_matr, first_matr, matrix_size);

			}

			//Выводим результат
			cout << "result: " << endl;
			print_matr(first_matr, matrix_size);
		}
	}

	//отправляем все полученные c 0му процессу и он их перемножает
	//если число матриц слишком мало, то их все перемножает 0 процесс
	
	//MPI_Group_free(&world_group);
	//MPI_Group_free(&masters_group);

	if (proc_rank == 0) {
		
		//for (int i = 0; i < number_of_matrices; ++i) {
			/*
		    for (int j = 0; j < number_of_matrices; ++j) {
				delete [] matrices[j];
			}
			*/
			//delete[] matrices[0];
			//delete[] matrices[1];
			//delete[] matrices;
		//}

	}
	

	MPI_Finalize();

}


