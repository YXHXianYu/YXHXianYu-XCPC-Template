#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 50 + 10;

int n;
int a[maxn][maxn];
int b[maxn * maxn];

void work() {
	
	cin >> n;
	
	int cnt = 0;
	int p = 0;
	for(int i = 1, j = n * n; i <= j; i++, j--) {
		b[++cnt] = i;
		if(i == j) break;
		b[++cnt] = j;
	}
	
	assert(cnt == n * n);
	
	cnt = 0;
	int j = 1;
	for(int i = 1; i <= n;) {
		a[i][j] = b[++cnt];
		if((i&1)) {
			if(j == n) {
				i++;
			} else {
				j++;
			}
		} else {
			if(j == 1) {
				i++;
			} else {
				j--;
			}
		}
	}
	
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			cout << a[i][j] << " ";
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
