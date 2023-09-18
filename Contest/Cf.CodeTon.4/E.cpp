#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 8e5 + 10;

int n, m;
int a[maxn];

vector<int> e[maxn];
int used[maxn];
int va[maxn];

int q1[maxn];
int stk[maxn];
int tag[maxn];

void work() {
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; i++) e[i].clear();
	for(int i = 1; i <= n; i++) used[i] = 0;
	for(int i = 1; i <= n; i++) va[i] = 1;
	
	
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	
	int hd1 = 0, tl1 = 0;
	for(int i = 1; i <= n; i++) {
		if(a[i] == 0) {
			q1[++tl1] = i;
		}
	}
	
	int N = n;
	
	while(hd1 < tl1) {
		int st = q1[++hd1];
		if(used[st]) continue;
		
		int hd2 = 0, tl2 = 0;
		stk[0] = 0;
		priority_queue<pair<int, int> > pq;
		
		tag[st] = 1;
		pq.push({0, st}); // small
		
		int cnt = 0;
		
		N++;
		
		while(!pq.empty()) {
			int x = pq.top().second;
			int ava = - pq.top().first;
			pq.pop();
			tag[x] = 0; // tag: in pq
			
			if(cnt >= ava) {
				cnt += va[x];
				stk[++stk[0]] = x;
				used[x] = N;
				
				for(auto y: e[x]) {
					if(used[y] || tag[y]) continue;
					tag[y] = 1;
					pq.push({-a[y], y});
				}
			} else { // dead
				break;
			}
		}
		
		while(!pq.empty()) {
			int x = pq.top().second;
			pq.pop();
			tag[x] = 0;
		}
		
		if(cnt == n) {
			cout << "YES" << endl;
			return;
		}
		
		a[N] = 1;
		e[N].clear();
		used[N] = 0;
		va[N] = cnt;
		
//		cout << "N = " << N - n << ": ";
		for(int i = 1; i <= stk[0]; i++) {
			int x = stk[i];
//			cout << x << " ";
			for(auto y: e[x]) {
				if(used[y]) continue;
				e[N].push_back(y);
				e[y].push_back(N);
			}
		}
//		cout << endl;
		
	}
	
	cout << "NO" << endl;
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
