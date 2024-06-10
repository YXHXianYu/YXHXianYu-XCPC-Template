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

	string s;
	cin >> s;
	s = " " + s;

	int cnt = 0;
	for(int i = 1, j = n; i < j; i++, j--) if(s[i] != s[j]) cnt++;

	int N = n / 2;
	if(n & 1) {
		for(int i = 0; i <= N; i++) cout << (i >= cnt);
		for(int i = N; i >= 0; i--) cout << (i >= cnt);
		cout << endl;
	} else {
		for(int i = 0; i < N; i++) cout << (i >= cnt && (i - cnt) % 2 == 0);
		cout << (N >= cnt && (N - cnt) % 2 == 0);
		for(int i = N - 1; i >= 0; i--) cout << (i >= cnt && (i - cnt) % 2 == 0);
		cout << endl;
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