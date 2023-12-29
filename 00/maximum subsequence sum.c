#include<stdio.h>
#include<stdlib.h>
#define MAX(a,b) ((a)>(b)?(a):(b))
int* arr; // array

int Kadane(int N) {
    int maxTail; //maximum sum of sub_array ending at the current position
    int maxSum; // maximum sum of sub_array found up to this point
    
    //initialize
    maxTail = arr[0];
    maxSum = arr[0];

    //kadane algorithm
    for (int i = 1; i < N; i++) {
       maxTail = MAX(arr[i],maxTail + arr[i]);

 
        if (maxSum <maxTail)
            maxSum =maxTail;
    }

    return maxSum;

}

int main(void) {
    int N; //the number of an array element
    int resultSum; // result

    //Input
    scanf("%d", &N);

    arr = (int*)malloc(N * sizeof(int));

    // Input element of an array
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]); 
    }

    //Calculate
    resultSum = Kadane(N);

    //Output result
    printf("%d", resultSum);

    free(arr);


}