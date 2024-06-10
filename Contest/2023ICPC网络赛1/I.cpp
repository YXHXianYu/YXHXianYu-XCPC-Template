#include<bits/stdc++.h>
using namespace std;
#define endl '\n'

const int MOD = 998244353;
int dp[100001][62];
int mul(int a, int b) {
	int res = 0;
	for(; b; b >>= 1) {
		if(b & 1) res = (res + a) % MOD;
		a = a * 2 % MOD;
	}
	return res;
}
int get(char c) {
	if(islower(c)) return c - 'a';
	if(isupper(c)) return c - 'A' + 26;
	return c - '0' + 52;
}

void work() {
	int n;
	cin >> n;
	string s;
	cin >> s;
	s = " " + s;
	
	bool up = false, low = false, dig = false;
	if(s[1] == '?') {
		for(int i = 0; i < 62; i++) {
			dp[1][i] = 1;
		}
	} else if(islower(s[1])) {
		dp[1][get(s[1])] = dp[1][get(s[1]) + 26] = 1;
		low = true;
	} else {
		dp[1][get(s[1])] = 1;
		if(isupper(s[1])) up = true;
		else dig = true;
	}
	
	for(int i = 2; i <= n; i++) {
		int sum = 0;
		for(int j = 0; j < 62; j++) {
			sum = (sum + dp[i - 1][j]) % MOD;
		}
		if(s[i] == '?') {
			for(int j = 0; j < 62; j++) {
				dp[i][j] = sum - dp[i - 1][j];
				if(dp[i][j] < 0) dp[i][j] += MOD;
			}
		} else if(islower(s[i])) {
			low = true;
			int j = get(s[i]);
			dp[i][j] = sum - dp[i - 1][j];
			if(dp[i][j] < 0) dp[i][j] += MOD;
			dp[i][j + 26] = sum - dp[i - 1][j + 26];
			if(dp[i][j + 26] < 0) dp[i][j + 26] += MOD;
		} else {
			if(isupper(s[i])) up = true;
			else dig = true;
			int j = get(s[i]);
			dp[i][j] = sum - dp[i - 1][j];
			if(dp[i][j] < 0) dp[i][j] += MOD;
		}
	}
	
	int ans1 = 0;
	for(int j = 0; j < 62; j++) {
		ans1 = ans1 + dp[n][j];
		if(ans1 >= MOD) ans1 -= MOD;
	}
	
//	cout << "aaa " << ans1 << endl;
	
	if(!up) {
		memset(dp, 0, sizeof(dp));
		if(s[1] == '?') {
			for(int i = 0; i < 36; i++) {
				dp[1][i] = 1;
			}
		} else if(islower(s[1])) {
			dp[1][s[1] - 'a'] = 1;
		} else {
			dp[1][s[1] - '0' + 26] = 1;
		}
		
		for(int i = 2; i <= n; i++) {
			int sum = 0;
			for(int j = 0; j < 36; j++) {
				sum = (sum + dp[i - 1][j]) % MOD;
			}
			if(s[i] == '?') {
				for(int j = 0; j < 36; j++) {
					dp[i][j] = sum - dp[i - 1][j];
					if(dp[i][j] < 0) dp[i][j] += MOD;
				}
			} else if(islower(s[i])) {
				int j = s[i] - 'a';
				dp[i][j] = sum - dp[i - 1][j];
				if(dp[i][j] < 0) dp[i][j] += MOD;
			} else {
				int j = s[i] - '0' + 26;
				dp[i][j] = sum - dp[i - 1][j];
				if(dp[i][j] < 0) dp[i][j] += MOD;
			}
		}
		
		int ans2 = 0;
		for(int j = 0; j < 36; j++) {
			ans2 += dp[n][j];
			if(ans2 >= MOD) ans2 -= MOD;
		}
		
		ans1 -= ans2;
		if(ans1 < 0) ans1 += MOD;
	}
	
	{
		// no low
		auto curget = [](char c) {
			if(isupper(c)) return c - 'A';
			if(islower(c)) return c - 'a';
			return c - '0' + 26;
		};
		
		memset(dp, 0, sizeof(dp));
		if(s[1] == '?') {
			for(int i = 0; i < 36; i++) {
				dp[1][i] = 1;
			}
		} else {
			dp[1][curget(s[1])] = 1;
		}
		
		for(int i = 2; i <= n; i++) {
			int sum = 0;
			for(int j = 0; j < 36; j++) {
				sum = (sum + dp[i - 1][j]) % MOD;
			}
			if(s[i] == '?') {
				for(int j = 0; j < 36; j++) {
					dp[i][j] = sum - dp[i - 1][j];
					if(dp[i][j] < 0) dp[i][j] += MOD;
				}
			} else {
				int j = curget(s[i]);
				dp[i][j] = sum - dp[i - 1][j];
				if(dp[i][j] < 0) dp[i][j] += MOD;
			}
		}
		
		int ans2 = 0;
		for(int j = 0; j < 36; j++) {
			ans2 += dp[n][j];
			if(ans2 >= MOD) ans2 -= MOD;
		}
		
		ans1 -= ans2;
		if(ans1 < 0) ans1 += MOD;
	}
	
	if(!dig) {
		memset(dp, 0, sizeof(dp));
		if(s[1] == '?') {
			for(int i = 0; i < 52; i++) {
				dp[1][i] = 1;
			}
		} else if(islower(s[1])) {
			dp[1][s[1] - 'a'] = dp[1][s[1] - 'a' + 26] = 1;
		} else {
			dp[1][s[1] - 'A' + 26] = 1;
		}
		
		for(int i = 2; i <= n; i++) {
			int sum = 0;
			for(int j = 0; j < 52; j++) {
				sum = (sum + dp[i - 1][j]) % MOD;
			}
			if(s[i] == '?') {
				for(int j = 0; j < 52; j++) {
					dp[i][j] = sum - dp[i - 1][j];
					if(dp[i][j] < 0) dp[i][j] += MOD;
				}
			} else if(islower(s[i])) {
				int j = s[i] - 'a';
				dp[i][j] = sum - dp[i - 1][j];
				if(dp[i][j] < 0) dp[i][j] += MOD;
				dp[i][j + 26] = sum - dp[i - 1][j + 26];
				if(dp[i][j] < 0) dp[i][j] += MOD;
			} else {
				int j = s[i] - 'A' + 26;
				dp[i][j] = sum - dp[i - 1][j];
				if(dp[i][j] < 0) dp[i][j] += MOD;
			}
		}
		
		int ans2 = 0;
		for(int j = 0; j < 52; j++) {
			ans2 += dp[n][j];
			if(ans2 >= MOD) ans2 -= MOD;
		}
		
		ans1 -= ans2;
		if(ans1 < 0) ans1 += MOD;
	}
	
	// only up
	if(!dig) {
		auto curget = [](char c) {
			if(islower(c)) return c - 'a';
			return c - 'A';
		};
		
		memset(dp, 0, sizeof(dp));
		
		if(s[1] == '?') {
			for(int i = 0; i < 26; i++) {
				dp[1][i] = 1;
			}
		} else {
			dp[1][curget(s[1])] = 1;
		}
		
		
		for(int i = 2; i <= n; i++) {
			int sum = 0;
			for(int j = 0; j < 26; j++) {
				sum = (sum + dp[i - 1][j]) % MOD;
			}
			if(s[i] == '?') {
				for(int j = 0; j < 26; j++) {
					dp[i][j] = sum - dp[i - 1][j];
					if(dp[i][j] < 0) dp[i][j] += MOD;
				}
			} else {
				int j = curget(s[i]);
				dp[i][j] = sum - dp[i - 1][j];
				if(dp[i][j] < 0) dp[i][j] += MOD;
			}
		}
		
		int ans3 = 0;
		for(int j = 0; j < 26; j++) {
			ans3 += dp[n][j];
			if(ans3 >= MOD) ans3 -= MOD;
		}
		
		ans1 += ans3;
		if(ans1 >= MOD) ans1 -= MOD;
	}
	
	// only dig
	if(!low && !up) {
		memset(dp, 0, sizeof(dp));
		if(s[1] == '?') {
			for(int i = 0; i < 10; i++) {
				dp[1][i] = 1;
			}
		} else {
			dp[1][s[1] - '0'] = 1;
		}
		
		for(int i = 2; i <= n; i++) {
			int sum = 0;
			for(int j = 0; j < 10; j++) {
				sum = (sum + dp[i - 1][j]) % MOD;
			}
			if(s[i] == '?') {
				for(int j = 0; j < 10; j++) {
					dp[i][j] = sum - dp[i - 1][j];
					if(dp[i][j] < 0) dp[i][j] += MOD;
				}
			} else {
				int j = s[i] - '0';
				dp[i][j] = sum - dp[i - 1][j];
				if(dp[i][j] < 0) dp[i][j] += MOD;
			}
		}
		
		int ans3 = 0;
		for(int j = 0; j < 10; j++) {
			ans3 += dp[n][j];
			if(ans3 >= MOD) ans3 -= MOD;
		}
		
		ans1 += ans3;
		if(ans1 >= MOD) ans1 -= MOD;
	}
	
	// only low
	if(!up && !dig) {
		memset(dp, 0, sizeof(dp));
		if(s[1] == '?') {
			for(int i = 0; i < 26; i++) {
				dp[1][i] = 1;
			}
		} else {
			dp[1][s[1] - 'a'] = 1;
		}
		
		for(int i = 2; i <= n; i++) {
			int sum = 0;
			for(int j = 0; j < 26; j++) {
				sum = (sum + dp[i - 1][j]) % MOD;
			}
			if(s[i] == '?') {
				for(int j = 0; j < 26; j++) {
					dp[i][j] = sum - dp[i - 1][j];
					if(dp[i][j] < 0) dp[i][j] += MOD;
				}
			} else {
				int j = s[i] - 'a';
				dp[i][j] = sum - dp[i - 1][j];
				if(dp[i][j] < 0) dp[i][j] += MOD;
			}
		}
		
		int ans3 = 0;
		for(int j = 0; j < 26; j++) {
			ans3 += dp[n][j];
			if(ans3 >= MOD) ans3 -= MOD;
		}
		
		ans1 += ans3;
		if(ans1 >= MOD) ans1 -= MOD;
	}
	
	cout << ans1;
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
