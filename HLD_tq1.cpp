//13510 : Tree&Query 1
#include <bits/stdc++.h>
using namespace std;
namespace SEG{
	//MAX Segment Tree : type=positive int32, n=1e5
	const int N=128*1024;
	int arr[2*N];
	void set(int i,int c){
		arr[i+=N]=c;
		for(i/=2;i;i/=2)
			arr[i]=max(arr[i*2],arr[i*2+1]);
	}
	int get(int i,int j){
		i+=N;j+=N;
		int res=0;
		while(i<=j){
			if(i%2)
				res=max(res,arr[i]);
			if(j%2==0)
				res=max(res,arr[j]);
			i=(i+1)/2;
			j=(j-1)/2;
		}
		return res;
	}
	//module SEG Verified by 10868
}
namespace GRAPH{
	//Get and contains Input and Graph
	int n;
	int hi[100100],lo[100100],w[100100];
	vector<int> arr[100100];
	vector<int> wrr[100100];
	void input(){
		//get input
		cin>>n;
		for(int i=1;i<n;i++){
			cin>>hi[i]>>lo[i]>>w[i];
			arr[hi[i]].push_back(lo[i]);
			wrr[hi[i]].push_back(w[i]);
			arr[lo[i]].push_back(hi[i]);
			wrr[lo[i]].push_back(w[i]);
		}
	}
	//module GRAPH Not Verified
}
namespace HLD{
	//Heavy-Light Decomposition
	using GRAPH::arr;
	using GRAPH::wrr;
	int P[100100][20];
	int S[100100],D[100100],I[100100],T[100100];
	void dfs1(int x){
		//find parents and evaluate size and depth
		S[x]=1;
		for(int i=0;i<arr[x].size();i++)
			if(arr[x][i]!=P[x][0]){
				int y=arr[x][i];
				D[y]=D[x]+1;
				P[y][0]=x;
				for(int i=1;i<20;i++)
					P[y][i]=P[P[y][i-1]][i-1];
				dfs1(y);
				S[x]+=S[y];
			}
	}
	void dfs2(int x){
		//get dfs-ordering and top
		static int cnt;
		I[x]=cnt++;
		int mi=-1;
		for(int i=0;i<arr[x].size();i++)
			if(arr[x][i]!=P[x][0])
				if(mi==-1||S[arr[x][mi]]<S[arr[x][i]])
					mi=i;//get largest subtree
		if(mi!=-1){
			//mainstream
			SEG::set(cnt,wrr[x][mi]);
			T[arr[x][mi]]=T[x];
			dfs2(arr[x][mi]);
		}
		for(int i=0;i<arr[x].size();i++)
			if(i!=mi&&arr[x][i]!=P[x][0]){
				//substream
				SEG::set(cnt,wrr[x][i]);
				T[arr[x][i]]=arr[x][i];
				dfs2(arr[x][i]);
			}
	}
	int lcs(int x,int y){
		//Lowest Common Ancestor
		if(D[x]<D[y])
			swap(x,y);
		int dd=D[x]-D[y];
		for(int i=0;i<20;i++)
			if(dd&(1<<i))
				x=P[x][i];
		if(x==y)
			return x;
		for(int i=19;i>=0;i--)
			if(P[x][i]!=P[y][i]){
				x=P[x][i];
				y=P[y][i];
			}
		return P[x][0];
	}
	void init(){
		//HLD Initializing Function
		dfs1(1);
		T[1]=1;
		dfs2(1);
	}
	int mget(int x,int p){
		int res=0;
		while(T[x]!=T[p]){
			res=max(res,SEG::get(I[T[x]],I[x]));
			x=P[T[x]][0];
		}
		res=max(res,SEG::get(I[p]+1,I[x]));
		return res;
	}
	void func(){
		//HLD Operating Function
		int m;cin>>m;
		while(m--){
			int x,y,z;
			cin>>x>>y>>z;
			if(x==1){
				using GRAPH::lo;
				using GRAPH::hi;
				if(P[hi[y]][0]==lo[y])
					swap(hi[y],lo[y]);
				SEG::set(I[lo[y]],z);
			}
			else{
				int w=lcs(y,z);
				cout<<max(mget(y,w),mget(z,w))<<'\n';
			}
		}
	}
}
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	GRAPH::input();
	HLD::init();
	HLD::func();
}
