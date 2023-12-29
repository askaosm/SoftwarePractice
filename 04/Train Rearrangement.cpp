#include<iostream>
#include<stack>
#include<vector>

using namespace std;

bool TrainRearrangement(int N, vector<int>& train) {
    stack<int> s;
    int count = 1;

    for (int i = 0; i < N; i++) {
        int val = train[i];
        s.push(val);  //move A to B

        while (!s.empty() && s.top() == count) {
            s.pop(); //move B to c
            count++;
        }
    }

    return s.empty();  
}

int main() {
    int caseNum;
    vector<bool> result;
    cin >> caseNum; //following cases

    for (int i = 0; i < caseNum; i++) {
        int N;
        cin >> N;
        vector<int> train(N);
        for (int j = 0; j < N; j++) {
            cin >> train[j];  
        }
        result.push_back(TrainRearrangement(N, train));
    }

    for (int i = 0; i < result.size(); i++) {
        if (result[i]) {
            cout << "POSSIBLE" << endl;
        }
        else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}
