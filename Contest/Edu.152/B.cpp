#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;


void work() {
	int n, k;
	cin >> n >> k;

	vector<pair<int, int>> a(n + 1);
	for(int i = 1; i <= n; i++) cin >> a[i].first, a[i].second = i;
	for(int i = 1; i <= n; i++) a[i].first = (a[i].first - 1) % k + 1;

	sort(a.begin() + 1, a.end(), [](const pair<int,int>&a, const pair<int,int>& b){
		if(a.first != b.first) return a.first > b.first;
		else return a.second < b.second;
	});

	for(int i = 1; i <= n; i++) cout << a[i].second << " "; cout << endl;


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
