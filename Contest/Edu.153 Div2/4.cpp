#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	string s;
	cin >> s;
	int n = s.size();
	s = " " + s;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i++) {
		a[i] = s[i] - '0';
	}

	int s01 = 0;
	int s10 = 0;
	vector<int> f(n + 1);
	int sum = 0;
	int cnt0 = 0;
	for(int i = n; i >= 1; i--) {
		if(a[i]) {
			sum += cnt0;
			f[i] = sum;
		} else {
			cnt0++;
		}
	}
	s10 = sum;

	sum = 0;
	cnt0 = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i]) {
			sum += cnt0;
			f[i] = sum;
		} else {
			cnt0++;
		}
	}
	s01 = sum;

	// cout << s01 << ", " << s10 << endl;

	int tar = s01 + s10 >> 1;

	if(s01 == tar) {
		cout << "0" << endl;
		return;
	}

	if(s01 < tar) {
		tar = tar - s01;
		int ans = 0;
		while(tar) {
			int v = 0;
			int vi = 0;
			int vj = 0;
			for(int i = 1; i <= n; i++) {
				if(!a[i]) continue;
				for(int j = i + 1; j <= n; j++) {
					if(a[j]) continue;
					if(j - i > tar) break;
					if(j - i > v) {
						v = j - i;
						vi = i;
						vj = j;
					}
				}
			}
			ans += 1;
			tar -= v;
			swap(a[vi], a[vj]);
		}
		cout << ans << endl;
	} else { // s10 < tar
		tar = tar - s10;
		int ans = 0;
		while(tar) {
			int v = 0;
			int vi = 0;
			int vj = 0;
			for(int i = n; i >= 1; i--) {
				if(!a[i]) continue;
				for(int j = i - 1; j >= 1; j--) {
					if(a[j]) continue;
					if(i - j > tar) break;
					if(i - j > v) {
						v = i - j;
						vi = i;
						vj = j;
					}
				}
			}
			ans += 1;
			tar -= v;
			swap(a[vi], a[vj]);
		}
		cout << ans << endl;
	}
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
