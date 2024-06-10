#include<bits/stdc++.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS 1

const int M = 2e5;

#define LC (x << 1)
#define RC (x << 1 | 1)
const int INF = 1e9;

namespace mxst {
    int st[M * 4];
    int lim = M;
    void upd(int n, int p, int l, int r, int cur) {
        if(p < l || p > r) return;
        if(l == r) {
            st[cur] = n;
            return;
        }
        int mid = (l + r) / 2;
        upd(n, p, l, mid, cur * 2);
        upd(n, p, mid + 1, r, cur * 2 + 1);
        st[cur] = max(st[cur * 2], st[cur * 2 + 1]);
    }
    void upd(int n, int p) {
        upd(n, p, 0, lim, 1);
    }
    int query(int ql, int qr, int l, int r, int cur) {
        if(qr < l || ql > r) return 0;
        if(ql <= l && qr >= r) return st[cur];
        int mid = (l + r) / 2;
        return max(query(ql, qr, l, mid, cur * 2), query(ql, qr, mid + 1, r, cur * 2 + 1));
    }
    int query(int l, int r) {
        return query(l, r, 0, lim, 1);
    }
    void clear() {
        memset(st, 0, sizeof(int) * (lim * 4));
    }
    int queryMaxLeft(int x, int l, int r, int p, int va) {
		if(p <= l) return -INF;
    	if(st[x] <= va) return -INF;
    	
		if(l == r) return l;
		
		int mid = l + r >> 1;
		
		if(r < p) {
			if(st[RC] > va)
				return queryMaxLeft(RC, mid+1, r, p, va);
			else
				return queryMaxLeft(LC, l, mid, p, va);
		} else {
			if(p <= mid) return queryMaxLeft(LC, l, mid, p, va);
			else { // mid < p
				int v = queryMaxLeft(RC, mid+1, r, p, va);
				if(v == -INF) return queryMaxLeft(LC, l, mid, p, va);
				else return v;
			}
		}
	}
	
	int queryMaxRight(int x, int l, int r, int p, int va) { // type==0,left; type==1,right;
//		cout << " - " << x << ", " << l << ", " << r << endl;
    	if(r <= p) return INF;
    	if(st[x] <= va) return INF;
    	
		if(l == r) return l;
		
		int mid = l + r >> 1;
		
		if(p < l) {
//			cout << " ----- " << st[LC] << ", " << va << endl;
			if(st[LC] > va)
				return queryMaxRight(LC, l, mid, p, va);
			else
				return queryMaxRight(RC, mid+1, r, p, va);
		} else {
			if(mid <= p) {
//				cout << "!" << endl;
				return queryMaxRight(RC, mid+1, r, p, va);
			} else { // p < mid
				int v = queryMaxRight(LC, l, mid, p, va);
				if(v == INF) return queryMaxRight(RC, mid+1, r, p, va);
				else return v;
			}
		}
	}
}

namespace cntst {
    int st[M * 4];
    int lim = M;
    void upd(int p, int l, int r, int cur) {
        if(p < l || p > r) return;
        if(l == r) {
            st[cur] = 1;
            return;
        }
        int mid = (l + r) / 2;
        upd(p, l, mid, cur * 2);
        upd(p, mid + 1, r, cur * 2 + 1);
        st[cur] = st[cur * 2] + st[cur * 2 + 1];
    }
    void upd(int p) {
        upd(p, 0, lim, 1);
    }
    int query(int ql, int qr, int l, int r, int cur) {
        if(r < ql || l > qr) return 0;
        if(ql <= l && qr >= r) return st[cur];
        int mid = (l + r) / 2;
        return query(ql, qr, l, mid, cur * 2) + query(ql, qr, mid + 1, r, cur * 2 + 1);
    }
    int query(int l, int r) {
        return query(l, r, 0, lim, 1);
    }
    void clear() {
        memset(st, 0, sizeof(int) * (lim * 4));
    }
}
int a[M + 1], b[M + 1];
map<int, int> l;
bool mark[M + 1];

int findRight(int p, int n) {
    int v = mxst::queryMaxRight(1, 0, mxst::lim, p, a[p]);
    return min(n - 1, v - 1);
}

int findLeft(int p, int n) {
	int v = mxst::queryMaxLeft(1, 0, mxst::lim, p, a[p]);
	return max(0, v + 1);
}

pair<int, int> pr[M + 1];

int main() {
    int t;
    cin >> t;
    int n, m, k;
    int la;
    while(t--) {
        scanf("%d%d%d", &n, &m, &k);
        mxst::lim = cntst::lim = n;
        mxst::clear();
        cntst::clear();
        l.clear();
        memset(mark, 0, sizeof(bool) * (n + 1));
        bool ans = true;
        for(int i = 0; i < n; i++) {
            scanf("%d", a + i);
            mxst::upd(a[i], i);
        }
        
//        for(int i = 0; i < n; i++) {
//        	cout << i << ": " << mxst::query(i, i) << endl;
//		}
        
//        cout << mxst::queryMaxLeft(1, 0, mxst::lim, 0, 5) << endl;
//        cout << mxst::queryMaxLeft(1, 0, mxst::lim, 1, 1) << endl;
//        cout << mxst::queryMaxLeft(1, 0, mxst::lim, 2, 3) << endl;
//        cout << mxst::queryMaxLeft(1, 0, mxst::lim, 3, 2) << endl;
//        cout << mxst::queryMaxLeft(1, 0, mxst::lim, 4, 4) << endl;
//        cout << endl;
//        cout << mxst::queryMaxRight(1, 0, mxst::lim, 0, 5) << endl;
//        cout << mxst::queryMaxRight(1, 0, mxst::lim, 1, 1) << endl;
//        cout << mxst::queryMaxRight(1, 0, mxst::lim, 2, 3) << endl;
//        cout << mxst::queryMaxRight(1, 0, mxst::lim, 3, 2) << endl;
//        cout << mxst::queryMaxRight(1, 0, mxst::lim, 4, 4) << endl;
//        cout << endl;
        
        for(int i = 0; i < m; i++) {
            scanf("%d", b + i);
            mark[b[i]] = true;
        }
        for(int i = 0; i < k; i++) {
            scanf("%d", &la);
            l[la]++;
        }
        if(m + k < n) {
            puts("NO");
            continue;
        }
        int idx = 0;
        for(int i = 0; i < m && idx < n; i++) {
            for(; idx < n && a[idx] != b[i]; idx++);
            if(idx == n) {
                ans = false;
                break;
            }
        }
        idx = 0;
        if(!ans) {
            puts("NO");
            continue;
        }
        for(int i = 0; i < n; i++) {
            if(!mark[a[i]]) {
                pr[idx++] = {a[i], i};
            }
        }
        sort(pr, pr + idx);
        for(int i = idx - 1; i > -1; i--) {
            int p = pr[i].second;
            int lb = findLeft(p, n);
            int rb = findRight(p, n);
            int removed = cntst::query(lb, rb);
            int len = rb - lb + 1 - removed;
            auto it = l.upper_bound(len);
            if(it == l.begin()) {
                ans = false;
                break;
            }
            it--;
            it->second--;
            if(it->second == 0) {
                l.erase(it);
            }
            cntst::upd(p);
            mxst::upd(-1, p);
        }
        if(ans) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}
