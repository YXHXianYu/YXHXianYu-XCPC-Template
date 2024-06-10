#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 100 + 10;

int n, m;
char a[maxn];
char b[maxn];

int f[maxn][maxn];
                                                                                                                                                                                                                                                                                                                

void work() {
	
	cin >> (a + 1);
	n = strlen(a + 1);
	
	cin >> (b + 1);
	m = strlen(b + 1);
	
	if(a[1] == b[1]) {
		cout << "YES" << endl;
		cout << a[1] << "*" << endl;
		return;
	}
	
	if(a[n] == b[m]) {
		cout << "YES" << endl;
		cout <<  "*" <<  a[n]  << endl;
		return;
	}
	
	for(int i = 1; i < n; i++) {
		for(int j = 1; j < m; j++) {
			if(a[i] == b[j] && a[i + 1] == b[j + 1]) {
				cout << "YES" << endl;
				cout << "*" << a[i] << a[i + 1] << "*" << endl;
				return;
			}
		}
	}
	
	cout << "NO" << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
