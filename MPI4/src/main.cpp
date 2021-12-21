#include <iostream>
#include "mpi.h"

using namespace std;
int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);

	int rank, n, i, message;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int previousMessage = -2;
	bool isOdd = false;
    double startTime = MPI_Wtime();
	if (rank == 0)
	{
		cout << "Hello from process " << rank << "\n";
		for (i = 1; i < n; i++) {
			MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			
            if (message % 2 == 1 && previousMessage % 2 == 1) {
				isOdd = true;
			} 
			
            previousMessage = message;
			cout << "Hello from process " << message << endl;
		}

		if (isOdd) {
			cout << "Sequence has at least two adjacent odd numbers" << endl;
		} else {
			cout << "Sequence does not have at least two adjacent odd numbers" << endl;
		}
	}
	else MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    cout << "Time for processor " << rank << " is " << MPI_Wtime() - startTime << endl;
	MPI_Finalize();
	return 0;
}