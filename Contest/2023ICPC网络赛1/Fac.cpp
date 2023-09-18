#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define ll long long
#define endl '\n'

void work() {
	ll n;
	cin >> n;
	
	vector<ll> a(n + 1);
	for(ll i = 1; i <= n; i++) cin >> a[i];
	
	sort(a.begin() + 1, a.end());
	
	ll N = 0;
	vector<array<ll, 2>> b(n + 1);
	
	b[++N][0] = a[1];
	b[N][1] = 1;
	for(int i = 2; i <= n; i++) {
		if(a[i - 1] == a[i]) {
			b[N][1] += 1;
		} else {
			b[++N][0] = a[i];
			b[N][1] = 1;
		}
	}
	
	// trie
	
	vector<array<int, 2>> t(n * 60 + 100);
	vector<int> sz(n * 60 + 100);
	
	ll rt = 1;
	ll tot = 1;
	
	for(int i = 1; i <= N; i++) {
		ll p = rt;
		ll x = b[i][0];
		
		for(int j = 0; j < 60; j++) {
			int e = x & 1;
			
			if(t[p][e] == 0) {
				t[p][e] = ++tot;
			}
			p = t[p][e];
			sz[p] += b[i][1];
			
			x >>= 1;
		}
	}
	
	ll ans = 0;
	
	auto C2 = [&](ll n) -> ll{
		return n * (n - 1) / 2;
	};
	auto C3 = [&](ll n) -> ll{
		return n * (n - 1) * (n - 2) / 6;
	};
	
	for(int i = 1; i <= N; i++) {
		if(b[i][1] == 1) continue;
		
		ll cnt = 0;
		
		ll p = rt, dep = 0;
		ll x = b[i][0];
		
		for(int j = 0; j < 60; j++) {
			int e = x & 1;
			
			if(~dep&1) {
				if(t[p][e ^ 1])
					cnt += sz[t[p][e ^ 1]];
			}
			
			if(t[p][e] == 0) break;
			p = t[p][e];
			dep += 1;
			
			x >>= 1;
		}
		
		cnt = cnt * C2(b[i][1]) + C3(b[i][1]);
		
		ans += cnt;
	}
	
	cout << C3(n) - ans << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
//	freopen("F.txt", "r", stdin);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
