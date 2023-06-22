#include <bits/stdc++.h>
using namespace std;
#define N (128*1024)
namespace SBK{ //sum of biggest k in range, implementation using persistent segment tree
	#define NN (N*2)
	#define x first
	#define y second.first
	#define z second.second
	typedef pair<int,pair<int,long long>> pii;
	int n;
	vector<pii> pst[NN];
	void upd(int i,int t,int v){
		pst[i+=N].push_back({t,{1,v}});
		while(i/=2)
			pst[i].push_back({t,{
				pst[i*2].back().y+pst[i*2+1].back().y,
				pst[i*2].back().z+pst[i*2+1].back().z
			}});
	}
	int gety(int t,int i,int j){
		int res=0;i+=N;j+=N;
		while(i<=j){
			if(i%2)res+=prev(lower_bound(pst[i].begin(),pst[i].end(),pii(t+1,{-1,0})))->y;
			if(j%2==0)res+=prev(lower_bound(pst[j].begin(),pst[j].end(),pii(t+1,{-1,0})))->y;
			i=(i+1)/2;
			j=(j-1)/2;
		}
		return res;
	}
	long long getz(int t,int i,int j){
		long long res=0;i+=N;j+=N;
		while(i<=j){
			if(i%2)res+=prev(lower_bound(pst[i].begin(),pst[i].end(),pii(t+1,{-1,0})))->z;
			if(j%2==0)res+=prev(lower_bound(pst[j].begin(),pst[j].end(),pii(t+1,{-1,0})))->z;
			i=(i+1)/2;
			j=(j-1)/2;
		}
		return res;
	}
	long long ksum(int i,int j,int k){
		if(k<=0)return 0;
		int mint=-1,maxt=n-1;
		for(int t;maxt-mint>1;gety(t,i,j)<k?mint=t:(maxt=t))
			t=maxt+mint>>1;
		return getz(maxt,i,j);
	}
	void init(int* arr,int _n){
		n=_n;
		for(int i=0;i<NN;i++){
			pst[i].clear();
			pst[i].push_back({-1,{0,0}});
		}
		int* irr=new int[n];
		for(int i=0;i<n;i++)
			irr[i]=i;
		sort(irr,irr+n,[&arr](int a,int b){
			return arr[a]>arr[b];
		});
		for(int i=0;i<n;i++)
			upd(irr[i],i,arr[irr[i]]);
	}
	#undef NN
	#undef x
	#undef y
	#undef z
}
int main(){
	int arr[100000];
	for(int i=0;i<100000;i++)arr[i]=1000000000;
	SBK::init(arr,100000);
	while(1){
		int i,j,k;cin>>i>>j>>k;
		cout<<SBK::ksum(i,j,k)<<endl;
	}
}
