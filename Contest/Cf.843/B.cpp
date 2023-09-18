#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 4e5 + 10;

int n;
int k[maxn];
vector<int> c[maxn];
int cnt[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> k[i];
		c[i].resize(k[i]);
		for(int j = 0; j < k[i]; j++) {
			cin >> c[i][j];
			cnt[c[i][j]]++;
		}
	}
	
	int tag;
	for(int i = 1; i <= n; i++) {
		tag = 1;
		for(int j = 0; j < k[i]; j++) {
			if(--cnt[c[i][j]] == 0) {
				tag = 0;
			}
		}
		if(tag) break;
		for(int j = 0; j < k[i]; j++) {
			cnt[c[i][j]]++;
		}
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j < k[i]; j++) {
			cnt[c[i][j]] = 0;
		}
	}
	
	if(tag) {
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
