#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int x;
	cin >> x;

	vector<int> ans;
	ans.push_back(x);

	priority_queue<int> pq;

	int y = x;
	for(int i = 2, lim = sqrt(x); i <= lim && y > 1; i++) {
		while(y % i == 0) {
			y /= i;
			pq.push(i);
		}
	}
	if(y > 1) pq.push(y);

	while(pq.top() >= 3) {
		int y = pq.top();
		pq.pop();
		int k = x / y;
		x = x - k;
		ans.push_back(x);

		y -= 1;
		for(int i = 2, lim = sqrt(y); i <= lim && y > 1; i++) {
			while(y % i == 0) {
				y /= i;
				pq.push(i);
			}
		}
		if(y > 1) pq.push(y);
	}
	while(x >= 2) {
		x /= 2;
		ans.push_back(x);
	}

	cout << ans.size() << endl;
	for(auto x: ans) cout << x << " "; cout << endl;
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
