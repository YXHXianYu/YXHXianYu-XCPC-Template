#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;
char s[maxn];

void work() {
	
	cin >> (s + 1);
	n = strlen(s + 1);
	
	int p1 = 1;
	int p2 = -1;
	if(s[1] == 'a') {
		p1 = 1;
		
		if(s[n] == 'a') {
			cout << s[1] << " ";
			for(int i = 2; i < n; i++) cout << s[i];
			cout << " " << s[n] << endl;
		} else {
			int pos = -1;
			for(int i = 2; i < n; i++) {
				if(s[i] == 'b') {
					pos = i;
					break;
				}
			}
			if(pos == -1) {
				cout << ":(" << endl;
				return;
			}
			
			for(int i = 1; i < pos; i++) cout << s[i];
			cout << " ";
			for(int i = pos; i < n; i++) cout << s[i];
			cout << " " << s[n] << endl;
		}
		return;
	} else {
		for(p1 = 2; s[p1] == 'a' && p1 <= n; p1++);
		p1--;
	}
	if(p1 > n) {
		cout << ":(" << endl;
		return;
	}
	
	// a: [1, p1]
	
	int i;
	for(i = 1; i <= p1 && p1 + i <= n; i++) {
		if(s[i] < s[p1 + i]) {
			p2 = p1 + i;
			break;
		} else if(s[i] > s[p1 + i]) {
			assert(false);
		}
	}
	if(p1 + i > n) {
		cout << ":(" << endl;
		return;
	}
	if(i > p1) {
		p2 = p1 + p1;
	}
	
	if(p2 >= n) {
		cout << ":(" << endl;
		return;
	}
	
	// b: [p1 + 1, p2...]
	
	for(i = 1; i <= p1; i++) cout << s[i];
	cout << " ";
	for(; i < n; i++) cout << s[i];
	cout << " " << s[n] << endl;
	
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
