#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
char s[maxn];

void work() {
	
	cin >> (s + 1);
	n = strlen(s + 1);
	
	if(s[2] == 'a') {
		cout << s[1] << " ";
		cout << s[2] << " ";
		for(int i = 3; i <= n; i++) cout << s[i];
		cout << endl;
	} else {
		cout << s[1] << " ";
		for(int i = 2; i < n; i++) cout << s[i];
		cout << " " << s[n] << endl;
	}
	
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
