#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int N = 100;
int sg[N * 3][N * 3];
int dfs(int x, int y) {
//	cout<<x<<" "<<y<<endl;
	if(x < 2 && y < 2 && x + y < 2) return 0;
	if(sg[x][y] != -1) return sg[x][y];
	vector<int> s;
	for(int i = 2; i <= x; i += 2) {
		s.push_back(dfs(x - i, y + i / 2));
	}
	for(int i = 2; i <= y; i += 2) {
		s.push_back(dfs(x + i/2, y - i));
	}
	for(int i = 1; i <= min(x, y); ++i) {
		s.push_back(dfs(x - i, y - i));
	}
	for(int i = min(x, y) + 1; i <= (y+x)/2; ++i) {
		int l = i - min(x, y);
		int r = x + y - i * 2;
		s.push_back(dfs(min(l, r), max(l, r)));
	}
	sort(s.begin(), s.end());
	int ret = 0;
	for(auto x : s) {
		if(ret == x)
			ret++;
	}
	return sg[x][y] = ret;
	
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
	
	auto check = [](int x) {
		int cnt = 0;
		while(x % 2 == 0) {
			x >>= 1;
			cnt ^= 1;
		}
		return (cnt != 0);
	};
	
//	for(int i = 1; i < a.size(); i++) cout << a[i] << " " << check(a[i]) << endl;
	
	for(int i = 1; i <= 100; i++) cout << i << ": " << check(i) << endl;
	
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
