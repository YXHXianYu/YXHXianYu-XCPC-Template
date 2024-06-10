#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 100 + 10;

int l, r;

int getV(int x) {
	int mx = 0;
	int mn = 9;
	while(x) {
		mx = max(mx, x % 10);
		mn = min(mn, x % 10);
		x /= 10;
	}
	return mx - mn;
}

int getD(int x) {
	int cnt = 0;
	while(x) {
		cnt += 1;
		x /= 10;
	}
	return cnt;
}

int A[maxn];
int B[maxn];

int C[maxn];
int D[maxn];

void work() {
	
	cin >> l >> r;
	
	if(l == r) {
		cout << l << endl;
		return;
	}
	
	int dL = getD(l);
	int dR = getD(r);
	
	if(dL < dR) {
		int cnt = 1;
		for(int i = 1; i < dR; i += 1) cnt *= 10;
		cout << cnt - 1 << endl;
		return;
	}
	
	int cnt = 0;
	int x = l;
	while(x) {
		A[++cnt] = x % 10;
		x /= 10;
	}
	cnt = 0;
	x = r;
	while(x) {
		B[++cnt] = x % 10;
		x /= 10;
	}
	
	int lim = cnt;
	while(A[lim] == B[lim] && lim >= 1) {
		lim--;
	}
	
	int mx0 = -1;
	int mn0 = 10;
	for(int i = cnt; i > lim; i--) {
		mx0 = max(mx0, A[i]);
		mn0 = min(mn0, A[i]);
	}
	int mx, mn;
	
	int ansv = 10;
	for(int i = cnt; i > lim; i--) C[i] = A[i];
	
	if(lim == 1) {
		for(int i = 1; i <= 9; i++) {
			if(i < A[lim]) continue;
			if(i > B[lim]) continue;
			mx = max(mx0, i);
			mn = min(mn0, i);
			if(mx - mn < ansv) {
				ansv = mx - mn;
				C[lim] = i;
			}
		}
	} else {
		for(int i = 1; i <= 99; i++) {
			int x = i / 10;
			int y = i % 10;
			if(x < A[lim] || x > B[lim]) continue;
			if(x == A[lim] && y <= A[lim-1]) continue;
			if(x == B[lim] && y >= B[lim-1]) continue;
			mx = max(mx0, max(x, y));
			mn = min(mn0, min(x, y));
			if(mx - mn < ansv) {
				ansv = mx - mn;
				C[lim] = x;
				for(int j = lim-1; j >= 1; j--) C[j] = y;
			}
		}
		int x, y;
		
		x = A[lim];
		y = A[lim-1];
		mx = max(mx0, max(x, y));
		mn = min(mn0, min(x, y));
		for(int j = lim-2; j >= 1; j--) {
			if(A[j] >= mx) {
				mx = A[j];
				D[j] = A[j];
			} else {
				for(int k = j; k >= 1; k--) D[k] = mx;
				break;
			}
		}
		if(mx - mn < ansv) {
			ansv = mx - mn;
			C[lim] = x;
			C[lim-1] = y;
			for(int j = lim-2; j >= 1; j--) C[j] = D[j];
		}
		
		x = B[lim];
		y = B[lim-1];
		mx = max(mx0, max(x, y));
		mn = min(mn0, min(x, y));
		for(int j = lim-2; j >= 1; j--) {
			if(B[j] <= mn) {
				mn = B[j];
				D[j] = B[j];
			} else {
				for(int k = j; k >= 1; k--) D[k] = mn;
				break;
			}
		}
		if(mx - mn < ansv) {
			ansv = mx - mn;
			C[lim] = x;
			C[lim-1] = y;
			for(int j = lim-2; j >= 1; j--) C[j] = D[j];
		}
		
	}
	
	// output
	for(int j = cnt; j >= 1; j--) cout << C[j]; cout << endl;
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
