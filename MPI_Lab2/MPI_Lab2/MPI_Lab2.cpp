
#include "mpi.h"
#include <stdio.h>
#include <ctime>

void Count(int* invec, int* inoutvec, int* len, MPI_Datatype* datatype);

int value = 0;
bool done = false;

int main(int argc, char* argv[])
{
	int ProcNum, ProcRank;
	srand(time(NULL));
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Op myOp;
	MPI_Op_create((MPI_User_function*)Count, true, &myOp);
	int sendValue = 2;
	int recvValue = 0;
	if (!done) //если не был поднят флаг
	{ 
		printf("\n Hello from process %3d", ProcRank);
		MPI_Reduce(&sendValue, void* recvbuf, int count, MPI_Datatype type,
			MPI_Op op, int root, MPI_Comm comm);
	}
	
	MPI_Finalize();
	return 0;

}

void Count(int* invec, int* inoutvec, int* len, MPI_Datatype* datatype)
{
	//параметр len не нужен, так как каждый процесс будет передавать одно значение
	if (*invec == -1 || *inoutvec == -1)
	{
		printf("Terminating processes");
		done = true;
	}
	++value;//просто увеличиваем значение счетчика
	printf("Value: %d", value);//и выводим сообщение об этом
}