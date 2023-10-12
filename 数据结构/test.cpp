#include<bits/stdc++.h>
using namespace std;
#define LLI long long
#define DBL double
#define pii pair<int, int>
#define mp make_pair
#define fi first
#define se second
const int maxn = 250000 + 10;
const int maxm = 500000 + 10;

int n, m;
vector<pii> e[maxn];

// Shu Lian Pou Fen
int dep[maxn];
int siz[maxn];
int son[maxn];
int fa[maxn];

int top[maxn];
int dfn[maxn];
int rnk[maxn];

int dis[maxn]; // dis[i]: the minimal distance of path from 1 to i 

void dfs1(int x, int f) {
	dep[x] = dep[f] + 1;
	siz[x] = 1;
	son[x] = 0;
	fa[x] = f;
	for(auto z: e[x]) {
		int y = z.fi;
		if(y == f) continue;
		dis[y] = min(dis[x], z.se);
		dfs1(y, x);
		siz[x] += siz[y];
		if(son[x] == 0 || siz[son[x]] < siz[y])
			son[x] = y;
	}
}

void dfs2(int x, int t) {
	top[x] = t;
	dfn[x] = ++dfn[0];
	rnk[dfn[0]] = x;
	if(son[x] == 0) return;
	dfs2(son[x], t);
	for(auto y: e[x]) {
		if(y.fi == son[x] || y.fi == fa[x]) continue;
		dfs2(y.fi, y.fi);
	}
}

int get_lca(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]])
			swap(x, y);
		x = fa[top[x]];
	}
	if(dep[x] > dep[y])
		swap(x, y);
	return x;
}

int k;
int h[maxn];
vector<pii> vte[maxn];
int stk[maxn];

int tag[maxn]; // tag[i]==1, point i is KEY
LLI f[maxn]; // subtree x, 
int dfsF(int x) { // if return value == 1, it is KEY
	f[x] = 0;
	
	//if(tag[x]) return true;
	// ²»´æÔÚÕâÖÖÇé¿ö£¬ÒòÎªÒÑ¾­ÅÅ³ýÁË 
	
	bool flag = 0;
	for(auto z: vte[x]) {
		int y = z.fi;
		
		if(tag[y]) {
			flag = true;
			f[x] += z.se;
		} else if(dfsF(y)) {
			flag = true;
			f[x] += min(1ll * z.se, f[y]);
		}
	}
	
	if(flag) return true;
	else return false;
}


void work() {
	
	cin >> n;
	for(int i = 1; i < n; i++)  {
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back(mp(v, w));
		e[v].push_back(mp(u, w));
	}
	
	dis[1] = 1000000000; // 1~1 ¾àÀë max 
	dfs1(1, 0);
	dfs2(1, 1);
	
	// sort by dfn
	auto comp = [](int x, int y) -> bool {
		return dfn[x] < dfn[y];
	};
	
	cin >> m;
	while(m--) {
		cin >> k;
		for(int i = 1; i <= k; i++)
			cin >> h[i];
		for(int i = 1; i <= k; i++)
			tag[h[i]] = 1;
		sort(h + 1, h + k + 1, comp);
		
		stk[0] = 0;
		
		vte[1].clear();
		stk[++stk[0]] = 1;
		
		// clear vte when point enter stack
		
		for(int i = 1; i <= k; i++) {
			//if(h[i] == 1) continue;
			// In this problem, point 1 is impossible to be the KEY point.
			// In other words, hi != 1.
			
			// DFN of elements in stack is in INCREASING order 
			
			int lca = get_lca(stk[stk[0]], h[i]);
			
			if(lca != stk[stk[0]]) {
				// ÅÐ¶Ï: dfn[lca] ºÍ dfn[Õ»¶¥-1]
				// Ö®ºóÅÐ¶ÏÊ±£¬Ð¡ÓÚ£¬ÏàµÈ£¬´óÓÚ£¬ÈýÖÖÇé¿ö¶¼»á³öÏÖ
				// ¼ûÎÒ×Ô¼º»­µÄÍ¼½â 
				
				while(dfn[lca] < dfn[stk[stk[0] - 1]]) {
					vte[stk[stk[0] - 1]].push_back(mp(stk[stk[0]], dis[stk[stk[0]]]));
					stk[0]--;
				}
				if(dfn[lca] > dfn[stk[stk[0] - 1]]) {
					vte[lca].clear();
					vte[lca].push_back(mp(stk[stk[0]], dis[stk[stk[0]]]));
					stk[stk[0]] = lca;
				} else {
					vte[lca].push_back(mp(stk[stk[0]], dis[stk[stk[0]]]));
					stk[0]--;
				}
			}
			vte[h[i]].clear();
			stk[++stk[0]] = h[i];
		}
		for(int i = 1; i < stk[0]; i++)
			vte[stk[i]].push_back(mp(stk[i+1], dis[stk[i+1]]));
		
		dfsF(1);
		
		cout << f[1] << endl;
		
		for(int i = 1; i <= k; i++)
			tag[h[i]] = 0;
	}
	
	
	
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t = 1;
	//cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}