#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 3e5 + 10;

int n;
int a[maxn];

int ans[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	int mx = a[1];
	int mn = a[1];
	for(int i = 2; i <= n; i++) {
		mx = max(mx, a[i]);
		mn = min(mn, a[i]);
	}
	int lim = mx - mn;
	
	multiset<int> pos;
	multiset<int> neg;
	int zero = 0;
		
	for(int i = 1; i <= n; i++) {
		if(a[i] > 0) {
			pos.insert(a[i]);
		} else if(a[i] < 0) {
			neg.insert(-a[i]);
		} else {
			zero++;
		}
	}
	
	if(pos.size() == 0 || neg.size() == 0) {
		cout << "No" << endl;
		return;
	}
	
	mx = 0;
	mn = 0;
	ans[0] = 0;
	if(pos.size() >= neg.size()) {
		auto it = pos.end();
		it--;
		ans[++ans[0]] = *it;
		pos.erase(it);
	} else {
		auto it = neg.end();
		it--;
		ans[++ans[0]] = -(*it);
		neg.erase(it);
	}
	mx = max(mx + ans[ans[0]], 0ll);
	mn = min(mn + ans[ans[0]], 0ll);
	for(int i = 2; i <= n && pos.size() > 0 && neg.size() > 0; i++) {
		
//		cout << i << ": "; for(int j = 1; j <= ans[0]; j++) cout << ans[j] << " "; cout << endl;
		
		if(pos.size() >= neg.size()) {
			auto it = pos.lower_bound(lim - mx);
			if(it != pos.begin()) {
				it--;
				ans[++ans[0]] = *it;
				pos.erase(it);
				mx = max(mx + ans[ans[0]], 0ll);
				mn = min(mn + ans[ans[0]], 0ll);
			} else {
				auto it = neg.lower_bound(lim + mn);
				if(it != neg.begin()) {
					it--;
					ans[++ans[0]] = -(*it);
					neg.erase(it);
					mx = max(mx + ans[ans[0]], 0ll);
					mn = min(mn + ans[ans[0]], 0ll);
				} else {
					cout << "No" << endl;
					return;
				}
			}
		} else {
			auto it = neg.lower_bound(lim + mn);
			
			if(it != neg.begin()) {
				it--;
				ans[++ans[0]] = -(*it);
				neg.erase(it);
				mx = max(mx + ans[ans[0]], 0ll);
				mn = min(mn + ans[ans[0]], 0ll);
			} else {
				auto it = pos.lower_bound(lim - mx);
				if(it != pos.begin()) {
					it--;
					ans[++ans[0]] = *it;
					pos.erase(it);
					mx = max(mx + ans[ans[0]], 0ll);
					mn = min(mn + ans[ans[0]], 0ll);
				} else {
					cout << "No" << endl;
					return;
				}
			}
		}
		
	}
	
	while(pos.size() > 0) {
		ans[++ans[0]] = *pos.begin();
		pos.erase(pos.begin());
		mx = max(mx + ans[ans[0]], 0ll);
		mn = min(mn + ans[ans[0]], 0ll);
		if(mx >= lim || mn <= (-lim)) {
			cout << "No" << endl;
			return;
		}
	}
	while(neg.size() > 0) {
		ans[++ans[0]] = -(*neg.begin());
		neg.erase(neg.begin());
		mx = max(mx + ans[ans[0]], 0ll);
		mn = min(mn + ans[ans[0]], 0ll);
		if(mx >= lim || mn <= (-lim)) {
			cout << "No" << endl;
			return;
		}
	}
	for(int i = 1; i <= zero; i++) {
		ans[++ans[0]] = 0;
	}
	
	cout << "Yes" << endl;
	for(int i = 1; i <= ans[0]; i++) {
		cout << ans[i] << " ";
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
