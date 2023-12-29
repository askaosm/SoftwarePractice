#include<iostream>

using namespace std;

void searchK(int** arr, int N, int k) {
    int row = 0;
    int col = N - 1;
    while (row < N && col >= 0) {
        if (k > arr[row][col]) {
            row++;
        }
        else if (k < arr[row][col]) {
            col--;
        }
        else {
            int positionX = col + 1;
            int positionY = row + 1;

            cout << positionY << " " << positionX << endl;
            return;
        }
    }
    cout << "not found" << endl;
}

int main(void) {
    int N;
    cin >> N;

    int** arr = new int* [N];
    for (int i = 0; i < N; i++) {
        arr[i] = new int[N];
    }


    // get the matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
    int k;
    cin >> k; //get the search number

    searchK(arr, N, k);


    //free
    for (int i = 0; i < N; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    return 0;
}