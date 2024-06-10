#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 100 + 10;

int n, x;
int a[maxn];
int b[maxn];


void work() {
	
	cin >> n >> x;
	
	if((n & x) != x) {
		cout << "-1" << endl;
		return;
	}
	
	if(n == x) {
		cout << n << endl;
		return;
	}
	
	// n > x >= 0
	
	int k = 0;
	for(; (1ll << k) <= n; k++);
	k--;
	
	for(int i = 0; i <= k; i++) {
		a[i] = (n & (1ll << i)) > 0;
		b[i] = (x & (1ll << i)) > 0;
	}
	
//	for(int i = k; i >= 0; i--) cout << a[i]; cout << endl;
//	for(int i = k; i >= 0; i--) cout << b[i]; cout << endl;
	
	
	int pre_all_1 = 1;
	int b_last_1 = k;
	int flag_10 = 0;
	for(int i = k; i >= 0; i--) {
		if(a[i] == 1) {
			if(b[i] == 1) { // a[i] == 1 && b[i] == 1
				pre_all_1 = 1;
				b_last_1 = i;
				if(flag_10) {
					cout << "-1" << endl;
					return;
				}
			} else {        // a[i] == 1 && b[i] == 0
				if(pre_all_1) {
					if(x != 0) {
						cout << "-1" << endl;
					} else {
						cout << (1ll << (k + 1)) << endl;
					}
					return;
				}
				flag_10 = 1;
			}
		} else {            // a[i] == 0 && b[i] == 0;
			if(pre_all_1) {
				pre_all_1 = 0;
			}
		}
	}
	
	if(flag_10 == false) { // n == x
		assert(false);
	}
	
	int a_first_1 = -1;
	for(int i = b_last_1 - 1; i >= 0; i--) {
		if(a[i] == 1) {
			if(a_first_1 == -1) {
				a_first_1 = i;
				break;
			}
		}
	}
	
	int ans = 0;
	for(int i = k; i >= b_last_1; i--) {
		if(a[i] == 1) {
			ans |= 1ll << i;
		}
	}
	
	ans += 1ll << (a_first_1 + 1);
	
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
