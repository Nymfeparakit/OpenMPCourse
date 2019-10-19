#include <string>
#include <iostream>
#include <random>
#include "mpi.h"

using namespace std;
int main(int argc, char* argv[])
{
	const int polynom_size = 2;
	const int number_of_plnms = 14;
	int proc_num, proc_rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
	MPI_Datatype polynom;
	//������� ������������ ��� ������������������ double �������������
	MPI_Type_contiguous(number_of_plnms * polynom_size, MPI_DOUBLE, &polynom);
	MPI_Type_commit(&polynom);

	//TODO �������� �� ������� ������ ������� ������������ ��������?
	//double** polynoms = nullptr;
	//double* polynoms[number_of_plnms];
	double polynoms[number_of_plnms][polynom_size * number_of_plnms];
	if (proc_rank == 0) { //������ � 0 �������� ���������� ��� ��������
		//polynoms = new double*[number_of_plnms];
		/*for (int i = 0; i < number_of_plnms; ++i)
		{
			//����� ��������������� ������ �����, ��� ��� ������� ��������� ���� �������������
			polynoms[i] = new double[polynom_size * number_of_plnms];
		}*/
		//���������� ��������� ������������
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5); // [1, 20] ��������

		//��������� �� ���������� ����������
		std::cout << "Polynoms: " << std::endl;
		for (int i = 0; i < number_of_plnms; ++i)
		{
			//std::cout << i << ": ";
			//��������� ������ polynom_size ������������� �������
			for (int j = 0; j < polynom_size; ++j)
			{
				//polynoms[i][j] = dist6(rng);
				polynoms[i][j] = 1;
				//std::cout << polynoms[i][j] << " ";//������� ��� �������������
			}
			//��������� ��������� ������
			for (int j = polynom_size; j < polynom_size * number_of_plnms; ++j) {
				polynoms[i][j] = 0;
			}
			//std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	//}
	if (number_of_plnms >= proc_num) {



		int* send_counts = nullptr;//����� ������������ ����� ���������, ��� ������������ ������� ��������
		int* displs = nullptr;//�������� 
		int default_chunk_size = number_of_plnms / proc_num;//���������� ���������, ������� �������� ������ �������
		//����� ���������� ���������, ��� ����� ����� �������� ��������� ���������
		int nmbr_of_remaining_plnms = number_of_plnms % proc_num;
		//����� ������ ���������, ������� ����� �������� default_chunk_size ���������
		int nmbr_of_frst_procs = proc_num - nmbr_of_remaining_plnms;
		//std::cout << "proc_num: " << proc_num << std::endl;
		//std::cout << "default_chunk_size: " << default_chunk_size << std::endl;
		int recv_count;//����� ���������, ������� ������� �������
		if (proc_rank == 0) {//������� � ������ 0 ���������� ������ ��������� ��������
							 // ������� ����� �����������
			//�������� ������
			displs = new int[proc_num];
			send_counts = new int[proc_num];

			//����������, ����� ����� ��������� ������ ���� ����������
			//������� �� ���������
			//std::cout << "send_counts: " << std::endl;
			for (int i = 0; i < nmbr_of_frst_procs; ++i) {
				send_counts[i] = default_chunk_size;
				displs[i] = default_chunk_size * i;
				//std:cout << std::to_string(send_counts[i]) << " ";
			}
			//��������� ��������� �������� �� 1 ������� ������
			for (int i = nmbr_of_frst_procs; i < proc_num; ++i) {
				send_counts[i] = default_chunk_size + 1;
				displs[i] = (default_chunk_size + 1) * (i - nmbr_of_frst_procs)
					+ nmbr_of_frst_procs * default_chunk_size;
				//std::cout << std::to_string(send_counts[i]) << " ";
			}
			//std::cout << std::endl;

			//������� �������� ��� ��������
			/*std::cout << "displs: " << std::endl;
			for (int i = 0; i < proc_num; ++i) {
			std::cout << std::to_string(displs[i]) << " ";
			}*/
			//}		
		}

		//���������� ��� ������� �������� ��������, ������� ��������� �� �������
		if (proc_rank < nmbr_of_frst_procs) {
			recv_count = default_chunk_size;
		}
		else {
			recv_count = default_chunk_size + 1;
		}

		//TODO �������� �� �����������
		//double** recv_polynoms = new double*[number_of_plnms];
		//double* recv_polynoms[number_of_plnms];
		double recv_polynoms[number_of_plnms][polynom_size * number_of_plnms];
		/*for (int i = 0; i < number_of_plnms; ++i)
		{
			//����� ��������������� ������ �����, ��� ��� ������� ��������� ���� �������������
			recv_polynoms[i] = new double[polynom_size * number_of_plnms];
		}*/

		//int MPI_Scatterv(const void* sendbuf, const int sendcounts[],
			//const int displs[], MPI_Datatype sendtype, void* recvbuf,
			//int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

		//TODO ������ ���� ����, ���� ����� ��������� >=...
		MPI_Scatterv(polynoms, send_counts, displs, polynom, recv_polynoms, recv_count, polynom, 0,
			MPI_COMM_WORLD);

		//if (proc_rank == 2) {

		//����� 1�� �������� ��� ������������
		double* first_polynom_copy = new double[polynom_size * number_of_plnms]();

		//TODO ������ ������� �� ���������, ������ �� ����� �����������
		//�������� ��� �������� �� 1��
		int first_polynom_size = polynom_size;//������ ���� �������� ����� ��������� �������������
		for (int i = 1; i < recv_count; ++i) {
			//������ ����� 1�� ��������
			//std::cout << "first poly copy: ";
			for (int j = 0; j < first_polynom_size; ++j) {
				first_polynom_copy[j] = recv_polynoms[0][j];
				recv_polynoms[0][j] = 0;
				//std::cout << std::to_string(first_polynom_copy[j]) << " ";
			}
			for (int j = 0; j < polynom_size * number_of_plnms; ++j) {
				for (int k = 0; k < polynom_size * number_of_plnms; ++k) {
					if (j + k < polynom_size * number_of_plnms) {
						recv_polynoms[0][j + k] += first_polynom_copy[j] * recv_polynoms[i][k];
					}
				}
			}
			first_polynom_size += polynom_size - 1;//������� �������� ������������� ����� ������������
		}

		delete[] first_polynom_copy;//������� �����

		std::cout << std::to_string(proc_rank) << ": ";
		for (int j = 0; j < first_polynom_size; ++j) {
			std::cout << recv_polynoms[0][j] << " ";
		}
		std::cout << std::endl;		

		//�������� ��� �������� 
		MPI_Gather(recv_polynoms, 1, polynom, polynoms, 1, polynom, 0, MPI_COMM_WORLD);
	
		//����� ��������� ����� ����� ���������
		//������������ �� 3 ��������
		int zero_proc_poly_num = proc_num / 3;//������� ������� �������
		int first_proc_poly_num = (proc_num - zero_proc_poly_num) / 2;//������ ������� �������
		int second_proc_poly_num = proc_num - zero_proc_poly_num - first_proc_poly_num;//������� ������� �������

		if (proc_rank == 0) {
			MPI_Send(polynoms[zero_proc_poly_num], first_proc_poly_num, polynom, 1, 0, MPI_COMM_WORLD);
			MPI_Send(polynoms[zero_proc_poly_num + first_proc_poly_num], second_proc_poly_num, polynom, 2, 0, MPI_COMM_WORLD);
		}
		
		recv_count = zero_proc_poly_num;
		if (proc_rank == 1) {
			recv_count = first_proc_poly_num;
		}
		else if (proc_rank == 2) {
			recv_count = second_proc_poly_num;
		}
		
		if (proc_rank == 1 || proc_rank == 2) {
			MPI_Recv(recv_polynoms, recv_count, polynom, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}

		if (proc_rank <= 2) {
			//����� 1�� �������� ��� ������������
			first_polynom_copy = new double[polynom_size * number_of_plnms]();

			for (int i = 1; i < recv_count; ++i) {
				//������ ����� 1�� ��������
				//std::cout << "first poly copy: ";
				for (int j = 0; j < polynom_size * number_of_plnms; ++j) {
					if (proc_rank == 0) {
						first_polynom_copy[j] = polynoms[0][j];
						polynoms[0][j] = 0;
					}
					else {
						first_polynom_copy[j] = recv_polynoms[0][j];
						recv_polynoms[0][j] = 0;
					}

					//std::cout << std::to_string(first_polynom_copy[j]) << " ";
				}
				for (int j = 0; j < polynom_size * number_of_plnms; ++j) {
					for (int k = 0; k < polynom_size * number_of_plnms; ++k) {
						if (j + k < polynom_size * number_of_plnms) {
							if (proc_rank == 0) {
								polynoms[0][j + k] += first_polynom_copy[j] * polynoms[i][k];
							}
							else {
								recv_polynoms[0][j + k] += first_polynom_copy[j] * recv_polynoms[i][k];
							}
						}
					}
				}
			}

			delete[] first_polynom_copy;//������� �����
		}

			if (proc_rank == 1 || proc_rank == 2) {
				MPI_Send(recv_polynoms[0], 1, polynom, 0, 0, MPI_COMM_WORLD);
			}
			else if (proc_rank == 0) {
				MPI_Recv(polynoms[1], 1, polynom, 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);	
				std::cout << std::endl;
				MPI_Recv(polynoms[2], 1, polynom, 2, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				//����� 1�� �������� ��� ������������
				double* first_polynom_copy = new double[polynom_size * number_of_plnms]();

				for (int i = 1; i < 3; ++i) {
					//������ ����� 1�� ��������
					//std::cout << "first poly copy: ";
					for (int j = 0; j < polynom_size * number_of_plnms; ++j) {
						first_polynom_copy[j] = polynoms[0][j];
						polynoms[0][j] = 0;
						//std::cout << std::to_string(first_polynom_copy[j]) << " ";
					}
					for (int j = 0; j < polynom_size * number_of_plnms; ++j) {
						for (int k = 0; k < polynom_size * number_of_plnms; ++k) {
							if (j + k < polynom_size * number_of_plnms) {
								polynoms[0][j + k] += first_polynom_copy[j] * polynoms[i][k];
							}
						}
					}
				}

			}


		if (proc_rank == 0) {

			//������� ���������� ��������
			for (int j = 0; j < polynom_size * number_of_plnms; ++j) {
				std::cout << polynoms[0][j] << " ";
			}

			//������� ������
			/*for (int i = 0; i < number_of_plnms; ++i)
			{
				delete[] polynoms[i];
			}*/
			//delete[] polynoms;
			delete[] send_counts;
			delete[] displs;
		}

		/*for (int i = 0; i < number_of_plnms; ++i)
		{
			delete[] recv_polynoms[i];
		}*/
		//delete[] recv_polynoms;
	}
	MPI_Type_free(&polynom);
	MPI_Finalize();
}


