#include <mpi.h>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    int n = 1000000000;
	int rank, size;	
	MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int result;
    int *a, *b;

    if (rank == 0) {
    	a = new int[n];
    	b = new int[n];
        fill(a, a + n, 1);
        fill(b, b + n, 1);
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    int *vec_a = new int[n/size]; 
    int *vec_b = new int[n/size];

	MPI_Scatter(a, n/size, MPI_INT, vec_a, n/size, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(b, n/size, MPI_INT, vec_b, n/size, MPI_INT, 0, MPI_COMM_WORLD);

    int sum = 0;
	for(int i = 0; i < n/size; ++i){
		sum += vec_a[i] * vec_b[i];
	}

	MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    delete[] vec_a;
    delete[] vec_b;
    if (rank == 0) {
        delete[] a;
        delete[] b;
        cout << "Result: " << result << endl;
    }

    MPI_Finalize();
	return 0;
}