#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int N = 5e5 + 1010;
int n;
int a[N];

void work() {
	cin>>n;
	map<int, int> mp;
	for(int i = 1; i <= n; ++i) {
		cin>>a[i];
	}
	sort(a + 1, a + 1 + n);
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
