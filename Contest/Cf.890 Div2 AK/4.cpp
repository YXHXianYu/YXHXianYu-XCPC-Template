#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	auto query = [](int L, int R) -> int {
		if(R - L < 0) assert(false);
		if(R - L == 0) return 0;
		cout << "? " << L << " " << R << '\n';
		cout.flush();
		int x;
		cin >> x;
		return x;
	};

	function<int(int, int)> solve = [&](int L, int R) -> int {
		if(R - L < 0) assert(false); 
		if(R - L == 0) return L;

		int mid = L + R >> 1;
		int Lp = solve(L, mid);
		int Rp = solve(mid+1, R);

		int v1 = query(Lp, Rp);
		int v2 = query(Lp + 1, Rp);
		
		if(v1 - v2 == Rp - Lp) return Lp;
		else return Rp;
	};

	int ans = solve(1, n);

	cout << "! " << ans << '\n';
	cout.flush();
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
