
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

void Count(int* invec, int* inoutvec, int* len, MPI_Datatype* datatype);

int value = 0;
bool done = false;

int main(int argc, char* argv[])
{
	int ProcNum, ProcRank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	srand(time(NULL) + ProcRank);//seed generator
	int minRange = -1;
	int maxRange = 20;
	int minNumber = 25;
	int counter = 0;

	int* msgArray = NULL;
	int ifDone = 0;
	if (ProcRank == 0)
	{
		msgArray = new int[ProcNum];
	}
	else
	{
		msgArray = NULL;
	}
	while (1)
	{
		int randomNumber = rand() % (maxRange - minRange + 1) + minRange;//генерируем рандомное число в диапазоне [-1,10]
		printf("Process N%d number: %d\n", ProcRank, randomNumber);
		//процесс с рангом 0 получает от каждого по числу и собирает их в массив
		MPI_Gather(&randomNumber, 1, MPI_INT, msgArray, 1, MPI_INT, 0, MPI_COMM_WORLD);
		//ищет в массиве -1
		if (ProcRank == 0)
		{
			for (int i = 0; i < ProcNum; ++i)
			{
				if (msgArray[i] == -1)
				{
					ifDone = 1;
					break;
				}
			}
		}
		MPI_Bcast(&ifDone, 1, MPI_INT, 0, MPI_COMM_WORLD);//этот же процесс рассылает всем сообщение
		if (ifDone)
		{
			break;
		}
		else if (ProcRank == 0)
		{
			counter += ProcNum;
			printf("Counter: %d\n", counter);
		}
	}
	if (ProcRank == 0)
	{
		delete[] msgArray;
	}
	printf("Process N%d completed\n", ProcRank);

	//---1 вариант
	/*while (1)
	{
		int randomNumber = rand() % (maxRange - minRange + 1) + minRange;//генерируем рандомное число в диапазоне [-1,10]
		printf("Process N%d number: %d\n", ProcRank, randomNumber);
		//процесс с рангом 0 получает от каждого по числу и находит минимальное 
		MPI_Reduce(&randomNumber, &minNumber, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
		MPI_Bcast(&minNumber, 1, MPI_INT, 0, MPI_COMM_WORLD);//этот же процесс рассылает всем сообщение
		if (minNumber == -1)
		{
			break;
		}
		else if (ProcRank == 0)
		{
			counter += ProcNum;
			printf("Counter: %d\n", counter);
		}
	}
	printf("Process N%d completed\n", ProcRank);
	*/

	//2 вариант

	/*MPI_Request request;
	int flag = 0;
	MPI_Status status;
	if (ProcRank != 0)
	{
		MPI_Irecv(&minNumber, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &request);
	}
	int randomNumber;
	bool firstIteration = true;
	while (1)
	{
		randomNumber = rand() % (maxRange - minRange + 1) + minRange;//генерируем рандомное число в диапазоне [-1,10]
		//printf("Process N%d number: %d\n", ProcRank, randomNumber);
		//MPI_Barrier(MPI_COMM_WORLD);
		//процесс с рангом 0 узнает мин элемент
		if (ProcRank == 0)
		{
			if (minNumber != -1 && !firstIteration)//если -1 еще не пришел
			{
				counter += ProcNum;//просто увеличиваем счетчик
				printf("Counter: %d\n", counter);
			}
			else if (minNumber == -1)
			{
				for (int i = 1; i < ProcNum; ++i)//останавливаем каждый из процессов
				{
					MPI_Ssend(&minNumber, 1, MPI_INT, i, 0, MPI_COMM_WORLD);//отправляем всем -1
					//при этом ожидаем, когда процесс начнет получать сообщение
				}
				break;//завершаем работу
			}
			firstIteration = false;
		}
		else//для процессов с другим рангом
		{
			MPI_Test(&request, &flag, &status);//проверяем не пришло ли что-либо
			if (flag)
			{
				break;
			}
		}
		MPI_Reduce(&randomNumber, &minNumber, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
		//MPI_Barrier(MPI_COMM_WORLD);
	}

	printf("Process N%d completed\n", ProcRank);*/
	
	MPI_Finalize();
	return 0;

}

