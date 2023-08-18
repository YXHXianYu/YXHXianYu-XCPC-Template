#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	string a;
	cin >> a;
	int n = a.size();
	a = " " + a + "#";

	string b;
	cin >> b;
	int m = b.size();
	b = " " + b;

	vector<int> nxt(m + 1);
	for(int i = 2, j = 0; i <= m; i++) {
		while(j && b[i] != b[j + 1]) j = nxt[j];
		if(b[i] == b[j + 1]) j++;
		nxt[i] = j;
	}

	for(int i = 1, j = 0; i <= n; i++) {
		while(j && a[i] != b[j + 1]) j = nxt[j];
		if(a[i] == b[j + 1]) j++;
		if(j == m) cout << i - m + 1 << endl;
	}

	for(int i = 1; i <= m; i++) {
		cout << nxt[i] << " ";
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
