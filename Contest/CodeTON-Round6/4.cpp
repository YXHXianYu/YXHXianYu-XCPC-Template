/**
 * Created by YXH_XianYu on 2023.9
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n;
	cin >> n;

	vector<int> c(n + 1);
	for(int i = 1; i <= n; i++) cin >> c[i];

	int k;
	cin >> k;

	vector<array<int, 2>> stk(n + 1);
	int top = 0;
	for(int i = 1; i <= n; i++) {
		while(top && stk[top][0] >= c[i]) top--;
		stk[++top] = {c[i], i};
	}

	vector<int> out(n + 1);

	out[1] = k / stk[1][0];
	int cnt = k % stk[1][0];

	for(int i = top; i >= 2; i--) stk[i][0] -= stk[i - 1][0];
	for(int i = 2; i <= top; i++) {
		int v = min(out[i - 1], cnt / stk[i][0]);
		out[i] = v;
		cnt -= v * stk[i][0];
	}

	// cout << " - ";
	// for(int i = 1; i <= top; i++) cout << "(" << stk[i][0] << "," << stk[i][1] << ") ";
	// cout << endl;

	for(int i = 1; i <= top; i++) {
		for(int j = stk[i - 1][1] + 1; j <= stk[i][1]; j++) {
			cout << out[i] << " ";
		}
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