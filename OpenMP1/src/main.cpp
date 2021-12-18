#include <iostream>
#include <omp.h>

using namespace std;

double max(int A[], int j, int threadNumber)
{
    double t1 = omp_get_wtime();
    int maxValue = A[0];

    #pragma omp parallel for reduction(max:maxValue) num_threads(threadNumber)
    for (int k = 0; k < j; ++k) {
        if (maxValue < A[k]) {
            maxValue = A[k];
        }
    }

    if (j == 10) {
        cout << "Max: " << maxValue << endl;
    }

    return omp_get_wtime() - t1;
}

int main(int argc, char* argv[])
{
    int test[10] = {1, 2, 3, 23, -5, 6, 7, 1, -93, 10};
    cout << "Started array: [1, 2, 3, 23, -5, 6, 7, 1, -93, 10]" << endl;
    cout << max(test, 10, 12) << endl;

    int N;
    N = atoi(argv[1]);

    for (int i = 1; i < 11; ++i) {
        int* vec = new int[N];
        for (int i = 0; i < N; ++i) {
            vec[i] = rand();
        }

        double time = max(vec, N, i);
        cout << "Thread: " << i << ". Time: " << time << endl << endl;
        delete[] vec;
    }

    return 0;
}