#include <iostream>
#include <omp.h>

using namespace std;

double matrixMultiplication(int m, int n, int p, int** a, int** b, int** c, int T) 
{
    double t1 = omp_get_wtime();
    int i, j, k;
    #pragma omp parallel num_threads(T) shared(a,b,c) private(i,j,k) 
    {
        #pragma omp for schedule(static)
        for (i = 0; i < m; i = i + 1) {
            for (j = 0; j < n; j = j + 1) {
                c[i][j] = 0;
                for (k = 0; k < p; k = k + 1) {
                    c[i][j] += b[i][k] * a[k][j];
                }
            }
        }
    }

    double runtime = omp_get_wtime() - t1;
    if (m == 5 && n == 5 && p == 5) {
        cout << endl << "A * B:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << c[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return runtime;
}

int main(int argc, char* argv[])
{
    int** A = new int*[5];
    int** B = new int*[5];
    int** C = new int*[5];
    for (int i = 0; i < 5; i++) {
        A[i] = new int[5];
        B[i] = new int[5];
        C[i] = new int[5];
    }
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            B[i][j] = i+j;
            A[i][j] = i+j;
        }
    }

    cout << "A matrix" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "B matrix" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    double time = matrixMultiplication(5, 5, 5, A, B, C, 12);
    

    for (int i = 0; i < 5; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    int M, N, P;
    M = atoi(argv[1]);
    N = atoi(argv[2]);
    P = atoi(argv[3]);

    A = new int* [M];
    B = new int* [M];
    C = new int* [P];

    for (int i = 0; i < M; i++) {
        A[i] = new int[N];
        B[i] = new int[P];
    }

    for (int i = 0; i < M; i++) {
        C[i] = new int[N];
    }

    double oneExTime = 0;
    for (int j = 0; j < 20; j++) {
        oneExTime += matrixMultiplication(M, N, P, A, B, C, 1);
    }

    cout << "Thread: 1" << ". Time: " << oneExTime << ". Efficiency: 1" << endl << endl;

    for (int i = 2; i < 11; i++) {
        double time = 0;
        for (int j = 0; j < 20; j++) {
            time += matrixMultiplication(M, N, P, A, B, C, i);
        }
        cout << "Thread: " << i << ". Time: " << time / 20 << ". Efficiency: " <<
            oneExTime / (time / 20) << endl << endl;
    }

    for (int i = 0; i < N; i++) {
        delete[] A[i];
        delete[] C[i];
    }
    for (int i = 0; i < P; i++) {
        delete[] B[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
    
    return 0;
}