/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, hp;
	cin >> n >> hp;

	int N = 2 * n * 31;
	vector<array<int, 2>> trie(N);
	vector<int> sz(N);
	int rt = 1;
	int tot = 1;
	
	for(int i = 1; i <= n; i++) {
		int opt, x;
		cin >> opt >> x;
		if(opt == 0) {
			int p = rt;
			sz[p] += 1;
			for(int i = 29; i >= 0; i--) {
				int e = (x >> i & 1);
				if(trie[p][e] == 0) trie[p][e] = ++tot;
				p = trie[p][e];
				sz[p] += 1;
			}
		} else if(opt == 1) {
			int p = rt;
			sz[p] -= 1;
			for(int i = 29; i >= 0; i--) {
				int e = (x >> i & 1);
				p = trie[p][e];
				sz[p] -= 1;
			}
		} else if(opt == 2) {
			int h;
			cin >> h;

			int p = rt;
			int ans = 0;
			int cnt = 0;
			for(int i = 29; i >= 0; i--) {
				if(x >> i & 1) {
					if((1LL << i | cnt) > h) {
						if(trie[p][0]) ans += sz[trie[p][0]];
						if(!trie[p][1]) break;
						p = trie[p][1];
					} else {
						if(!trie[p][0]) break;
						p = trie[p][0];
						cnt |= 1LL << i;
					}
				} else {
					if((1LL << i | cnt) > h) {
						if(trie[p][1]) ans += sz[trie[p][1]];
						if(!trie[p][0]) break;
						p = trie[p][0];
					} else {
						if(!trie[p][1]) break;
						p = trie[p][1];
						cnt |= 1LL << i;
					}
				}
			}
			cout << ans << endl;
			if(ans == 0) hp--;
		} else assert(false);
	}
	cout << hp << endl;
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