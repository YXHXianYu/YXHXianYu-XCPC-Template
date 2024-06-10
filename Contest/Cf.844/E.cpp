#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

int n;

struct Rect {
	int u;
	int d;
	int l;
	int r;
} a[maxn];

int h2[maxn];
int hup[maxn];
int hdown[maxn];

bool comp(int x, int y) {
	if(a[x].l != a[y].l) return a[x].l < a[y].l;
	if(a[x].r != a[y].r) return a[x].r < a[y].r;
	return false;
}

bool rectEmpty(int idx) {
	return a[idx].u == 0;
}

void setEmpty(int idx) {
//	cout << " set empty: " << idx << endl;
	a[idx].u = a[idx].d = a[idx].l = a[idx].r = 0;
}

int getS(int i) {
	return (a[i].r - a[i].l + 1) * (a[i].d - a[i].u + 1);
}

void work() {
	
	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i].u >> a[i].l >> a[i].d >> a[i].r;
	
	int N2 = 0;
	int Nup = 0;
	int Ndown = 0;
	
	for(int i = 1; i <= n; i++) {
		if(a[i].u == 1 && a[i].d == 2) {
			h2[++N2] = i;
		} else if(a[i].u == 1) {
			hup[++Nup] = i;
		} else {
			hdown[++Ndown] = i;
		}
	}
	
	sort(h2 + 1, h2 + N2 + 1, comp);
	sort(hup + 1, hup + Nup + 1, comp);
	sort(hdown + 1, hdown + Ndown + 1, comp);
	
//	cout << " N2 = " << N2 << endl;
//	for(int i = 1; i <= N2; i++) cout << h2[i] << " ";
//	cout << endl;
//	cout << " Nup = " << Nup << endl;
//	for(int i = 1; i <= Nup; i++) cout << hup[i] << " ";
//	cout << endl;
//	cout << " Ndown = " << Ndown << endl;
//	for(int i = 1; i <= Ndown; i++) cout << hdown[i] << " ";
//	cout << endl;
	
	int lst = h2[1];
	int cur;
	for(int i = 2; i <= N2; i++) {
		cur = h2[i];
		
		if(a[lst].r >= a[cur].r) { // remove
//			cout << "!";
			setEmpty(cur);
		} else if(a[lst].r >= a[cur].l) { // shorter
			a[cur].l = a[lst].r + 1;
			lst = cur;
		} else {
			lst = cur;
		}
	}
	
	lst = hup[1];
	for(int i = 2; i <= Nup; i++) {
		cur = hup[i];
		
		if(a[lst].r >= a[cur].r) { // remove
			setEmpty(cur);
		} else if(a[lst].r >= a[cur].l) { // shorter
			a[cur].l = a[lst].r + 1;
			lst = cur;
		} else {
			lst = cur;
		}
	}
	
	lst = hdown[1];
	for(int i = 2; i <= Ndown; i++) {
		cur = hdown[i];
		
		if(a[lst].r >= a[cur].r) { // remove
			setEmpty(cur);
		} else if(a[lst].r >= a[cur].l) { // shorter
			a[cur].l = a[lst].r + 1;
			lst = cur;
		} else {
			lst = cur;
		}
	}
	

	
