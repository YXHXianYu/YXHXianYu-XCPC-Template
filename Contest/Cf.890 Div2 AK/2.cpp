#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i];

	if(n == 1) {
		cout << "NO" << endl;
		return;
	}

	sort(a.begin() + 1, a.begin() + n + 1);

	int sum = 0;
	for(int i = 1; i <= n; i++) {
		sum += a[i];
	}

	int R1 = n + 1;
	for(int i = n; i >= 1; i--) {
		if(a[i] > 1) {
			sum -= 1;
		} else {
			R1 = i;
			break;
		}
	}

	if(R1 > n || sum >= R1 * 2) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
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
