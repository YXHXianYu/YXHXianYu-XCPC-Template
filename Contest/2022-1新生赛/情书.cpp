#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n, k;
char s[maxn]; 
int f[200];

void work() {

	cin >> n >> k;
	cin >> (s + 1);
	
	k %= 26;
	for(int i = 'a'; i <= 'z'; i++) {
		f[i] = i - k + 26;
		if(f[i] > 'z') f[i] -= 26;
	}
	
	for(int i = n; i >= 1; i--) {
		cout << ((char)(f[s[i]]));
	}
	cout << endl;
	
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	// cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
