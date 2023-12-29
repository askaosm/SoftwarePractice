#include<iostream>
#include<vector>
#include <queue>
#include<functional>
#include<algorithm>
using namespace std;
void largestNnumbers(int N, int** arr);
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
    largestNnumbers(N, arr);


    //free
    for (int i = 0; i < N; i++) {
        delete[] arr[i];
    }

}

void largestNnumbers(int N, int **arr) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int j = 0; j < N; j++) {
        minHeap.push(arr[0][j]);
     }
   
    
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (minHeap.top() < arr[i][j]) {
                minHeap.pop();
                minHeap.push(arr[i][j]);
            }
            
        }
    }
    vector<int> temp;
    while (!minHeap.empty()) {
        temp.push_back(minHeap.top());
        minHeap.pop();
   
    }
    reverse(temp.begin(), temp.end());
    for (int i = 0; i < N; i++) {
        cout << temp[i] << " ";
    }
    

}