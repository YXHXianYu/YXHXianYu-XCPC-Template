#include<bits/stdc++.h>
using namespace std;
const int maxn = 6e5 + 10;
const int target = 3e5 + 1;

int n;
int a[maxn];
int s, t;

vector<int> e[maxn];
map<int, int> edgeValue[maxn];

int pri[maxn];
int isntPri[maxn];
int numberP[maxn];
void getPrime(int N) {
	for(int i = 2; i <= N; i++) {
		if(!isntPri[i]) {
			pri[++pri[0]] = i;
			numberP[i] = pri[0];
		}
		for(int j = 1; j <= pri[0] && (i * pri[j] <= N) && i * pri[j] <= target; j++) {
			isntPri[i * pri[j]] = 1;
			if(i % pri[j] == 0) break;
		}
	}
}

int fa[maxn];
int vis[maxn];
int q[maxn];
int ans[maxn];
void bfs() {
	
	int hd = 0, tl = 0;
	
	q[++tl] = 0;
	vis[0] = 1;
	
	while(hd < tl) {
		int x = q[++hd];
		
		for(auto y: e[x]) {
			if(vis[y]) continue;
			vis[y] = 1;
			fa[y] = x;
			q[++tl] = y;
			
			if(y == target) {
				ans[++ans[0]] = t;
				while(fa[x] != 0) {
					int f = fa[x];
					ans[++ans[0]] = edgeValue[f][x];
					x = f;
				}
				ans[++ans[0]] = s;
				
				cout << ans[0] << endl;
				for(int i = ans[0]; i >= 1; i--) cout << ans[i] << " ";
				cout << endl;
				
				return;
			}
		}
	}
	
	cout << -1 << endl;
}

void work() {

	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	cin >> s >> t;
	
	if(s == t) {
		cout << 1 << endl;
		cout << s << endl;
		return;
	}
//	if(a[s] == 1 && a[t] == 1) {
//		cout << -1 << endl;
//		return;
//	}
//	if(a[s] == a[t]) {
//		cout << 2 << endl;
//		cout << s << " " << t << endl;
//		return;
//	}
	
	getPrime(300000);
	
	for(int i = 1; i <= n; i++) {
		vector<int> fac;
		
		int x = a[i];
		int lim = sqrt(x);
		for(int j = 1; pri[j] <= x && pri[j] <= lim && j <= pri[0]; j++) {
			if(x % pri[j] != 0) continue;
			x /= pri[j];
			while(x % pri[j] == 0) x /= pri[j];
			
			fac.push_back(j);
		}
		if(x > 1) {
			if(isntPri[x]) {
				assert(false);
			}
			fac.push_back(numberP[x]);
		}
		
		for(auto st: fac) {
			for(auto ed: fac) {
				if(st == ed) continue;
				if(edgeValue[st].count(ed) == 0) {
					edgeValue[st][ed] = i;
					edgeValue[ed][st] = i;
					e[st].push_back(ed);
					e[ed].push_back(st);
				}
			}
		}
		
		if(i == s) {
			for(auto j: fac) {
				e[0].push_back(j);
			}
		} else if(i == t) {
			for(auto j: fac) {
				e[j].push_back(target);
			}
		}
	}
	
	bfs();
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
