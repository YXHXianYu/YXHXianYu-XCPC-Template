#include<bits/stdc++.h>
using namespace std;
long long a[1000000],lmin[1000000],rmin[1000000],pos[1000001];
long long l[1000000],r[1000000];
stack<int>s;
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,i,j,t;
	long long cl,cr,ans=0,cmin,cminp;
	cin>>n;
	for(i=0;i<n;i++)cin>>a[i];
	for(i=0;i<n;i++)
	{
		while(!s.empty()&&a[s.top()]>a[i])s.pop();
		if(s.empty())lmin[i]=-1;
		else lmin[i]=s.top();
		s.push(i);
	}
	while(!s.empty())s.pop();
	for(i=n-1;i>-1;i--)
	{
		while(!s.empty()&&a[s.top()]>a[i])s.pop();
		if(s.empty())rmin[i]=n;
		else rmin[i]=s.top();
		s.push(i);
	}

	while(!s.empty())s.pop();
	for(i=0;i<n;i++)pos[a[i]]=i;
	for(j=1;j<=n;j++)
	{
		t=pos[j];
		cl=t;
		cr=t;
		if(cl>0)cl-=l[cl-1];
		if(cr<n-1)cr+=r[cr+1];
        cout << j << ": " << cl << ", " << t << ", " << cr << endl;
		if(cr-t>=t-cl)
		{
			ans--;
			cmin=1000000000;
			cminp=-1;
			for(i=t;i>=cl;i--)
			{
				if(a[i]<cmin)
				{
					cmin=a[i];
					cminp=i;
				}
				ans+=min(cr-t+1,rmin[cminp]-t);
			}
		}
		else
		{
			ans+=(cr-t+1)*(t-cl+1);
			cmin=1000000000;
			cminp=-1;
			for(i=t;i<=cr;i++)
			{
				if(a[i]<cmin)
				{
					cmin=a[i];
					cminp=i;
				}
				ans-=min(t-cl+1,t-lmin[cminp]);
			}
		}
		l[cr]=cr-cl+1;
		r[cl]=cr-cl+1;
	}
	cout<<ans<<'\n';
	return 0;
}