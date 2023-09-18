#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
int a[maxn];

void work() {

	int N = 0;
	map<int, int> f;
	vector<set<int> > g;
	
	g.push_back(set<int>());
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			int delta = a[j] - a[i];
			
//			cout << "(" << i << ", " << j << ")" << endl;
			
			for(int m = 1; m <= delta; m++) {
				int k = delta - m * m;
				if(k < 0) break;
				if(k % (2 * m) != 0) continue;
				k /= 2 * m;
				int x = k * k - a[i];
				if(x < 0) break;
				int p;
				
				if(f.count(x) == 0) {
					f[x] = ++N;
					g.push_back(set<int>());
					p = N;
				} else {
					p = f[x];
				}
				
				g[p].insert(i);
				g[p].insert(j);
//				cout << " - x = " << x << endl;
//				cout << " - g[" << p << "] insert: " << i << endl;
//				cout << " - g[" << p << "] insert: " << j << endl;
			}
		}
	}
	
	int ans = 1;
	for(int i = 1; i <= N; i++) 
		ans = max(ans, (int)(g[i].size()));
	cout << ans << endl;
	
	
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
