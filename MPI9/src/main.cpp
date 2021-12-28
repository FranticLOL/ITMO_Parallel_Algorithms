#include <mpi.h>
using namespace std;

int main(int argc, char *argv[])
{
	int rank, size, tempSum, result;
    int n = 1000000;
    
    double start_time;	
	MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    int a[n];
    if (rank == 0) {
    	for (int i = 0; i < n; ++i) {
            a[i] = 1;
        }
    }
	
	int l = n / size;
	
	int sub_a[l];
	
	MPI_Scatter(&a, l, MPI_INT, &sub_a, l, MPI_INT, 0, MPI_COMM_WORLD);
	
	int sum = 0;
	for (int i = 0; i < l; ++i){
         sum += sub_a[i];
    }
	
	if (rank == 0) {
        start_time = MPI_Wtime();
    }
		
	for (int i = 2; i <= size; i *= 2)
	{
		if (rank % i == 0) {
			if (rank + i / 2 < size) {
				MPI_Recv(&tempSum, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				sum += tempSum;
			}
		}
		else {
			MPI_Send(&sum, 1, MPI_INT, rank - (rank % i), 0, MPI_COMM_WORLD);
			break;
		}
	}
	
    if (rank == 0) {
        double resultTime = MPI_Wtime() - start_time;
        cout << "Doubling scheme sum: " << sum << endl <<
        "Time for doubling model: " << resultTime << endl; 
    }

    if (rank == 0) {
        for (int i = 0; i < n; ++i) {
            a[i] = 1;
        }
    }

    MPI_Scatter(&a, l, MPI_INT, &sub_a, l, MPI_INT, 0, MPI_COMM_WORLD);
    
    sum = 0;
    for (int i = 0; i < l; ++i) {
        sum += sub_a[i];
    }

    if (rank == 0) {
        start_time = MPI_Wtime();
    }

    MPI_Reduce(&sum, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        double resultTime = MPI_Wtime() - start_time;
        cout << endl << endl << "Reduce sum: " << result << endl;
        cout << "Time for reduce function: " << resultTime << endl;
    }


    MPI_Finalize();
    return 0;
}
