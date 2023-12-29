#include<iostream>
#include<vector>
#include<stack>

using namespace std;
int N, S; //the number of coin type, change Sum
vector<int> types, counts; //coin types, the number of coins
vector<vector<int > > possibleCases; // possible cases

void findCombination();
void bSort(vector<vector<int> >& t);


int main(void) {
    //input
    cin >> N >> S;
    types.resize(N);  counts.resize(N);
    for (int i = 0; i < N; i++)
        cin >> types[i] >> counts[i];

    
    findCombination();

    //output
    bSort(possibleCases);

    cout << possibleCases.size() << endl;

    for (int i = 0; i < possibleCases.size(); i++) {
        for (int j = 0; j < possibleCases[i].size(); j++) {
            cout << possibleCases[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

void findCombination() {
    // Stack structure: (id, (currentSum, currentCombination))
    stack<pair<int, pair<int, vector<int>>>> st;

    st.push(make_pair(0, make_pair(0, vector<int>())));

    while (!st.empty()) {
        pair<int, pair<int, vector<int>>> top = st.top();
        st.pop();

        int id = top.first;
        int currentSum = top.second.first;
        vector<int> currentCombination = top.second.second;

        if (S == currentSum) {
            possibleCases.push_back(currentCombination);
            continue;
        }

        if (currentSum > S)
            continue;
        if (id >= N) continue;
        for (int coin_num = 0; coin_num <= counts[id]; coin_num++) {
            vector<int> newCombination = currentCombination;
            for (int i = 0; i < coin_num; i++) {
                newCombination.push_back(types[id]);
            }
            int nextSum = types[id] * coin_num + currentSum;
            st.push(make_pair(id + 1, make_pair(nextSum, newCombination)));
        }
    }
}



void bSort(vector<vector <int > >& t) {
    int n = t.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (t[j].size() > t[j + 1].size());
            {
                vector <int> temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;

            }
        }
    }
}

