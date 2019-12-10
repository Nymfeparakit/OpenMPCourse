#define _CRT_SECURE_NO_WARNINGS
#include "mpi.h"
#include <random>
#include <iostream>
#include "mul_utils.hpp"

using namespace std;

void print_arr(int *arr, int size) {
	for (int i = 0; i < size; ++i) { cout << arr[i] << " "; }
	cout << endl;
}

//[char] -> [vec<char>] -> [longint]
template<size_t numbers_count, size_t number_size>
void arr_char_to_arr_longint(int proc_rank, int real_numbers_count, char(&a)[numbers_count][number_size], longint(&b)[numbers_count])
{
	for (int i = 0; i < real_numbers_count; ++i) {

		vector<char> vec;
		for (int j = 0; j < number_size; ++j) {

			vec.push_back(a[i][j]);
			//b[i].number.push_back(a[i][j]);
		}
		longint lint(vec);
		b[i] = lint;

	}

}

char **allocate_2d_array(int rows, int columns) {

	char *data = new char[rows * columns];
	char **array = new char*[rows];
	for (int i = 0; i<rows; i++)
		array[i] = &(data[columns*i]);

	return array;

}

int main(int argc, char* argv[])
{

	const int number_size = 4; //����� �������� �������� � �����
	const int numbers_count = 10; //���������� ������������� �����
	int proc_num, proc_rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

	//�� 0��� �������� ������������ ��� �����
	char numbers[numbers_count][number_size];
	if (proc_rank == 0) { //������ � 0 �������� ���������� ��� �����
						  //���������� ��������� ������������
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5); // [1, 20] ��������

		std::cout << "Numbers: " << std::endl;
		for (int i = 0; i < numbers_count; ++i)
		{
			for (int j = 0; j < number_size; ++j)
			{
				//��������� ������ ������ 0 � 1
				numbers[i][j] = dist6(rng) % 2;
			}
			//numbers[i][0] = 0;
			numbers[i][1] = 1;
		}
		//numbers[numbers_count - 1][0] = 1;

		for (int i = 0; i < numbers_count; ++i)
		{
			for (int j = 0; j < number_size; ++j)
			{
				cout << numbers[i][j] + 0 << " ";
			}
			cout << endl;
		}
		std::cout << std::endl;

	}

	if (proc_rank == 0) { //����������� ���������������

		longint recv_numbers_lint_check[numbers_count];
		arr_char_to_arr_longint(proc_rank, numbers_count, numbers, recv_numbers_lint_check);

		for (int i = 0; i < numbers_count; ++i) {
			recv_numbers_lint_check[i].print();
		}

		for (int i = 1; i < numbers_count; ++i) {
			recv_numbers_lint_check[0] = ss_mult(recv_numbers_lint_check[0], recv_numbers_lint_check[i]);
		}

		cout << "sequential mul result: " << endl;
		recv_numbers_lint_check[0].print();

	}

	int recv_count;//����� ���������, ������� ������� �������
	int* send_counts = nullptr;//����� ������������ ����� ���������, ��� ������������ ������� ��������
	int* displs = nullptr;//�������� 
	if (numbers_count >= proc_num) { //���� ����� ������, ��� ���������

		int default_chunk_size = numbers_count / proc_num;//���������� ���������, ������� �������� ������ �������
														  //����� ���������� ���������, ��� ����� ����� �������� ��������� ���������
		int nmbr_of_remaining_plnms = numbers_count % proc_num;
		//����� ������ ���������, ������� ����� �������� default_chunk_size ���������
		int nmbr_of_frst_procs = proc_num - nmbr_of_remaining_plnms;

		if (proc_rank == 0) {//������� � ������ 0 ���������� ������ ��������� ��������
							 // ������� ����� �����������
							 //�������� ������
			displs = new int[proc_num];
			send_counts = new int[proc_num];

			//����������, ����� ����� ��������� ������ ���� ����������
			//������� �� ���������
			for (int i = 0; i < nmbr_of_frst_procs; ++i) {
				send_counts[i] = default_chunk_size * number_size;
				displs[i] = default_chunk_size * i * number_size;
			}
			//��������� ��������� �������� �� 1 ������� ������
			for (int i = nmbr_of_frst_procs; i < proc_num; ++i) {
				send_counts[i] = (default_chunk_size + 1) * number_size;
				displs[i] = ((default_chunk_size + 1) * (i - nmbr_of_frst_procs)
					+ nmbr_of_frst_procs * default_chunk_size) * number_size;
			}

			/*std::cout << "send_counts: " << std::endl;
			print_arr(send_counts, proc_num);*/

		}

		//���������� ��� ������� �������� ��������, ������� ��������� �� �������
		if (proc_rank < nmbr_of_frst_procs) {
			recv_count = default_chunk_size;
		}
		else {
			recv_count = default_chunk_size + 1;
		}



		char recv_numbers[numbers_count][number_size];

		//int MPI_Scatterv(const void* sendbuf, const int sendcounts[],
		//const int displs[], MPI_Datatype sendtype, void* recvbuf,
		//int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)


		//TODO ������ ���� ����, ���� ����� ��������� >=...
		MPI_Scatterv(&(numbers[0][0]), send_counts, displs, MPI_CHAR, &(recv_numbers[0][0]), recv_count*number_size, MPI_CHAR, 0,
			MPI_COMM_WORLD);

		//������ ������� �� ������

		/*if (proc_rank == 1) {

		for (int i = 0; i < recv_count; ++i) {
		for (int j = 0; j < number_size; ++j) {
		cout << recv_numbers[i][j] << " ";
		}
		cout << endl;
		}

		}*/

		//��������� ��� � long int
		longint recv_numbers_lint[numbers_count];
		arr_char_to_arr_longint(proc_rank, recv_count, recv_numbers, recv_numbers_lint);

		/* if (proc_rank == 1) {

		for (int i = 0; i < recv_count; ++i) {
		for (int j = 0; j < number_size; ++j) {
		cout << recv_numbers_lint[i].number[j] << " ";
		}
		cout << endl;
		}

		} */

		//������ ������ ������� ������� ����������� ���� �����
		for (int i = 1; i < recv_count; ++i) {
			//��������� ����������� ����� ������� � ������ ����� �������
			recv_numbers_lint[0] = ss_mult(recv_numbers_lint[0], recv_numbers_lint[i]);
		}

		//������ ������� �����
		//TODO ��� ������ ����, ����� ��������� �������
		int columns_num = proc_num / 2;
		int rows_num = 2;
		int dims[2]{ rows_num, columns_num };
		int periods[2]{ 1, 1 };//�� ������ ������ 1 1
		int reorder = 0; //����� ����� ��������� ��������� ��������
		MPI_Comm cart_comm;
		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cart_comm);
		int cart_rank = -1;
		MPI_Comm_rank(cart_comm, &cart_rank);
		//if (proc_rank == 7) print_arr(coords, 2);

		//������� �������� �������
		MPI_Comm column_comm;
		int subdims[2]{ 1, 0 };
		MPI_Cart_sub(cart_comm, subdims, &column_comm);
		int row_num_rank = -1; //����, ��������� � ������� ������
		MPI_Comm_rank(column_comm, &row_num_rank);

		//�� ������ ������, ��������� ���������� �����

		vector<char> result1 = recv_numbers_lint[0].number;
		unsigned int result1_size = -1;
		if (row_num_rank == 1) { //�������� �� ������ ������ ���������� ����� ��������� �� �������
								 //������� ���������� ������ �������, ����� ��� ���� ��������� �������
			result1_size = result1.size();

			MPI_Send(&result1_size, 1, MPI_UNSIGNED, 0, 0, column_comm);
			MPI_Send(&result1[0], result1_size, MPI_CHAR, 0, 1, column_comm);


		}
		else if (row_num_rank == 0) {

			unsigned int result2_size = -1;
			vector<char> result2; //���� ����� ������� ������, ���������� �� ������� ��������
			MPI_Status status;
			MPI_Recv(&result2_size, 1, MPI_UNSIGNED, 1, 0, column_comm, &status);
			result2.resize(result2_size);
			MPI_Recv(&result2[0], result2_size, MPI_UNSIGNED, 1, 1, column_comm, &status);

			//����������� ��� �����
			longint result1_lint(result1);
			longint result2_lint(result2);
			result1_lint = ss_mult(result1_lint, result2_lint);
			result1 = result1_lint.number;
			result1_size = result1.size();

		}

		//�������� ������������ ��� ������ ������
		//������� ������ ��� ������ ������
		int *coords = new int[2];
		MPI_Cart_coords(cart_comm, cart_rank, 2, coords);

		MPI_Comm row_comm;
		int subdims2[2]{ 0, 1 };
		MPI_Cart_sub(cart_comm, subdims2, &row_comm);
		int column_num_rank = -1; //����, ��������� � ������� �������
		MPI_Comm_rank(row_comm, &column_num_rank);

		if (coords[0] == 0) {

			//������ �� ������� �������� ������ ������������� �������
			const int col_num = columns_num;
			unsigned int recv_counts[numbers_count]; //����������� ��������� ��� ����� �� ������ ������, ��� �����
			MPI_Gather(&result1_size, 1, MPI_UNSIGNED, &recv_counts[0], 1, MPI_UNSIGNED, 0, row_comm);

			//������������ final_recv_counts � final_displs ��� �������� � mpi_gatherv
			int max_vec_size = 0;
			int *final_recv_counts = new int[proc_num / 2];
			int *final_displs = new int[proc_num / 2];
			if (column_num_rank == 0) {
				int num_of_prev_elmnts = 0;
				//cout << "recv_counts to 0 process" << endl;
				for (int i = 0; i < proc_num / 2; ++i) {
					if (recv_counts[i] > max_vec_size) max_vec_size = recv_counts[i];
					final_recv_counts[i] = recv_counts[i];
					final_displs[i] = num_of_prev_elmnts;
					num_of_prev_elmnts += final_recv_counts[i];
					//cout << recv_counts[i] << " ";
				}

			}

			//���������� ��� ���������� 0 ��������
			//char **final_recv = allocate_2d_array(proc_num / 2, max_vec_size);
			char *final_recv = new char[proc_num / 2 * max_vec_size];
			MPI_Gatherv(&result1[0], result1_size, MPI_CHAR, final_recv, final_recv_counts, final_displs, MPI_CHAR, 0, row_comm);

			
			if (column_num_rank == 0) {

				cout << "max_vec_size: " << max_vec_size << endl;
				cout << "proc_num " << proc_num << endl;
				for (int i = 0; i < proc_num / 2; ++i) {
				cout << recv_counts[i] << " ";
				}

				longint *final_arr = new longint[proc_num / 2];
				
				//cout << "j" << endl;
				int num_of_prev_elements = 0;
				for (int i = 0; i < proc_num / 2; ++i) {
					vector<char> v;
					for (int j = 0; j < final_recv_counts[i]; ++j) {
						//cout << final_recv[num_of_prev_elements + j] + 0;
						v.push_back(final_recv[num_of_prev_elements + j]);
					}
					num_of_prev_elements += final_recv_counts[i];
					//cout << endl;
					longint number(v);
					final_arr[i] = number;
				}
				
				for (int i = 1; i < proc_num / 2; ++i) {
					final_arr[0] = ss_mult(final_arr[0], final_arr[i]);
				}

				vector<char> final_res = final_arr[0].number;
				cout << endl;
				cout << "result size: " << final_res.size() << endl;

				cout << "parallel mul result: " << endl;
				final_arr[0].print();

				
			}

			

		}
		

	}

	MPI_Finalize();

}