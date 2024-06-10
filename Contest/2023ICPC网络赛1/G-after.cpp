#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int MAXN = 1e6 + 10;

vector<int> inv(MAXN + 1);
vector<array<int, 2>> a(MAXN + 1);
vector<vector<int>> e(MAXN + 1, vector<int>());
vector<int> f(MAXN + 1);
vector<int> sz(MAXN + 1), deg(MAXN + 1);

int find(int x) {
	return (f[x] == x ? x : f[x] = find(f[x]));
}
void merge(int x, int y) {
	f[y] = x;
	sz[x] += sz[y];
	deg[x] += deg[y];
}

void work() {
	const int MOD = 998244353;
	
	int n;
	scanf("%lld", &n);
	
	inv[1] = 1;
	for(int i = 2; i <= n; ++i) {
		inv[i] = (MOD - 1ll * MOD / i * inv[MOD % i] % MOD);
	}
	
	for(int i = 1; i < n; i++) {
		scanf("%lld%lld", &a[i][0], &a[i][1]);
	}
	
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%lld%lld", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	for(int i = 1; i <= n; i++) f[i] = i;
	for(int i = 1; i <= n; i++) sz[i] = 1;
	for(int i = 1; i <= n; i++) deg[i] = e[i].size();
	
	int ans = 1;
	for(int i = 1; i < n; i++) {
		int u = find(a[i][0]);
		int v = find(a[i][1]);
		
		if(deg[u] > deg[v]) swap(u, v);
		
		int flag = 0;
		
		for(auto x: e[u]) {
			if(find(x) == v) {
				flag = 1;
			} else {
				e[v].push_back(x);
			}
		}
		
		if(flag == 0) {
			printf("%d\n", 0);
			return;
		}
		
		ans = 1ll * ans * inv[sz[u]] % MOD * inv[sz[v]] % MOD;
		
		merge(v, u);
	}
	
	printf("%d\n", ans);
}

signed main() {
	
	int t = 1;
	while(t--) {
		work();
	}
	
	return 0;
}
