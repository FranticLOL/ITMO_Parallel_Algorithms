#include "mpi.h"

using namespace std;

int main(int argc, char **argv)
{
	int rank, size, rank1;
	MPI_Init(&argc, &argv);
	MPI_Comm commRevs;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		cout << "Rank%2:" << endl;
	}
	// Split processes in two groups
	MPI_Comm_split(MPI_COMM_WORLD, rank % 2, size - rank, &commRevs);
	// Get new rank
	MPI_Comm_rank(commRevs, &rank1);
	cout << "Rank: " << rank << ". Rank1: " << rank1 << endl;
	MPI_Barrier(commRevs);
	MPI_Comm_free(&commRevs);

	// Sync processes
	MPI_Barrier(MPI_COMM_WORLD);

	if (rank == 0) {
		cout << "Rank%3:" << endl;
	}
	// Split processes in three groups
	MPI_Comm_split(MPI_COMM_WORLD, rank % 3, size - rank, &commRevs);
	// Get new rank
	MPI_Comm_rank(commRevs, &rank1);
	cout << "Rank: " << rank << ". Rank1: " << rank1 << endl;
	MPI_Comm_free(&commRevs);
	MPI_Finalize();
    return 0;
}