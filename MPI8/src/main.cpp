#include <iostream>
#include <mpi.h>
using namespace std;

int const N = 10;

int main(int argc, char **argv)
{
	int rank, size, ibuf;
	MPI_Status status;
	float rbuf;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	double resultTime;
    
    if (rank == 0 || rank == 1) {
        for (int i = 1; i <= 10000000; i *= 10) {
            int *a = new int[i];
            for (int k = 0; k < i; ++k) {
                a[k] = rand();
            }

            if (rank == 0) {
                resultTime = 0.0;
            }

            for (int j = 0; j < N; ++j) {
                if (rank == 0) {
                    double start_time = MPI_Wtime();
                    MPI_Send(a, i, MPI_INT, 1, 0, MPI_COMM_WORLD);
                    MPI_Recv(a, i, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
                    double end_time = MPI_Wtime();
                    resultTime += end_time - start_time;
                }
                if (rank == 1) {
                    MPI_Recv(a, i, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
                    MPI_Send(a, i, MPI_INT, 0, 0, MPI_COMM_WORLD);
                }
            }

            delete[] a;
            if (rank == 0) {
                cout << "Messages length: " << 2 * N * i * sizeof(int) << " bytes. Bandwidth: "
                     << ((2 * N * i * sizeof(int))/(1024.0*1024.0))/resultTime << " Mb/s" << endl;
            }
        }

        int *a = new int[0];
        if (rank == 0) {
            resultTime = 0.0;
        }
        for (int j = 0; j < N; ++j) {
            if (rank == 0) {
                double start_time = MPI_Wtime();
                MPI_Send(a, 0, MPI_INT, 1, 0, MPI_COMM_WORLD);
                MPI_Recv(a, 0, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
                double end_time = MPI_Wtime();
                resultTime += end_time - start_time;
            }
            if (rank == 1) {
                MPI_Recv(a, 0, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
                MPI_Send(a, 0, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }
        }
         delete[] a;
            if (rank == 0) {
                cout << "Latency: " << resultTime/(2 * N) << endl;
            }
    }
	MPI_Finalize();
    return 0;
}