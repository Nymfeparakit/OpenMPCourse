#include <string>
#include <iostream>
#include <random>
#include "mpi.h"

using namespace std;
int main(int argc, char* argv[])
{
	const int polynom_size = 3;
	const int number_of_plnms = 20;
	int proc_num, proc_rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
	MPI_Datatype polynom;
	//полином определяется как последовательность double коэффициентов
	MPI_Type_contiguous(number_of_plnms*polynom_size, MPI_DOUBLE, &polynom);
	MPI_Type_commit(&polynom);

	//TODO возможно ли сделать каждый полином динамическим массивом?
	//double** polynoms = nullptr;
	//double* polynoms[number_of_plnms];
	double polynoms[number_of_plnms][polynom_size * number_of_plnms];
	if (proc_rank == 0) { //только в 0 процессе генерируем все полиномы
		//polynoms = new double*[number_of_plnms];
		/*for (int i = 0; i < number_of_plnms; ++i)
		{
			//нужно зарезервировать больше места, так как степени полиномов буду увеличиваться
			polynoms[i] = new double[polynom_size * number_of_plnms];
		}*/
		//Генерируем рандомные коэффициенты
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 5); // [1, 20] диапазон

		//заполняем их случайными значениями
		std::cout << "Polynoms: " << std::endl;
		for (int i = 0; i < number_of_plnms; ++i)
		{
			std::cout << i << ": ";
			//заполняем первые polynom_size коэффициентов числами
			for (int j = 0; j < polynom_size; ++j)
			{
				polynoms[i][j] = dist6(rng);
				std::cout << polynoms[i][j] << " ";//выводим при необходимости
			}
			//Остальные заполняем нулями
			for (int j = polynom_size; j < polynom_size * number_of_plnms; ++j) {
				polynoms[i][j] = 0;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	int* send_counts = nullptr;//здесь записывается число элементов, кот отправляется каждому процессу
	int* displs = nullptr;//смещения 
	int default_chunk_size = number_of_plnms / proc_num;//количество полиномов, которое получает каждый процесс
	//число оставшихся полиномов, кот нужно будет докинуть последним процессам
	int nmbr_of_remaining_plnms = number_of_plnms % proc_num;
	//число первых процессов, которым будет прислано default_chunk_size полиномов
	int nmbr_of_frst_procs = proc_num - nmbr_of_remaining_plnms;
	//std::cout << "proc_num: " << proc_num << std::endl;
	//std::cout << "default_chunk_size: " << default_chunk_size << std::endl;
	int recv_count;//число элементов, которое получит процесс
	if (proc_rank == 0) {//процесс с рангом 0 отправляет другим процессам полиномы
						 // которые нужно перемножить
		//выделяем память
		displs = new int[proc_num];
		send_counts = new int[proc_num];

		//определяем, какое число элементов должно быть отправлено
		//каждому из процессов
		//std::cout << "send_counts: " << std::endl;
		for (int i = 0; i < nmbr_of_frst_procs; ++i) {
			send_counts[i] = default_chunk_size;
			displs[i] = default_chunk_size * i;
			//std:cout << std::to_string(send_counts[i]) << " ";
		}
		//Остальным процессам отправим на 1 элемент больше
		for (int i = nmbr_of_frst_procs; i < proc_num; ++i) {
			send_counts[i] = default_chunk_size + 1;
			displs[i] = (default_chunk_size + 1) * (i - nmbr_of_frst_procs)
				+ nmbr_of_frst_procs * default_chunk_size;
			//std::cout << std::to_string(send_counts[i]) << " ";
		}
		//std::cout << std::endl;

		//Выводим смещения для проверки
		/*std::cout << "displs: " << std::endl;
		for (int i = 0; i < proc_num; ++i) {
		std::cout << std::to_string(displs[i]) << " ";
		}*/
		//}		
	}

	//определяем для каждого процесса отдельно, сколько элементов он получит
	if (proc_rank < nmbr_of_frst_procs) {
		recv_count = default_chunk_size;
	}
	else {
		recv_count = default_chunk_size + 1;
	}

	//TODO заменить на статический
	//double** recv_polynoms = new double*[number_of_plnms];
	//double* recv_polynoms[number_of_plnms];
	double recv_polynoms[number_of_plnms][polynom_size * number_of_plnms];
	/*for (int i = 0; i < number_of_plnms; ++i)
	{
		//нужно зарезервировать больше места, так как степени полиномов буду увеличиваться
		recv_polynoms[i] = new double[polynom_size * number_of_plnms];
	}*/	//int MPI_Scatterv(const void* sendbuf, const int sendcounts[],
		//const int displs[], MPI_Datatype sendtype, void* recvbuf,
		//int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
	//TODO делать этот этап, если число полиномов >=...
	MPI_Scatterv(polynoms, send_counts, displs, polynom, recv_polynoms, recv_count, polynom, 0,
		MPI_COMM_WORLD);

	//if (proc_rank == 2) {
	/*for (int i = 0; i < recv_count; ++i) {
		std::cout << std::to_string(i) << ": ";
		for (int j = 0; j < polynom_size; ++j) {
			std::cout << recv_polynoms[i][j] << " ";
		}
		std::cout << std::endl;

	}*/

	//копия 1го полинома для перемножения
	double *first_polynom_copy = new double[polynom_size * number_of_plnms]();

	//TODO каждый получил по полиномам, теперь их нужно перемножить
	//умножаем все полиномы на 1ый
	int first_polynom_size = polynom_size;//размер посл полинома будет постоянно увеличиваться
	for (int i = 1; i < recv_count; ++i) {
		//делаем копию 1го полинома
		//std::cout << "first poly copy: ";
		for (int j = 0; j < first_polynom_size; ++j) {
			first_polynom_copy[j] = recv_polynoms[0][j];
			recv_polynoms[0][j] = 0;
			//std::cout << std::to_string(first_polynom_copy[j]) << " ";
		}
		for (int j = 0; j < first_polynom_size; ++j) {
			for (int k = 0; k < polynom_size; ++k) {
				recv_polynoms[0][j + k] += first_polynom_copy[j] * recv_polynoms[i][k];
			}
		}
		first_polynom_size += polynom_size - 1;//степень полинома увеличивается после перемножения
	}

	delete[] first_polynom_copy;//очищаем копию

	//выводим итоговый полином
	/*std::cout << "first poly: ";
	for (int i = 0; i < first_polynom_size; ++i) {
		cout << recv_polynoms[0][i] << " ";
	}
	cout << std::endl;
	*/
	//}

	//Каждый из процессов провел первый этап произведения
	//Собираем полученные полиномы в массив полиномов
	//int MPI_Gather(const void* sendbuf, int sendcount, MPI_Datatype sendtype,
		//void* recvbuf, int recvcount, MPI_Datatype recvtype, int root,
		//MPI_Comm comm)
	//double new_polynoms[number_of_plnms][polynom_size * number_of_plnms];
	MPI_Gather(recv_polynoms[0], 1, polynom, polynoms, 1, polynom, 0, MPI_COMM_WORLD);
	//теперь число полиномов < proc_num * 2
	//каждому отправляем по 2 полинома
	//рассчитываем для каждого смещение и число отправляемых ему полиномов
	//все это делаем в общем цикле шагов
	
	if (proc_rank == 0) {

		//выводим полученные полиномы
		for (int i = 0; i < proc_num; ++i) {
			std::cout << std::to_string(i) << ": ";
			for (int j = 0; j < polynom_size * number_of_plnms; ++j) {
				std::cout << polynoms[i][j] << " ";
			}
			std::cout << std::endl;
		}

		//Очищаем память
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

	MPI_Type_free(&polynom);
	MPI_Finalize();
}


