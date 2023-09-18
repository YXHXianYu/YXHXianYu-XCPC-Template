#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 10 + 10;

int n;
char s[maxn];
char f[100];

int m = 0;
	
void work() {
	
	cin >> n;
	cin >> (s + 1);
	
	for(int i = 1; i <= 8; i++) {
		int j;
		for(j = 1; j <= n; j++) {
			if(s[j] != f[i + j])
				break;
		}
		if(j > n) {
			cout << "YES" << endl;
			return;
		}
	}
	
	cout << "NO" << endl;
	return;
	
	
	
	
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i = 1; i <= 100; i++) {
		if(i % 3 == 0) {
			f[++m] = 'F';
		}
		if(i % 5 == 0) {
			f[++m] = 'B';
		}
	}
	m = 16;
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
