#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
char s[maxn];

void work() {
	
	cin >> n;
	cin >> s;
	
	char mn = 'z' + 1;
	for(int i = 0; i < n; i++) {
		mn = min(mn, s[i]);
	}
	
	int pos = -1;
	for(int i = n - 1; i >= 0; i--) {
		if(s[i] == mn) {
			pos = i;
			break;
		}
	}
	
	cout << s[pos];
	for(int i = 0; i < pos; i++) cout << s[i];
	for(int i = pos + 1; i < n; i++) cout << s[i];
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
