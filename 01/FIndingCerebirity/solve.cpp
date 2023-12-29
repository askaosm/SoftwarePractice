#include "solve.hpp"
#include<stack>

using namespace std;
int solve(Party* party) {
	//get the number of people
	int N = party->getN();
	stack<int> st;

	for (int i = 0; i < N; i++)
		st.push(i);
	int A, B;
	while (st.size() > 1) {
		A = st.top();
		st.pop();
		B = st.top();
		st.pop();


		if (party->askAToKnowB(A, B))
			st.push(B);
		else st.push(A);

	}
	int Pcelebrity = st.top();
	st.top();

	for (int i = 0; i < N; i++) {
		if (i != Pcelebrity) {
			if (party->askAToKnowB(Pcelebrity, i) || !party->askAToKnowB(i, Pcelebrity))
				return -1;

		}
	}

	return Pcelebrity;
}