//	cout << " N2 = " << N2 << endl;
//	for(int i = 1; i <= N2; i++) cout << "(" << a[h2[i]].l << ", " << a[h2[i]].r << ")";
//	cout << endl;
//	cout << " Nup = " << Nup << endl;
//	for(int i = 1; i <= Nup; i++) cout << "(" << a[hup[i]].l << ", " << a[hup[i]].r << ")";
//	cout << endl;
//	cout << " Ndown = " << Ndown << endl;
//	for(int i = 1; i <= Ndown; i++) cout << "(" << a[hdown[i]].l << ", " << a[hdown[i]].r << ")";
//	cout << endl;
	
	int pup = 1;
	int pdown = 1;
	for(int i = 1; i <= N2; i++) {
		int p2 = h2[i];
		
		if(rectEmpty(p2)) continue;
		
		while((rectEmpty(hup[pup]) || a[hup[pup]].r < a[p2].l) && pup <= Nup) pup++;
		while((rectEmpty(hdown[pdown]) || a[hdown[pdown]].r < a[p2].l) && pdown <= Ndown) pdown++;
		
		while(true) {
			
//			cout << " - " << p2 << ", " << hup[pup] << ", " << hdown[pdown] << endl;
			
			if(pup <= Nup && pdown <= Ndown) { // both
				if(a[p2].l <= a[hup[pup]].l && a[hup[pup]].r <= a[p2].r) { // 包含 
					setEmpty(hup[pup]);
					pup++;
					continue;
				} else if(a[hup[pup]].l < a[p2].l && a[hup[pup]].r <= a[p2].r) { // up左边突出去 
					a[hup[pup]].r = min(a[hup[pup]].r, a[p2].l - 1);
					pup++;
					continue;
				}
				if(a[p2].l <= a[hdown[pdown]].l && a[hdown[pdown]].r <= a[p2].r) { // 包含 
					setEmpty(hdown[pdown]);
					pdown++;
					continue;
				} else if(a[hdown[pdown]].l < a[p2].l && a[hdown[pdown]].r <= a[p2].r) { // down左边突出去 
					a[hdown[pdown]].r = min(a[hdown[pdown]].r, a[p2].l - 1);
					pdown++;
					continue;
				}
				
				if(a[hup[pup]].l < a[p2].l && a[hdown[pdown]].l < a[p2].l) { // up & down 穿过去了 
//					cout << "?";
					setEmpty(p2);
				} else if(a[hup[pup]].l < a[p2].l) { // up穿过去了 
					a[hdown[pdown]].l = max(a[hdown[pdown]].l, a[p2].r + 1);
					a[p2].u = 2;
				} else if(a[hdown[pdown]].l < a[p2].l) { // down穿过去了 
					a[hup[pup]].l = max(a[hup[pup]].l, a[p2].r + 1);
					a[p2].d = 1;
				} else {
					a[hup[pup]].l = max(a[hup[pup]].l, a[p2].r + 1);
					a[hdown[pdown]].l = max(a[hdown[pdown]].l, a[p2].r + 1);
				}
				break;
			} else if(pup <= Nup && pdown > Ndown) { // only up
				if(a[p2].l <= a[hup[pup]].l && a[hup[pup]].r <= a[p2].r) { // 包含 
					setEmpty(hup[pup]);
					pup++;
					continue;
				} else if(a[hup[pup]].l < a[p2].l && a[hup[pup]].r <= a[p2].r) { // up左边突出去 
					a[hup[pup]].r = min(a[hup[pup]].r, a[p2].l - 1);
					pup++;
					continue;
				} else if(/* a[p2].r < a[hup[pup]].r && */ a[p2].l <= a[hup[pup]].l) { // up右边突出去 
					a[hup[pup]].l = max(a[hup[pup]].l, a[p2].r + 1);
				} else if(/* a[p2].r < a[hup[pup]].r && */ a[hup[pup]].l < a[p2].l) { // up穿过去了 
					a[p2].u = 2;
				}
				break;
			} else if(pup > Nup && pdown <= Ndown) { // only down
				if(a[p2].l <= a[hdown[pdown]].l && a[hdown[pdown]].r <= a[p2].r) { // 包含 
					setEmpty(hdown[pdown]);
					pdown++;
					continue;
				} else if(a[hdown[pdown]].l < a[p2].l && a[hdown[pdown]].r <= a[p2].r) { // down左边突出去 
					a[hdown[pdown]].r = min(a[hdown[pdown]].r, a[p2].l - 1);
					pdown++;
					continue;
				} else if(/* a[p2].r < a[hdown[pdown]].r && */ a[p2].l <= a[hdown[pdown]].l) { // down右边突出去 
					a[hdown[pdown]].l = max(a[hdown[pdown]].l, a[p2].r + 1);
				} else if(/* a[p2].r < a[hdown[pdown]].r && */ a[hdown[pdown]].l < a[p2].l) { // down穿过去了 
					a[p2].d = 1;
				}
				break;
			} else if(pup > Nup && pdown > Ndown) {
				break;
			} else {
				assert(false);
			}
		}
		
		// 处理掉所有r <= a[p2].r的1格 
	}
	
	int ans = 0;
	for(int i = 1; i <= n; i++) {
		if(rectEmpty(i)) continue;
		ans += getS(i);
	}
	cout << ans << endl;
	for(int i = 1; i <= n; i++) {
		cout << a[i].u << " " << a[i].l << " " << a[i].d << " " << a[i].r << endl;
	}
//	cout << endl;
	
	
	
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
