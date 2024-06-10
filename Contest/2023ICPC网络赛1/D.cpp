#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

const int N = 2e6 + 1010;
const int inf = 1ll << 60;
int n, m;
int fa[N];
int sz[N], sum[N];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int q[N], cnt;
void work() {
	cin>>n>>m;
	for(int i  = 1; i <= n; ++i) {
		fa[i] = i;
		sum[i] = 1;
	}
	for(int i  = 1, u, v; i <= m; ++i) {
		cin>>u>>v;
		int fu = find(u), fv = find(v);
		if(fu == fv) {
			sz[fu]++;
			continue;
		}
		fa[fu] = fv;
		sz[fv] += sz[fu] + 1;
		sum[fv] += sum[fu];
		
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		if(fa[i] != i) continue;
		int s = sum[i];
		s = (s) * (s - 1) / 2;
		ans += s - sz[i];
	}
	
	
	if(ans == 0) {
		int min1 = inf, min2 = inf;
		for(int i = 1; i <= n; ++i) {
			if(fa[i] != i) continue;
			if(sum[i] <= min1) {
				min2 = min1;
				min1 = sum[i];
			}
			else if(sum[i] < min2){
				min2 = sum[i];
			}
		}
		cout<<min1 * min2<<"\n";
		return;
	}
	cout<<ans;
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
