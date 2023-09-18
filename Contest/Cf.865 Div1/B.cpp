#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e3 + 10;

int n;

vector<int> e[maxn];

void add(int x) {
	cout << "+ " << x << endl;
	cout.flush();
	cin >> x;
	assert(x != -2);
}

int query(int i, int j) {
	cout << "? " << i << " " << j << endl;
	cout.flush();
	int x;
	cin >> x;
	assert(x != -2);
	return x;
}

int a[maxn];
void dfs(int x, int fa) {
	a[++a[0]] = x;
	for(auto y: e[x]) {
		if(y == fa) continue;
		dfs(y, x);
	}
}

int ans[maxn];
int ans2[maxn];

int q[maxn];
int idx[maxn];

void work() {
	
	cin >> n;
	
	if(n == 2) {
		cout << "! 1 2 2 1" << endl;
		cout.flush();
		int x;
		cin >> x;
		return;
	}
	
	for(int i = 1; i <= n; i++) e[i].clear();
	
	add(n + 1);
	add(n);
	
	for(int i = 1, j = n; i < j; i++, j--) {
		e[i].push_back(j);
		e[j].push_back(i);
	}
	for(int i = 1, j = n - 1; i < j; i++, j--) {
		e[i].push_back(j);
		e[j].push_back(i);
	}
	
	a[0] = 0;
	dfs(n, -1);
	
//	for(int i = 1, j = n; i < j; i++, j--) swap(a[i], a[j]);
//	for(int i = 1; i <= n; i++) cout << a[i] << " "; cout << endl;
	
	q[1] = 0;
	for(int i = 2; i <= n; i++) {
		q[i] = query(1, i);
	}
	
	for(int i = 1; i <= n; i++) idx[i] = i;
	
	sort(idx + 1, idx + n + 1, [&](int a, int b) {
		return q[a] > q[b];	
	});
	
//	for(int i = 1; i <= n; i++) cout << i << ", " << idx[i] << ", " << q[idx[i]] << endl;
	
	// idx[1] == a[1] OR idx[1] == a[n]
	ans[idx[1]] = a[1];
	ans2[idx[1]] = a[n];
//	cout << idx[1] << " = " << a[1] << endl;
	
	int st = 2;
	int ed = n;
	int st2 = 1;
	int ed2 = n - 1;
	for(int i = 2; i <= n; i++) {
		int x = query(idx[1], idx[i]);
		if(x <= q[idx[1]]) {
			ans[idx[i]] = a[st];
			st += 1;
			ans2[idx[i]] = a[ed2];
			ed2 -= 1;
		} else {
			ans[idx[i]] = a[ed];
			ed -= 1;
			ans2[idx[i]] = a[st2];
			st2 += 1;
		}
	}
	
	cout << "! ";
	for(int i = 1; i <= n; i++) cout << ans[i] << " ";
	for(int i = 1; i <= n; i++) cout << ans2[i] << " ";
	cout << endl;
	cout.flush();
	int x;
	cin >> x;
	assert(x != -2);
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
