#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int MOD = 1e9 + 7;
const int INF = 1LL << 61;

int n;
int a[2][maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[0][i];
	
	int S = 0;
	sort(a[S] + 1, a[S] + n + 1);
	
	int N = n;
	for(int i = 1; i < n; i++) {
		int T = S ^ 1;
		
		priority_queue<pair<int, pair<int, int> > > pq;
		
		int cnt = 0;
		
		pq.push({-a[S][1]-a[S][2], {1, 2}});
		
		for(int j = 1; j < N; j++) {
			auto pr = pq.top();
			pq.pop();
			
			a[T][++cnt] = -pr.first;
			int x = pr.second.first;
			int y = pr.second.second;
			if(x == 1) {
				pq.push({-a[S][x]-a[S][y + 1], {x, y + 1}});
				pq.push({-a[S][y]-a[S][y + 1], {y, y + 1}});
			} else {
				pq.push({-a[S][x]-a[S][y + 1], {x, y + 1}});
			}
		}
		
		assert(cnt == N - 1);
		
		sort(a[T] + 1, a[T] + cnt + 1);
		
		int t = a[T][1] / MOD;
		for(int i = 1; i <= cnt; i++) {
			a[T][i] -= t * MOD;
		}
		
		assert(a[T][cnt] <= INF);
		
		N = cnt;
		S ^= 1;
		
//		for(int i = 1; i <= N; i++) {
//			cout << a[S][i] << " ";
//		}
//		cout << endl;
	}
	
	cout << a[S][1] % MOD << endl;
	
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
//	cout << INF << endl;
	
	int t = 1;
	// cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
