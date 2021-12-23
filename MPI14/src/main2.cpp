#include <stdio.h>
#include "mpi.h"

using namespace std;

void myMax(void *a, void *b, int *l, MPI_Datatype *type) {
    if (b < a) {
        b = a;
    }
}

int main(int argc, char **argv)
{
	int rank, size, i;
	int result = -1;
	MPI_Init(&argc, &argv);
	MPI_Op op;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Op_create(&myMax, 1, &op);
	MPI_Reduce(&rank, &result, 1, MPI_INT, op , 0, MPI_COMM_WORLD);
	MPI_Op_free(&op);
	if (rank == 0) {
		cout << "Max value by my function: " << result << endl;
	}
	MPI_Reduce(&rank, &result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (rank == 0) {
		cout << "Max value by MPI_MAX function: " << result << endl;
	}
	MPI_Finalize();
    return 0;
}