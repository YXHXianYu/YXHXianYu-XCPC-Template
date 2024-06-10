/**
 * Created by YXH_XianYu on 2023.8.31
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


void work() {
	int n, m;
	cin >> n >> m;

	string s;
	cin >> s;
	s = " " + s;

	// int B = sqrt(1e5);
	int B = 500;
	// int B = 1;
	int N = (B - 1) / n + 1;
	vector<int> L(N + 1), R(N + 1), id(n + 1);
	for(int i = 1; i <= n; i++) {
		id[i] = (i - 1) / n + 1;
		if(L[id[i]] == 0) L[id[i]] = i;
		R[id[i]] = i;
	}

	vector<int> len(n + 1); // for element
	vector<array<int, 3>> mx(N + 1); // for block

	for(int i = 1; i <= N; i++) {
		for(int j = L[i]; j <= R[i]; j++) {
			if(j == L[i] || s[j - 1] != s[j]) {
				len[j] = 1;
			} else {
				int L = j-len[j-1];
				int R = j-1;
				len[L] = (R-L+1) + 1;
				len[j] = (R-L+1) + 1;
			}
			if(len[j] > mx[i][0]) {
				mx[i][0] = len[j];
				mx[i][2] = j;
				mx[i][1] = j - len[j] + 1;
			}
		}
	}

	for(int i = 1; i <= m; i++) {
		int opt;
		cin >> opt;

		if(opt == 1) {
			int l, r;
			cin >> l >> r;

			array<int, 3> ans{};

			if(id[l] == id[r]) {
				
				int cnt = 0;
				for(int j = l; j <= r; j++) {
					if(j == l || s[j - 1] != s[j]) {
						cnt = 1;
					} else {
						cnt += 1;
					}
					if(cnt > ans[0]) {
						ans[0] = cnt;
						ans[2] = j;
						ans[1] = j - cnt + 1;
					}
				}
				cout << ans[1] << " " << ans[2] << endl;

			} else {

				int cntL = 0;
				for(int j = l; j <= R[id[l]]; j++) {
					if(j == l || s[j - 1] != s[j]) {
						cntL = 1;
					} else {
						cntL += 1;
					}
					if(cntL > ans[0]) {
						ans[0] = cntL;
						ans[2] = j;
						ans[1] = j - cntL + 1;
					}
				}
				if(R[id[l]] != n && s[R[id[l]]] == s[R[id[l]] + 1]) {
					int tmpL = R[id[l]] - cntL + 1;
					int tmpR = min(r, R[id[l]]+1 + len[R[id[l]] + 1] - 1);
					if(tmpR-tmpL+1 > ans[0]) {
						ans[0] = tmpR-tmpL+1;
						ans[1] = tmpL;
						ans[2] = tmpR;
					}
				}

				int cntR = 0;
				for(int j = r; j >= L[id[r]]; j--) {
					if(j == r || s[j + 1] != s[j]) {
						cntR = 1;
					} else {
						cntR += 1;
					}
					if(cntR > ans[0]) {
						ans[0] = cntR;
						ans[1] = j;
						ans[2] = j + cntR - 1;
					}
				}
				if(L[id[r]] != 1 && s[L[id[r]]] == s[L[id[r]] - 1]) {
					int tmpL = max(l, L[id[r]]-1 - len[L[id[r]] - 1] - 1);
					int tmpR = L[id[r]] + cntR - 1;
					if(tmpR-tmpL+1 > ans[0]) {
						ans[0] = tmpR-tmpL+1;
						ans[1] = tmpL;
						ans[2] = tmpR;
					}
				}

				array<int, 3> cntmid;
				cntmid[0] = len[R[id[l]]];
				cntmid[2] = R[id[l]];
				cntmid[1] = cntmid[2] - cntmid[0] + 1;

				for(int j = id[l] + 1; j <= id[r]; j++) {
					if(j > id[l] && j < id[r] && mx[j][0] > ans[0]) {
						ans = mx[j];
					}
					
					if(s[R[id[j-1]]] == s[L[id[j]]]) {
						cntmid[0] += len[L[id[j]]];
						cntmid[2] = min(r, cntmid[1] + cntmid[0] - 1);

						if(cntmid[0] > ans[0]) {
							ans = cntmid;
						}

						if(len[L[id[j]]] != (R[id[j]] - L[id[j]] + 1)) {
							cntmid[0] = len[R[id[j]]];
							cntmid[1] = R[id[j]] - len[R[id[j]]] + 1;
							cntmid[2] = R[id[j]];
						}

					} else {
						cntmid[0] = len[R[id[j]]];
						cntmid[1] = R[id[j]] - len[R[id[j]]] + 1;
						cntmid[2] = R[id[j]];
					}
				}
				
				cout << ans[1] << " " << ans[2] << endl;
			}

		} else if(opt == 2) {
			int x; char ch;
			cin >> x >> ch;

			s[x] = ch;

			mx[id[x]][0] = 0;
			for(int j = L[id[x]]; j <= R[id[x]]; j++) len[j] = 0;

			for(int j = L[id[x]]; j <= R[id[x]]; j++) {
				if(j == L[id[x]] || s[j - 1] != s[j]) {
					len[j] = 1;
				} else {
					int L = j-len[j-1];
					int R = j-1;
					len[L] = (R-L+1) + 1;
					len[j] = (R-L+1) + 1;
				}
				if(len[j] > mx[id[x]][0]) {
					mx[id[x]][0] = len[j];
					mx[id[x]][2] = j;
					mx[id[x]][1] = j - len[j] + 1;
				}
			}

		} else assert(false);
	}
	
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