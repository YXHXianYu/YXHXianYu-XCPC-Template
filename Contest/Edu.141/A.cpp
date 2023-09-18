#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
int a[maxn];

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	sort(a + 1, a + n + 1);
	
	if(n == 2 && a[1] == a[2]) {
		cout << "NO" << endl;
		return;
	}
	
	int p = -1;
	bool flag = 0;
	for(int i = n - 1; i >= 1; i--) {
		if(a[i + 1] == a[i]) {
			flag = 1;
		} else {
			p = i;
			break;
		}
	}
	
	if(p == -1 && flag == 1) {
		cout << "NO" << endl;
		return;
	}
	
	if(flag == 0) {
		cout << "YES" << endl;
		for(int i = n; i >= 1; i--) {
			cout << a[i] << " ";
		}
		cout << endl;
		return;
	}
	
	swap(a[n - 1], a[p]);
	
	cout << "YES" << endl;
	for(int i = n; i >= 1; i--) {
		cout << a[i] << " ";
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
