#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define x first
#define y second
#define N (256*1024)
#define M (1024*1024)
#define inf 0x3f3f3f3f
int n,k,res=inf;
int siz[N],v[N];
vector<pii> arr[N];
void dfs1(int x,int p){
	siz[x]=1;
	for(auto[y,w]:arr[x])
		if(y!=p&&!v[y]){
			dfs1(y,x);
			siz[x]+=siz[y];
		}
}
int cent(int x,int p,int s){
	for(auto[y,w]:arr[x])
		if(y!=p&&!v[y]&&siz[y]*2>s)
			return cent(y,x,s);
	return x;
}
vector<pii> tmp;
void dfs2(int x,int p,int d,int l){
	if(l>k)
		return;
	tmp.push_back({d,l});
	for(auto[y,w]:arr[x])
		if(y!=p&&!v[y])
			dfs2(y,x,d+1,l+w);
}
int D[M];
void dnc(int x){
	dfs1(x,-1);
	x=cent(x,-1,siz[x]);
	vector<int> del;
	for(auto[y,w]:arr[x])
		if(!v[y]){
			tmp.clear();
			dfs2(y,x,1,w);
			for(auto[d,l]:tmp)
				res=min(res,D[k-l]+d);
			for(auto[d,l]:tmp)
				if(d<D[l]){
					D[l]=d;
					del.push_back(l);
				}
		}
	v[x]=1;
	for(int i:del)
		D[i]=!!i*inf;
	for(auto[y,w]:arr[x])
		if(!v[y])
			dnc(y);
}
int main(){
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	memset(D,inf,sizeof D);
	D[0]=0;
	cin>>n>>k;
	for(int i=1;i<n;i++){
		int x,y,z;cin>>x>>y>>z;
		arr[x].push_back({y,z});
		arr[y].push_back({x,z});
	}
	dnc(0);
	cout<<(res==inf?-1:res);
}
