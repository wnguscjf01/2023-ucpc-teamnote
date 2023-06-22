#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define N 4096
struct GM{
	long long s,l,r,m;
	GM():s(0),l(0),r(0),m(0){}
	GM(long long x):s(x){
		l=r=m=max(x,0ll);
	}
	GM operator+(GM y){
		GM z;
		z.s=s+y.s;
		z.l=max(l,s+y.l);
		z.r=max(y.r,r+y.s);
		z.m=max({m,r+y.l,y.m});
		return z;
	}
};
GM T[N*2];
void upd(int i,long long v){
	i+=N;
	T[i]=T[i].s+v;
	for(i/=2;i;i/=2)
		T[i]=T[i*2]+T[i*2+1];
}
GM get(int i,int j){
	GM l, r;
	i+=N;j+=N;
	while(i<=j){
		if(i%2)l=l+T[i];
		if(j%2==0)r=T[j]+r;
		i=(i+1)/2;
		j=(j-1)/2;
	}
	return l+r;
}
pair<pair<int,int>,int> arr[3030];
int main(){
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	int n;cin>>n;
	map<int,int> My;
	for(int i=0;i<n;i++){
		cin>>arr[i].x.x>>arr[i].x.y>>arr[i].y;
		My[arr[i].x.y]=0;
	}
	int _=0;
	for(auto&p:My)
		p.y=_++;
	for(int i=0;i<n;i++)
		arr[i].x.y=My[arr[i].x.y];
	sort(arr,arr+n);
	long long _max=0;
	for(int i=0;i<n;i++){
		memset(T,0,sizeof T);
		for(int j=i;j<n;){
			for(int x=arr[j].x.x;x==arr[j].x.x;j++)
				upd(arr[j].x.y,arr[j].y);
			_max=max(_max,get(0,N-1).m);
		}
		while(arr[i].x.x==arr[i+1].x.x)
			i++;
	}
	cout<<_max;
}
