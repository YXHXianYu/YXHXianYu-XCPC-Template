#include<bits/stdc++.h>
using namespace std;
#define int long long

struct BIT {
	int n;
	vector<int> a;
	BIT(int n = 0) { init(n); }
	void init(int n) { this->n = n; a.resize(n + 1); }

	#define lowbit(x) (x&-x)
	void set(int x, int v) {
		for(; x <= n; x += lowbit(x)) a[x] = max(a[x], v);
	}
	int get(int x) {
		int ans = 0; for(; x; x -= lowbit(x)) ans = max(ans, a[x]); return ans;
	}
};

void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	int N = 0;
	for(int i = 1; i <= n; i++) N = max(N, a[i]);

	BIT bit(N);
	vector<int> b(N + 1);
	for(int i = 1; i <= n; i++) {
		int v = bit.get(a[i] - 1);
		if(b[a[i]] < v + a[i]) {
			b[a[i]] = v + a[i];
			bit.set(a[i], b[a[i]]);
		}
	}

	cout << bit.get(N) << endl;
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