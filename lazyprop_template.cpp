#include <bits/stdc++.h>
using namespace std;
#define N (1024*1024)
int tree[2*N];
int lazy[2*N];
void push(int i){
	if(lazy[i]){
		tree[i]+=lazy[i];
		if(i<N){
			lazy[i*2]+=lazy[i];
			lazy[i*2+1]+=lazy[i];
		}
		lazy[i]=0;
	}
}
void upd(int i,int L,int R,int l,int r,int v){
	push(i);
	if(L>r||l>R)return;
	if(l<=L&&R<=r){
		lazy[i]=v;
		push(i);
		return;
	}
	upd(i*2,L,(L+R)/2,l,r,v);
	upd(i*2+1,(L+R)/2+1,R,l,r,v);
	tree[i]=min(tree[i*2],tree[i*2+1]);
}
int get(int i,int L,int R,int l,int r){
	if(L>r||l>R)return 1987654321;
	push(i);
	if(l<=L&&R<=r)
		return tree[i];
	return min(get(i*2,L,(L+R)/2,l,r),get(i*2+1,(L+R)/2+1,R,l,r));
}
int arr[300300];
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n;cin>>n;
	long long res=0;
	for(int i=0;i<n;i++)
		cin>>arr[i];
	for(int i=n-1;i>=0;i--){
		res+=get(1,0,N-1,arr[i],arr[i]);
		upd(1,0,N-1,arr[i]+1,N-1,1);
	}
	for(int i=0;i<n;i++){
		upd(1,0,N-1,arr[i]+1,N-1,-1);
		cout<<res-get(1,0,N-1,arr[i],arr[i])+get(1,0,N-1,0,N-1)<<' ';
		upd(1,0,N-1,0,arr[i]-1,1);
	}
}
