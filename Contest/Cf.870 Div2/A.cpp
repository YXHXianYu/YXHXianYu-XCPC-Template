#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
int l[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> l[i];
	
	sort(l + 1, l + n + 1);
	
	if(l[n] == 0) {
		cout << 0 << endl;
		return;
	}
	
	int cnt = 0;
	for(int i = n - 1; i >= 1; i--) {
		int v = n - i;
		if(l[i + 1] > v && l[i] <= v) {
			cout << v << endl;
			return;
		}
	}
	
	cout << -1 << endl;
	
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
