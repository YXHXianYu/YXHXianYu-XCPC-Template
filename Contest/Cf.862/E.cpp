#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
vector<pair<int, int>> e[maxn];
int a[maxn];
int b[maxn]; // discrete

int A, B;
int top;
int inStk[maxn];
pair<int, int> stk[maxn];
int found = false;

void dfs(int x) {
	for(auto pr: e[x]) {
		int y = pr.first;
		int id = pr.second;
		if(inStk[y]) continue;
		
		stk[++top] = {y, id};
		inStk[y] = 1;
		
		if(y == B) {
			found = true;
			return;
		}
		dfs(y);
		if(found) return;
		
		inStk[y] = 0;
		top--;
	}
}

int fMax;
map<int, int> f;
int used[maxn];

void dfs2(int x, int fa) {
	used[x] = 1;
	f[a[x]] += 1;
	if(f[a[x]] >= 2) fMax = max(fMax, a[x]);
	for(auto y: e[x]) {
		if(y.first == fa) continue;
		if(used[y.first]) continue;
		dfs2(y.first, x);
	}
}

int ans[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		e[x].push_back({y, i});
		e[y].push_back({x, i});
	}
	
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	f.clear();
	for(int i = 1; i <= n; i++) f[a[i]] += 1;
	
	int va = -1;
	for(auto it = f.rbegin(); it != f.rend(); it++) {
		if(it->second >= 2) {
			va = max(va, it->first);
		}
	}
	
	if(va == -1) {
		for(int i = 1; i < n; i++) {
			cout << 0 << endl; 
		}
		return;
	}
	
	if(f[va] >= 3) {
		for(int i = 1; i < n; i++) {
			cout << va << endl;
		}
		return;
	}
	
	// f[va] == 2
	A = B = -1;
	for(int i = 1; i <= n; i++) {
		if(a[i] == va) {
			B = A;
			A = i;
		}
	}
	assert(A != -1 && B != -1);
	
	found = false;
	top = 0;
	stk[++top] = {A, 0};
	inStk[A] = 1;
	dfs(A);
	
//	for(int i = 1; i <= top; i++) {
//		cout << stk[i].first << ", " << stk[i].second << endl;
//	}
	
	for(int i = 1; i < n; i++) ans[i] = va;
	for(int i = 2; i <= top; i++) ans[stk[i].second] = 0;
	
	f.clear();
	fMax = 0;
	for(int i = 1; i <= n; i++) used[i] = 0;
	dfs2(stk[1].first, stk[2].first);
	ans[stk[2].second] = max(ans[stk[2].second], fMax);
	
	for(int i = 3; i <= top; i++) {
		dfs2(stk[i - 1].first, stk[i].first);
		ans[stk[i].second] = max(ans[stk[i].second], fMax);
	}
	
	f.clear();
	fMax = 0;
	for(int i = 1; i <= n; i++) used[i] = 0;
	dfs2(stk[top].first, stk[top - 1].first);
	ans[stk[top].second] = max(ans[stk[top].second], fMax);
	
	for(int i = top - 1; i >= 2; i--) {
		dfs2(stk[i].first, stk[i - 1].first);
		ans[stk[i].second] = max(ans[stk[i].second], fMax);
	}
	
	for(int i = 1; i < n; i++) cout << ans[i] << endl;
	
	
	
	
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
