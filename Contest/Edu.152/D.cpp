#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n;
	cin >> n;

	vector<int> a(n + 2);
	for(int i = 1; i <= n; i++) cin >> a[i];

	int ans = 0;
	vector<int> tag(n + 2);
	for(int i = 1; i <= n; i++) {
		if(tag[i] == 1) continue;
		if(a[i] == 2) {
			ans++;
			tag[i] = 1;
			for(int j = i - 1; j >= 1 && tag[j] == 0; j--) {
				if(a[j] >= 1) {
					tag[j] = 1;
				} else {
					tag[j] = 1;
					break;
				}
			}
			for(int j = i + 1; j <= n && tag[j] == 0; j++) {
				if(a[j] >= 1) {
					tag[j] = 1;
				} else {
					tag[j] = 1;
					break;
				}
			}
		}
	}

	// cout << ans << endl;
	// for(int i = 1; i <= n; i++) cout << tag[i] << " "; cout << endl;

	if(a[1] == 1 && tag[1] == 0) {
		ans++;
		tag[1] = 1;
		for(int i = 2; i <= n; i++) {
			if(tag[i] == 1) break;
			tag[i] = 1;
			if(a[i] >= 1) continue;
			break;
		}
	}

	if(a[n] == 1 && tag[n] == 0) {
		ans++;
		tag[n] = 1;
		for(int i = n - 1; i >= 1; i--) {
			if(tag[i] == 1) break;
			tag[i] = 1;
			if(a[i] >= 1) continue;
			break;
		}
	}

	for(int i = 1; i <= n; i++) {
		if(tag[i]) continue;
		if(a[i] == 1) {
			tag[i] = 1;
			if(a[i - 1] == 1) continue; // must 0, 1, i
			if(a[i - 1] == 0 && tag[i - 1] == 0) {
				ans++;
				tag[i - 1] = 1;
				continue;
			}
			if(a[i + 1] == 0 && tag[i + 1] == 0) {
				ans++;
				tag[i + 1] = 1;
				continue;
			}
			if(tag[i + 1] == 1) {
				ans++;
				continue;
			}
			// a[i + 1] == 1 && tag[i + 1] == 0
			ans++;
			for(int j = i + 1; j <= n && tag[j] == 0; j++) {
				tag[j] = 1;
				if(a[j] >= 1) continue;
				break;
			}

		}
	}
	for(int i = 1; i <= n; i++) {
		if(tag[i]) continue;
		assert(a[i] == 0);
		tag[i] = 1;
		ans++;
	}

	cout << ans << endl;
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
