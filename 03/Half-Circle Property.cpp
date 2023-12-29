#include<iostream>
#include <vector>
#define HCP 1
#define noHCP 0
using namespace std;
int isHCP(vector<pair<float, float>> points, int N);

int main() {

	int N;
	cin >> N;
	vector<pair<float, float>> points(N);

	for (int i = 0; i < N; i++) {
		cin >> points[i].first >> points[i].second;
	}

	
	//call is HCP and output result
	int result = isHCP(points, N);
	if (result == HCP) cout << "HCP" << endl;
	else cout << "NO HCP" << endl;

	return 0;

}


int isHCP(vector<pair<float, float>> points, int N) {
	//culculate the inner product of all other points(vector)
	for (int i = 1; i < N; i++) {

		float productX = points[0].first * points[i].first;
		float productY = points[0].second * points[i].second;
		float dotProduct = productX + productY;

		if (dotProduct < 0) ///180도 안에 없음 
		{
			return noHCP;
		}

	}
	return HCP;

}
