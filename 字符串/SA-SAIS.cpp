#include<bits/stdc++.h>
using namespace std;
// #define int long long

struct SA{
    static const int MAX_LEN=1e6+5;
    static const int SIGMA=128;
	int str[MAX_LEN<<1];
	int type[MAX_LEN<<1];
	int LMS[MAX_LEN<<1];
	int sa[MAX_LEN];
	int rank[MAX_LEN];
	int cnt[MAX_LEN];
	int cur[MAX_LEN];
	void inducedsort(int *str,int len,int sigma,int *LMS,int LMSC,int *type){
		#define PUSH_S(x) (sa[cur[str[x]]--] = x)
		#define PUSH_L(x) (sa[cur[str[x]]++] = x)
		memset(sa,-1,sizeof(int)*(len+2));memset(cnt,0,sizeof(int)*(sigma+2));
		for(int i=0;i<len;i++)++cnt[str[i]];
		for(int i=1;i<sigma;i++)cnt[i]+=cnt[i-1];
		for(int i=0;i<sigma;i++)cur[i]=cnt[i]-1;
		for(int i=LMSC-1;i>=0;--i)PUSH_S(LMS[i]);
		for(int i=1;i<sigma;i++)cur[i]=cnt[i-1];
		for(int i=0;i<len;i++)sa[i]>0&&type[sa[i]-1]==0&&PUSH_L(sa[i]-1);
		for(int i=0;i<sigma;i++)cur[i]=cnt[i]-1;
		for(int i=len-1;i>=0;--i)sa[i]>0&&type[sa[i]-1]&&PUSH_S(sa[i]-1);
		#undef PUSH_S
		#undef PUSH_L
	}
	void sais(int *str,int len,int sigma,int *LMS,int *type){
		type[len-1]=1;
		for(int i=len-2;i>=0;--i)type[i]=(str[i]==str[i+1]?type[i+1]:str[i]<str[i+1]);
		int LMSC=0;
		rank[0]=-1;
		for(int i=1;i<len;i++)rank[i]=(type[i]&&!type[i-1])?(LMS[LMSC]=i,LMSC++):-1;
		inducedsort(str,len,sigma,LMS,LMSC,type);
		int tot=-1;
		int *s1=str+len;
		for(int i=0,now,last;i<len;i++){
		    if(-1==(now=rank[sa[i]]))continue;
		    if(tot<1||LMS[now+1]-LMS[now]!=LMS[last+1]-LMS[last])++tot;
		    else for(int j=LMS[now],k=LMS[last];j<LMS[now+1];++j,++k)if((str[j]<<1|type[j])!=(str[k]<<1|type[k])){
		        ++tot;
		        break;
		    }
		    s1[last=now]=tot;
		}
		if(tot+1<LMSC)sais(s1,LMSC,tot+1,LMS+LMSC,type+len);
		else for(int i=0;i<LMSC;i++)sa[s1[i]]=i;
		for(int i=0;i<LMSC;i++)s1[i]=LMS[sa[i]];
		inducedsort(str,len,sigma,s1,LMSC,type);
	}
    // 0-index
	void buildSA(string& s, vector<int>& sa, vector<int>& rk, vector<int>& ht){
		int n = s.size();
        sa = rk = ht = vector<int>(n + 1);
		for(int i = 0; i < n; i++) str[i] = s[i];
		sais(str, n + 1, SIGMA, LMS, type);
		for(int i = 1; i <= n; i++) sa[i] = this->sa[i] + 1;
        for(int i = 1; i <= n; i++) rk[sa[i]] = i;
        s.push_back(0);
        for(int i = 1, k = 0; i <= n; i++) {
            k = max(k - 1, 0);
            if(rk[i] == 1) continue;
            int j = sa[rk[i] - 1];
            while(s[i + k] == s[j + k]) k++;
            ht[rk[i]] = k;
        }
	}
}S;

void work() {
    string s;
    cin >> s;
    int n = s.size();

    vector<int> sa, rk, ht;
    S.buildSA(s, sa, rk, ht); // 0-index

    for(int i = 1; i <= n; i++) cout << sa[i] << " "; cout << endl;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    work();

    return 0;
}