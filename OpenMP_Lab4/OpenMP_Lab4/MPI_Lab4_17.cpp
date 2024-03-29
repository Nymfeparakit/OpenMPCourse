#include <string>
#include <iostream>
#include <random>
#include "mpi.h"

using namespace std;
int main(int argc, char* argv[])
{
	const int polynom_size = 2;
	const int number_of_plnms = 7;
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
			//std::cout << i << ": ";
			//заполняем первые polynom_size коэффициентов числами
			for (int j = 0; j < polynom_size; ++j)
			{
				//polynoms[i][j] = dist6(rng);
				polynoms[i][j] = 1;
				//std::cout << polynoms[i][j] << " ";//выводим при необходимости
			}
			//Остальные заполняем нулями
			for (int j = polynom_size; j < polynom_size * number_of_plnms; ++j) {
				polynoms[i][j] = 0;
			}
			//std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	if (number_of_plnms < 8) {
		double recv_polynoms[number_of_plnms][polynom_size * number_of_plnms];
		int number_of_plnms_to_send = number_of_plnms / 2;
		int number_of_plnms_to_mul = 0;
		if (proc_rank == 0) {
			MPI_Send(polynoms, number_of_plnms_to_send, polynom, 1, 0, MPI_COMM_WORLD);
			number_of_plnms_to_mul = number_of_plnms - number_of_plnms_to_send;
		}
		else if (proc_rank == 1) {
			MPI_Recv(recv_polynoms, number_of_plnms_to_send, polynom, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			number_of_plnms_to_mul = number_of_plnms_to_send;
		}
		double *first_polynom_copy = new double[polynom_size * number_of_plnms]();
		for (int i = 1; i < number_of_plnms_to_mul; ++i) {
			//делаем копию 1го полинома
			//std::cout << "first poly copy: ";
			for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
				if (proc_rank == 0) {
					first_polynom_copy[j] = polynoms[0][j];
					polynoms[0][j] = 0;
				}
				else if (proc_rank == 1) {
					first_polynom_copy[j] = recv_polynoms[0][j];
					recv_polynoms[0][j] = 0;
				}
				//std::cout << std::to_string(first_polynom_copy[j]) << " ";
			}
			for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
				for (int k = 0; k < polynom_size*number_of_plnms; ++k) {
					if (j + k < polynom_size*number_of_plnms) {
						if (proc_rank == 0) {
							polynoms[0][j + k] += first_polynom_copy[j] * polynoms[i][k];
						}
						else if (proc_rank == 1) {
							recv_polynoms[0][j + k] += first_polynom_copy[j] * recv_polynoms[i][k];
						}
					}
				}
			}
		}
		if (proc_rank == 1) {
			MPI_Send(recv_polynoms[0], 1, polynom, 0, 0, MPI_COMM_WORLD);
		}
		else if (proc_rank == 0) {
			MPI_Recv(recv_polynoms[0], 1, polynom, 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			std::cout << "number_of_plnms recv < 8: ";
			for (int i = 0; i < polynom_size*number_of_plnms; ++i) {
				std::cout << recv_polynoms[0][i] << " ";
			}
			std::cout << "number_of_plnms snd< 8: ";
			for (int i = 0; i < polynom_size*number_of_plnms; ++i) {
				std::cout << polynoms[0][i] << " ";
			}
			for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
				polynoms[1][j] = 0;
			}
			for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
				for (int k = 0; k < polynom_size*number_of_plnms; ++k) {
					if (j + k < polynom_size*number_of_plnms) {
							polynoms[1][j + k] += polynoms[0][j] * recv_polynoms[0][k];
					}
				}
			}
			std::cout << "number_of_plnms < 8: ";
			for (int i = 0; i < polynom_size*number_of_plnms; ++i) {
				std::cout << polynoms[1][i] << " ";
			}
			std::cout << std::endl;
		}
		delete[] first_polynom_copy;

	}
	else {



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
	}*/

	//int MPI_Scatterv(const void* sendbuf, const int sendcounts[],
		//const int displs[], MPI_Datatype sendtype, void* recvbuf,
		//int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

	//TODO делать этот этап, если число полиномов >=...
	MPI_Scatterv(polynoms, send_counts, displs, polynom, recv_polynoms, recv_count, polynom, 0,
		MPI_COMM_WORLD);

	//if (proc_rank == 2) {

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
		for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
			for (int k = 0; k < polynom_size*number_of_plnms; ++k) {
				if (j + k < polynom_size*number_of_plnms) {
					recv_polynoms[0][j + k] += first_polynom_copy[j] * recv_polynoms[i][k];
				}
			}
		}
		first_polynom_size += polynom_size - 1;//степень полинома увеличивается после перемножения
	}

	delete[] first_polynom_copy;//очищаем копию

	std::cout << std::to_string(proc_rank) << ": ";
	for (int j = 0; j < first_polynom_size; ++j) {
		std::cout << recv_polynoms[0][j] << " ";
	}
	std::cout << std::endl;


	//Каждый из процессов провел первый этап произведения
	//Собираем полученные полиномы в массив полиномов
	//double new_polynoms[number_of_plnms][polynom_size * number_of_plnms];
	//MPI_Gather(recv_polynoms[0], 1, polynom, polynoms, 1, polynom, 0, MPI_COMM_WORLD);

	//Общее число полиномов должно быть >= 8
	//Делаем 3 шага
	if (proc_rank == 0) {
		std::cout << "first_poly_size: " << first_polynom_size << std::endl;
	}
	if (proc_rank % 2 != 0) {
		//Отправляем предыдущему процессу
		MPI_Send(recv_polynoms[0], 1, polynom, proc_rank - 1, 0, MPI_COMM_WORLD);
	}
	else { //получаем еще полином и перемножаем 2
		//записываем все в 2ой
		MPI_Recv(recv_polynoms[1], 1, polynom, proc_rank + 1, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for (int j = 0; j < number_of_plnms*first_polynom_size; ++j) {
			recv_polynoms[2][j] = 0;
		}
		for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
			for (int k = 0; k < polynom_size*number_of_plnms; ++k) {
				if (j + k < polynom_size*number_of_plnms) {
					recv_polynoms[2][j + k] += recv_polynoms[0][j] * recv_polynoms[1][k];
				}
			}
		}
		first_polynom_size += first_polynom_size - 1;//степень полинома увеличивается после перемножения
		if (proc_rank == 0) {
			std::cout << "1_step " << std::to_string(proc_rank) << ": ";
			for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
				std::cout << recv_polynoms[2][j] << " ";
			}
			std::cout << std::endl;
		}

	}

	//2 шаг
	if (proc_rank == 0) {
		std::cout << "first_poly_size: " << first_polynom_size << std::endl;
	}
	if (proc_rank == 2 || proc_rank == 6) {
		MPI_Send(recv_polynoms[2], 1, polynom, proc_rank - 2, 0, MPI_COMM_WORLD);
	}
	else if (proc_rank == 0 || proc_rank == 4) { //получаем еще полином и перемножаем 2
		   //записываем все в 3ий
		MPI_Recv(recv_polynoms[1], 1, polynom, proc_rank + 2, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if (proc_rank == 0) {
			std::cout << "2_step_first_poly " << std::to_string(proc_rank) << ": ";
			for (int j = 0; j < 2 * first_polynom_size; ++j) {
				std::cout << recv_polynoms[1][j] << " ";
			}
		}
		if (proc_rank == 0) {
			std::cout << "2_step_second_poly " << std::to_string(proc_rank) << ": ";
			for (int j = 0; j < 2 * first_polynom_size; ++j) {
				std::cout << recv_polynoms[2][j] << " ";
			}
		}
		for (int j = 0; j < 2 * number_of_plnms*polynom_size; ++j) {
			recv_polynoms[3][j] = 0;
		}
		for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
			for (int k = 0; k < polynom_size*number_of_plnms; ++k) {
				if (j + k < polynom_size*number_of_plnms) {
					recv_polynoms[3][j + k] += recv_polynoms[1][j] * recv_polynoms[2][k];
				}
			}
		}
		first_polynom_size += first_polynom_size - 1;//степень полинома увеличивается после перемножения
		if (proc_rank == 0) {
			std::cout << "2_step " << std::to_string(proc_rank) << ": ";
			for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
				std::cout << recv_polynoms[3][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	//последний шаг
	if (proc_rank == 0) {
		std::cout << "first_poly_size: " << first_polynom_size << std::endl;
	}
	if (proc_rank == 4) {
		MPI_Send(recv_polynoms[3], 1, polynom, 0, 0, MPI_COMM_WORLD);
	}
	else if (proc_rank == 0) { //получаем еще полином и перемножаем 2
												 //записываем все в 3ий
		MPI_Recv(recv_polynoms[2], 1, polynom, 4, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
			recv_polynoms[4][j] = 0;
		}
		for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
			for (int k = 0; k < polynom_size*number_of_plnms; ++k) {
				if (j + k < polynom_size*number_of_plnms) {
					recv_polynoms[4][j + k] += recv_polynoms[2][j] * recv_polynoms[3][k];
				}
			}
		}
		first_polynom_size += first_polynom_size - 1;//степень полинома увеличивается после перемножения
		if (proc_rank == 0) {
			std::cout << "3_step " << std::to_string(proc_rank) << ": ";
			for (int j = 0; j < polynom_size*number_of_plnms; ++j) {
				std::cout << recv_polynoms[4][j] << " ";
			}
			std::cout << std::endl;
		}
	}

		//теперь число полиномов < proc_num * 2
		//все это делаем в общем цикле шагов
		//опеределяем число оставшихся полиномов

		int number_of_remaining_plnms = number_of_plnms >= 16 ? 8 : number_of_plnms;
		int number_of_working_procs = number_of_remaining_plnms % 2 == 0 ? //число процессов, которые 
			number_of_remaining_plnms / 2 :								//будут включены в работу
			(number_of_remaining_plnms - 1) / 2;
		/*
		std::cout << "number_of_remaining_plnms: " << number_of_remaining_plnms << std::endl;
		std::cout << "number_of_working_procs: " << number_of_working_procs << std::endl;
		*/

		if (proc_rank == 0) {

			//выводим полученные полиномы
			for (int j = 0; j < polynom_size * number_of_plnms; ++j) {
				std::cout << recv_polynoms[4][j] << " ";
			}
			std::cout << std::endl;
		}


		//while (number_of_remaining_plnms != 2) {
			//каждому отправляем по 2 полинома
			//рассчитываем для каждого смещение и число отправляемых ему полиномов
		/*for (int i = 0; i < number_of_working_procs; ++i) {
			send_counts[i] = 2;
			displs[i] = 2 * i;
			//std:cout << std::to_string(send_counts[i]) << " ";
		}//остальным ничего не отправляем
		for (int i = number_of_working_procs; i < proc_num; ++i) {
			send_counts[i] = 0;
			displs[i] = 2 * i;
		}

		//}
	}*/
		if (proc_rank < number_of_working_procs) {
			recv_count = 2;//каждый получает по 2 полинома
		}
		else {
			recv_count = 0;
		}
		//MPI_Scatterv(polynoms, send_counts, displs, polynom, recv_polynoms, recv_count, polynom, 0,
			//MPI_COMM_WORLD);

		if (proc_rank == 0) {


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
	}
		MPI_Type_free(&polynom);
		MPI_Finalize();
	}


