#include<iostream>
#include<string>
#include<vector>

using namespace std;
int N;


vector<int> minimum(string s) {
	int power = 1;
	vector<int> result;
	result.push_back(power);  int j = 0;
	
	int temp;
	for(int i=1;i<s.size(); i++){
		power *= 2;
		result.push_back(power); j++;
		
		if (power == N) break;
		if (s[i] == '1' ) {
	
			if(N%5==0){
				if (power >= 3) {
					int temp = power + result[j - 1];
					if (N % temp == 0) {
						power = temp;
						result.push_back(power); j++;
					}
					else {
						power += 1;
						result.push_back(power); j++;
					}
				}
			}
			else {
				power += 1;
				result.push_back(power); j++;

			}
	
		}
		if (power == N) break;

	}
	return result;
}

int main(void) {
	int n;
	cin >> n;
	N = n;
	string s2;
	//change to binary
	while (n != 0) {
		s2 = (n % 2 == 0 ? "0" : "1")+s2 ;
		n /= 2;

	}
	vector<int> res;
	
	res = minimum(s2);

	
	cout << res.size() - 1 << " ";
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}

	return 0;



}

