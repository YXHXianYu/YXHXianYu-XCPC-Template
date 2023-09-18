#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 10;
const int maxlog = 20;

int n;
int a[maxn];

pair<int, int> st[20][maxn];

void buildST() {
	int lim = log2(n);
	for(int i = 1; i <= n; i++) st[0][i] = {a[i], i};
	for(int j = 1; j <= lim; j++) {
		for(int i = 1, lim2 = n - (1 << j) + 1; i <= lim2; i++) {
			st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
		}
	}
}

int queryST(int l, int r) {
	int k = log2(r - l + 1);
	return (max(st[k][l], st[k][r - (1 << k) + 1])).second;
}

int pre[maxn];

int rt[maxn]; // root[i]: the trie's root of i-th element
int trie[60 * maxn][2];
int tot;
int newNode() {
	tot++;
	trie[tot][0] = trie[tot][1] = 0;
	return tot;
}
void insert(int root, int va) {
	int p = root;
	for(int k = 30; k >= 0; k--) {
		int e = (va & (1 << k)) > 0;
		
		if(trie[p][e] == 0) {
			trie[p][e] = newNode();
//			cout << "trie: " << p << " --" << e << "--> " << trie[p][e] << endl;
		}
		p = trie[p][e];
	}
}

int query(int root, int va) {
	int ans = 0;
	int p = root;
	for(int k = 30; k >= 0; k--) {
		int e = (va & (1 << k)) > 0;
		
//		cout << "quey: " << p << " --" << e << "--> " << endl;
		
		if(trie[p][e ^ 1]) {
			ans ^= 1 << k;
			p = trie[p][e ^ 1];
		} else if(trie[p][e]) {
			p = trie[p][e];
		} else { // trie中不存在一个完整的数 
//			return 0;
			if(k == 30) return 0;
			assert(false);
		}
	}
	return ans;
}

int mergeTrie(int x, int y) {
	if(!x || !y) return x + y;
	trie[x][0] = mergeTrie(trie[x][0], trie[y][0]);
	trie[x][1] = mergeTrie(trie[x][1], trie[y][1]);
	return x;
}

int ans;

void solve(int l, int r) {
	if(l >= r) return;
	
	int mxPos = queryST(l, r);
	
//	cout << " - " << l << ", " << r << ": " << mxPos << endl;
	
	solve(l, mxPos - 1);
	solve(mxPos + 1, r);
	
	if(mxPos == l) {
//		cout << " - - " << query(rt[mxPos + 1], pre[mxPos]) << ", " << pre[mxPos] << endl;
		
		ans = max(ans, query(rt[mxPos + 1], pre[mxPos])); // [mxPos, mxPos+1 ~ r]
		
		rt[l] = mergeTrie(rt[mxPos + 1], rt[mxPos]);
		
	} else if(mxPos == r) {
//		cout << " - - " << query(rt[l], pre[mxPos - 1]) << ", " << pre[mxPos - 1] << endl;
		
		ans = max(ans, pre[l - 1] ^ pre[mxPos - 1]);  // [l, mxPos]
		ans = max(ans, query(rt[l], pre[mxPos - 1])); // [l+1 ~ mxPos-1, mxPos]
		
		rt[l] = mergeTrie(rt[l], rt[mxPos]);
		
	} else if(mxPos - l <= r - mxPos) { // left part is smaller (use right part's trie)
		// calculate ans
//		cout << " - - " << query(rt[mxPos + 1], pre[mxPos]) << ", " << pre[mxPos] << endl;
		
		ans = max(ans, query(rt[mxPos + 1], pre[mxPos]));
		for(int i = l; i < mxPos; i++) {
			ans = max(ans, pre[mxPos - 1] ^ pre[i - 1]);                 // [i, mxPos]
			ans = max(ans, query(rt[mxPos + 1], a[mxPos] ^ pre[i - 1])); // [i, mxPos+1 ~ r]
		}
		
		// merge trie (左侧Trie合并到右侧Trie) 
		rt[mxPos + 1] = mergeTrie(rt[mxPos + 1], rt[l]);
		rt[l] = mergeTrie(rt[mxPos + 1], rt[mxPos]);
		
	} else {                     // right part is smaller (use left part's trie)
		// calculate ans
//		cout << " - - " << query(rt[l], pre[l - 1]) << ", " << pre[l - 1] << endl;
		
		for(int i = mxPos; i <= r; i++) {
			ans = max(ans, pre[i] ^ pre[mxPos]);             // [mxPos, i]
			ans = max(ans, pre[l - 1] ^ pre[i] ^ a[mxPos]);  // [l, i]
			ans = max(ans, query(rt[l], pre[i] ^ a[mxPos])); // [l+1 ~ mxPos-1, i]
		}
		
		// merge trie (右侧Trie合并到左侧Trie) 
		rt[l] = mergeTrie(rt[l], rt[mxPos + 1]);
		rt[l] = mergeTrie(rt[l], rt[mxPos]);
	}
	// 上层递归只会用到本层的rt[l] 
//	cout << " - exit" << endl;
}

void work() {

	cin >> n;
	for(int i = 1; i <= n; i++) cin >> a[i];
	
	buildST();
	
	for(int i = 1; i <= n; i++) pre[i] = pre[i - 1] ^ a[i];
	
	tot = -1;
	newNode();
	
	for(int i = 1; i <= n; i++) {
		rt[i] = newNode();
		insert(rt[i], pre[i]);
	}
	
	ans = 0;
	solve(1, n);
	cout << ans << endl;
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
