#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<array<int, 2>> a(n + 1); //0L, 1R, 2A, 3B
	for(int i = 1; i <= n; i++) {
		// cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
		// 0, 3 is useful
		int x, y;
		cin >> a[i][0] >> x >> y >> a[i][1];

	}

	sort(a.begin() + 1, a.end(), [](const array<int, 2>& a, const array<int, 2>& b) {
		if(a[1] != b[1]) return a[1] > b[1];
		return a[0] < b[0];
	});

	vector<array<int, 2>> b(n + 1);
	int top = 0;
	b[++top] = a[1];
	for(int i = 2; i <= n; i++) {
		if(a[i][1] == b[top][1]) continue;
		if(b[top][0] <= a[i][1]) {
			b[top][0] = min(b[top][0], a[i][0]);
			continue;
		}
		// a[i][1] < b[top][0]
		b[++top] = a[i];
	}

	for(int i = 1, j = top; i < j; i++, j--) swap(b[i], b[j]);

	// cout << " - ";
	// for(int j = 1; j <= top; j++) cout << "(" << b[j][0] << "," << b[j][1] << ") ";
	// cout << endl;

	vector<int> c(n + 1);
	for(int i = 1; i <= top; i++) {
		c[i] = b[i][0];
	}
	
	// cout << "top = " << top << endl;
	// for(int j = 1; j <= top; j++) cout << c[j] << " "; cout << endl;

	int q;
	cin >> q;
	for(int i = 1; i <= q; i++) {
		int x;
		cin >> x;
		int p = upper_bound(c.begin() + 1, c.begin() + top + 1, x) - c.begin();
		p--;
		int ans = x;
		if(p > 0 && x >= c[p]) {
			ans = max(ans, b[p][1]);
		}
		cout << ans << " ";
	}
	cout << endl;
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
