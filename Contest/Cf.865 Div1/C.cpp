#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 10000 + 10;
const int maxm = 10000 + 10;

int n, m;
int a[maxm];
int b[maxm];

vector<int> e[maxn];

int dfn[maxn];
int low[maxn];
int scc[maxn];

int inStk[maxn];
int stk[maxn];

void tarjan(int x) {
	low[x] = dfn[x] = ++dfn[0];
	stk[++stk[0]] = x;
	inStk[x] = 1;
	
	for(auto y: e[x]) {
		if(dfn[y] == 0) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if(inStk[y] == 1) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	
	if(dfn[x] == low[x]) {
		scc[0]++;
		while(stk[stk[0]] != x) {
			scc[stk[stk[0]]] = scc[0];
			inStk[stk[stk[0]]] = 0;
			stk[0]--;
		}
		scc[stk[stk[0]]] = scc[0];
		inStk[stk[stk[0]]] = 0;
		stk[0]--;
	}
	
}
int N;
int dep[maxn];
int q[maxn];
const int INF = 1000000000;
void bfs(int st) {
	
	for(int i = 1; i <= N; i++) dep[i] = INF;
	int hd = 0, tl = 0;
	
	dep[st] = 1;
	q[++tl] = st;
	
	while(hd < tl) {
		int x = q[++hd];
		for(auto y: e[x]) {
			if(dep[y] > dep[x] + 1) {
//				cout << x << " -> " << y << endl;
				dep[y] = dep[x] + 1;
				q[++tl] = y;
			}
		}
	}
}

vector<int> ans[maxn];
vector<int> sccv[maxn];

int ansT[2000010];

void work() {
	
	cin >> n >> m;
	for(int i = 1; i <= m; i++) cin >> a[i] >> b[i];
	
	if(n == 1) {
		assert(m == 0);
		cout << "FINITE" << endl;
		cout << 1 << endl;
		cout << 1 << endl;
		return;
	}
	
	for(int i = 1; i <= n; i++) e[i].clear();
	
	for(int i = 1; i <= m; i++) {
		if(a[i] == 1) continue; // 1 only have out edge
		
		e[b[i]].push_back(a[i]);
	}
	
	for(int i = 0; i <= n; i++) stk[i] = inStk[i] = dfn[i] = low[i] = scc[i] = 0;
	
	tarjan(1);
	
	for(int i = 1; i <= n; i++)
		if(dfn[i] == 0) {
			cout << "INFINITE" << endl;
			return;
		}
	
	
	N = scc[0];
	for(int i = 1; i <= N; i++) e[i].clear();
	for(int i = 1; i <= m; i++) {
		if(a[i] == 1) continue;
		if(scc[a[i]] == scc[b[i]]) continue;
		
//		cout << scc[b[i]] << " -> " << scc[a[i]] << endl;
		e[scc[b[i]]].push_back(scc[a[i]]);
	}
	
	bfs(scc[1]);
	
	for(int i = 0; i <= N; i++) ans[i].clear();
	for(int i = 0; i <= N; i++) sccv[i].clear();
	
	for(int i = 1; i <= n; i++) sccv[scc[i]].push_back(i);
	
//	cout << " - "; for(int i = 1; i <= n; i++) cout << i << " " << scc[i] << ","; cout << endl;
//	cout << " - "; for(int i = 1; i <= N; i++) cout << dep[i] << " "; cout << endl;
	
	int mx = 0;
	for(int i = 1; i <= N; i++) {
		ans[dep[i]].push_back(i);
		mx = max(mx, dep[i]);
	}
	
	ansT[0] = 0;
	for(int i = mx; i >= 1; i--) {
		for(int j = i; j <= mx; j++) {
			
			for(auto k: ans[j]) {
				for(auto v: sccv[k]) {
					ansT[++ansT[0]] = v;
				}
			}
			
		}
	}
	
	cout << "FINITE" << endl;
	cout << ansT[0] << endl;
	for(int i = 1; i <= ansT[0]; i++) {
		cout << ansT[i] << " ";
	}
	cout << endl;
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
