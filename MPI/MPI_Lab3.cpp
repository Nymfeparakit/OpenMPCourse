
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

	//---1 �������
	while (1)
	{
		int randomNumber = rand() % (maxRange - minRange + 1) + minRange;//���������� ��������� ����� � ��������� [-1,10]
		printf("Process N%d number: %d\n", ProcRank, randomNumber);
		//������� � ������ 0 �������� �� ������� �� ����� � ������� ����������� 
		MPI_Reduce(&randomNumber, &minNumber, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
		MPI_Bcast(&minNumber, 1, MPI_INT, 0, MPI_COMM_WORLD);//���� �� ������� ��������� ���� ���������
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

	//2 �������

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
		randomNumber = rand() % (maxRange - minRange + 1) + minRange;//���������� ��������� ����� � ��������� [-1,10]
		//printf("Process N%d number: %d\n", ProcRank, randomNumber);
		//MPI_Barrier(MPI_COMM_WORLD);
		//������� � ������ 0 ������ ��� �������
		if (ProcRank == 0)
		{
			if (minNumber != -1 && !firstIteration)//���� -1 ��� �� ������
			{
				counter += ProcNum;//������ ����������� �������
				printf("Counter: %d\n", counter);
			}
			else if (minNumber == -1)
			{
				for (int i = 1; i < ProcNum; ++i)//������������� ������ �� ���������
				{
					MPI_Ssend(&minNumber, 1, MPI_INT, i, 0, MPI_COMM_WORLD);//���������� ���� -1
					//��� ���� �������, ����� ������� ������ �������� ���������
				}
				break;//��������� ������
			}
			firstIteration = false;
		}
		else//��� ��������� � ������ ������
		{
			MPI_Test(&request, &flag, &status);//��������� �� ������ �� ���-����
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

