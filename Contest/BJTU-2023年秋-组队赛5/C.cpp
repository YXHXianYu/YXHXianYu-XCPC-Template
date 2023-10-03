/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int read() {
	int ans = 0; char ch = getchar();
	while((ch < '0' || '9' < ch) && ch != '!') ch = getchar();
	if(ch == '!') return -1;
	while('0' <= ch && ch <= '9') ans = 10 * ans + ch - '0', ch = getchar();
	return ans;
}

void work() {
	int n = read();
	int m = read();

	
	
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