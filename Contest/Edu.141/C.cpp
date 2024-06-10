#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e6 + 10;

int n;
int m;
int a[maxn];
pair<int, int> b[maxn];

bool check(int x) {
	
//	cout << x << ": " << endl;
	
	int s = m;
	
	int tar = n - x;
	bool tar_used = false;
	if(s < a[n - x + 1]) {
		tar++;
	} else {
		tar_used = true;
		tar--;
		s -= a[n - x + 1];
	}
	
	if(tar <= 0) return true;
	
	for(int i = 1; i <= n; i++) {
		if(b[i].second == n - x + 1 && tar_used) {
			continue;
		}
		if(s < b[i].first) {
			break;
		}
		s -= b[i].first;
		tar--;
		if(tar <= 0) return true;
	}
	
	tar = n - x + 1;
	s = m;
	
	if(s < a[n - x + 1]) return false;

	for(int i = 1; i <= n; i++) {
		if(s < b[i].first) {
			return false;
		}
		s -= b[i].first;
		tar--;
		if(tar <= 0) return true;	
	}
	assert(false);
	return true;
}

void work() {
	
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	for(int i = 1; i <= n; i++) b[i].first = a[i], b[i].second = i;
	sort(b + 1, b + n + 1);
	
//	for(int i = 1; i <= n; i++) cout << b[i].first << " " << b[i].second << endl;
	
	int s = m;
	int cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(s < b[i].first) break;
		s -= b[i].first;
		cnt++;
	}
	
	if(cnt == 0) {
		cout << n + 1 << endl;
		return;
	}
	
	int tmp = n - cnt + 2;
	int ans = tmp;
	for(int i = 1; i <= 50; i++) {
		if(tmp - i < 1) break;
		if(check(tmp - i)) {
			ans = tmp - i;
		}
	}
	
	cout << ans << endl;
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
