#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    int** A = new int* [N];
    for (int i = 0; i < N; i++) {
        A[i] = new int[N]();
    }
    int** U = new int* [N+1];
    for (int i = 0; i <= N; i++) {
        U[i] = new int[N+1]();
    }
    // read
    int R1, R2, C1, C2, V;
    for (int k = 0; k < N; ++k) {
        cin >> R1 >> R2 >> C1 >> C2 >> V;
        if (R1>=0 && C1>=0)
            U[R1][C1] += V;
        if (C2+1 <= N) 
            U[R1][C2+1] -= V;
        if (R2+1 <= N)
            U[R2+1][C1] -= V;
        if (R2+1 <= N && C2+1 <= N) 
            U[R2+1][C2+1] += V;
    }

    //culculate cumlative sum
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            U[i][j] += U[i - 1][j] + U[i][j - 1] - U[i - 1][j - 1];
        }
    }

    // add value to matrix A
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] += U[i + 1][j + 1];
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }
    for (int i = 0; i < N; i++) {
        delete[] A[i], U[i];
    }
    delete[]  U[N];
    delete[] A, U;
    return 0;
}
