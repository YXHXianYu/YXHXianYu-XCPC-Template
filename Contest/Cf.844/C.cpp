#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
char s[maxn];
pair<int, int> cnt[200];

int tmpcnt[200];
int tmpneed[200];
int tmpneedcnt[200];
int anscnt[200];
int ansneed[200];
int ansneedcnt[200];


int tag[200];

char output[maxn];

void work() {
	
	cin >> n;
	cin >> (s + 1);
	
	for(int i = 'a'; i <= 'z'; i++) cnt[i].first = 0, cnt[i].second = i;
	
	for(int i = 1; i <= n; i++) cnt[s[i]].first++;
	
	sort(cnt + 'a', cnt + 'z' + 1);
	
	int ans = n;
	int ansi = -1;
	for(int i = 1; i <= n; i++) {
		if(n % i != 0) continue;
		
		for(int j = 'a'; j <= 'z'; j++) tmpcnt[j] = 0;
		for(int j = 'a'; j <= 'z'; j++) tag[j] = 0;
		tmpneed[0] = 0;

		int left = n / i;
		
		if(left > 26) continue;
		
		int sum = 0;
		for(int j = 'z'; j >= 'a'; j--) {
			if(cnt[j].first >= i) {
				sum += cnt[j].first - i;
				tmpcnt[cnt[j].second] = cnt[j].first - i;
				tag[cnt[j].second] = 1;
				left--;
			} else {
				if(left > 0) {
					left--;
					tmpneed[++tmpneed[0]] = cnt[j].second;
					tmpneedcnt[tmpneed[0]] = i - cnt[j].first;
					tag[cnt[j].second] = 1;
				} else {
					sum += cnt[j].first;
					tmpcnt[cnt[j].second] = cnt[j].first;
				}
			}
		}
		
		if(sum <= ans) {
			ans = sum;
			ansi = i;
			for(int j = 'a'; j <= 'z'; j++) anscnt[j] = tmpcnt[j]; // 需要删的 
			ansneed[0] = tmpneed[0];
			for(int i = 1; i <= ansneed[0]; i++) ansneed[i] = tmpneed[i]; // 用来填充的 
			for(int i = 1; i <= ansneed[0]; i++) ansneedcnt[i] = tmpneedcnt[i]; // 需要填充的数量 
			
			for(int j = 'a'; j <= 'z'; j++) {
				if(tag[j] == 0) {
					ansneed[++ansneed[0]] = i;
					ansneedcnt[ansneed[0]] = i;
				}
			}
			
		}
	}
	
	cout << ans << endl;
	for(int i = 1, j = 1; i <= n; i++) {
		if(anscnt[s[i]] > 0) {
			anscnt[s[i]]--;
			cout << ((char)(ansneed[j]));
			ansneedcnt[j]--;
			if(ansneedcnt[j] == 0) j++;
		} else {
			cout << s[i];
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
