#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int N = 500;
int sg[N * 3][N * 3];
int dfs(int i, int j) {
	
	if(i < 2 && j < 2 && i + j < 2) return 0;
	if(sg[i][j] != -1) return sg[i][j];
	
	set<int> s;
	for(int k = 1; j - 2 * k >= 0; k++) {
		int u = i + k, v = j - 2 * k;
		if(u > v) swap(u, v);
		s.insert(dfs(u, v));
	}
	for(int k = 1; i - 2 * k >= 0; k++) {
		int u = i - 2 * k, v = j + k;
		if(u > v) swap(u, v);
		s.insert(dfs(u, v));
	}
	for(int k = 1; i >= k && j >= k; k++) {
		int u = i - k, v = j - k;
		s.insert(dfs(u, v));
	}
	
	sg[i][j] = 0;
	while(s.count(sg[i][j])) sg[i][j] += 1;
	return sg[i][j];
}


void work() {
	memset(sg, -1, sizeof(sg));
	
	vector<int> a;
	
	for(int i = 0; i <= N; ++i) {
		for(int j = 0; j <= i; ++j) {
			if(dfs(j, i) == 0) {
				//cout<<i<<" "<<j<<" "<<dfs(j, i)<<endl;
//				cout<<i<<" ";
				a.push_back(i);
			}
		}
	} 
	int mod = 3;
	
	for(int i = 0; i < a.size(); i++) cout << a[i] << " "; cout << endl;
	cout << endl;
	
	int cnt = 0;
	for(int i = 1; i < a.size(); i++) {
		cout << a[i] - a[i - 1] << " "; 
		if(a[i] - a[i - 1] == 2) {
			if(++cnt == 3) {
				cout << endl;
				cnt = 0;
			}
		} else {
			cnt = 0;
		}
	}
	cout << endl;
	
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	// cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
