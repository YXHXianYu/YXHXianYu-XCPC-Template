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

int EFtag = 0;
int E[maxn];

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
	
	if(cnt == 1) {
		cout << l << endl;
		return;
	}
	
	if(A[cnt] + 2 <= B[cnt]) {
		for(int i = 1; i <= cnt; i++) {
			cout << A[cnt] + 1;
		}
		cout << endl;
		return;
	}
	
	if(A[cnt] + 1 == B[cnt]) {
		int va1 = 0;
		int mx = A[cnt];
		int mn = A[cnt];
		
		C[cnt] = A[cnt];
		for(int i = cnt - 1; i >= 1; i--) {
			if(A[i] >= mx) {
				C[i] = A[i];
				mx = A[i];
			} else {
				for(int j = i; j >= 1; j--) C[j] = mx;
				break;
			}
		}
		va1 = mx - mn;
		
		mx = mn = B[cnt];
		D[cnt] = B[cnt];
		for(int i = cnt - 1; i >= 1; i--) {
			if(B[i] <= mn) {
				D[i] = B[i];
				mn = B[i];
			} else {
				for(int j = i; j >= 1; j--) D[j] = mn;
				break;
			}
		}
		int va2 = mx - mn;
		
		int ansv = 10;
		for(int i = 1; i <= 99; i++) {
			int x = i / 10;
			int y = i % 10;
			if(x < A[cnt] || x > B[cnt]) continue;
			if(x == A[cnt] && y <= A[cnt - 1]) continue;
			if(x == B[cnt] && y >= B[cnt - 1]) continue;
			
			int mx = max(x, y);
			int mn = min(x, y);
			if(mx - mn < ansv) {
				ansv = mx - mn;
				E[cnt] = x;
				for(int j = cnt - 1; j >= 1; j--) E[j] = y;
			}
		}
		
		if(ansv <= va1 && ansv <= va2) {
			for(int i = cnt; i >= 1; i--) cout << E[i]; cout << endl;
		} else if(va1 <= va2) {
			for(int i = cnt; i >= 1; i--) cout << C[i]; cout << endl;
		} else {
			for(int i = cnt; i >= 1; i--) cout << D[i]; cout << endl;
		}
		
		return;
	}
	
	int lim = cnt;
	while(A[lim] == B[lim] && lim >= 1) {
		lim -= 1;
	}
	
	for(int i = cnt; i > lim; i--) C[i] = D[i] = A[i];
	
	int mx0 = A[cnt];
	int mn0 = A[cnt];
	for(int i = cnt - 1; i > lim; i--) {
		mx0 = max(mx0, A[i]);
		mn0 = min(mn0, A[i]);
	}
	
	int ansEF = 10;
	EFtag = false;
	if(A[lim] + 2 <= B[lim]) {
		int ans = 0;
		int ansv = 10;
		EFtag = true;
		for(int i = A[lim] + 1; i < B[lim]; i++) {
			int mx = max(mx0, i);
			int mn = min(mn0, i);
			if(mx - mn < ansv) {
				ans = i;
				ansv = mx - mn;
			}
		}
		for(int i = cnt; i > lim; i--) E[i] = A[i];
		for(int i = lim; i >= 1; i--) E[i] = ans;
		ansEF = ansv;
	}
	
	int va1 = 0, va2 = 0;
	int mx = max(mx0, A[lim]);
	int mn = min(mn0, A[lim]);
	
	C[lim] = A[lim];
	for(int i = lim - 1; i >= 1; i--) {
		if(A[i] >= mx) {
//			cout << "!" << i << endl;
			C[i] = A[i];
			mx = A[i];
		} else {
			for(int j = i; j >= 1; j--) {
				C[j] = mx;
			}
			break;
		}
	}
	va1 = mx - mn;
	
	mx = max(mx0, B[lim]);
	mn = min(mn0, B[lim]);
	
	D[lim] = B[lim];
	for(int i = lim - 1; i >= 1; i--) {
		if(B[i] <= mn) {
			D[i] = B[i];
			mn = B[i];
		} else {
			for(int j = i; j >= 1; j--) {
				D[j] = mn;
			}
			break;
		}
	}
	va2 = mx - mn;
	
//	cout << " va = " << va1 << ", " << va2 << "(" << mx << ", " << mn << ")" << " - " << mx0 << ", " << mn0 << endl;
	
	if(EFtag == true && ansEF <= va1 && ansEF <= va2) {
		for(int i = cnt; i >= 1; i--) cout << E[i]; cout << endl;
	} else if(va1 <= va2) {
		for(int i = cnt; i >= 1; i--) cout << C[i]; cout << endl;
	} else {
		for(int i = cnt; i >= 1; i--) cout << D[i]; cout << endl;	
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
