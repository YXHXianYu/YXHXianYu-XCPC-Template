#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;

map<char, int> f;

int n;
int cnt[10];
int m;

void work() {

    for(int i = 0; i <= 5; i++) {
        cnt[i] = 0;
    }

    cin >> n;
    char s[20] = {};
    for(int i = 1; i <= n; i++) {
        cin >> s;
        cnt[f[s[0]]] += 1;
    }
    cin >> m;
    for(int i = 1; i <= m; i++) {
        cin >> s;
        int len = strlen(s);
        for(int j = 0; j < len; j++) {
            cnt[f[s[j]]] -= 1;
        }
    }

    for(int i = 1; i <= 5; i++) {
        if(cnt[i] < 0) {
            cout << "NO" << endl;
            return;
        }
    }
    for(int i = 1; i <= 5; i++) {
        cnt[0] += cnt[i];
    }
    if(cnt[0] < 0) {
        cout << "NO" << endl;
        return;
    } else {
        cout << "YES" << endl;
        return;
    }

}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

    f['W'] = 1;
    f['U'] = 2;
    f['B'] = 3;
    f['G'] = 4;
    f['R'] = 5;
    f['O'] = 0;
    
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}
