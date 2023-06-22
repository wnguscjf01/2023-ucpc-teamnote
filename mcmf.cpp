//11408 MCMF
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define inf 1987654321
#define N 1000
vector<int> A[N];
vector<int> C[N];
vector<int> D[N];
vector<int> R[N];
pair<int,int> flow(int s,int e){
	static int P[N],_P[N],E[N],_Q[N];
	int res1=0,res2=0;
	for(;;){
		memset(P,-1,sizeof P);
		memset(E,60,sizeof E);
		memset(_Q,0,sizeof _Q);
		queue<int> Q;
		E[s]=0;
		Q.push(s);_Q[s]=1;
		while(!Q.empty()){
			int q=Q.front();Q.pop();_Q[q]=0;
			for(int i=0;i<A[q].size();i++)
				if(C[q][i]&&E[q]+D[q][i]<E[A[q][i]]){
					P[A[q][i]]=q;
					_P[A[q][i]]=i;
					E[A[q][i]]=E[q]+D[q][i];
					if(!_Q[A[q][i]]){
						Q.push(A[q][i]);
						_Q[A[q][i]]=1;
					}
				}
		}
		if(!~P[e])break;
		int dr=inf;
		for(int i=e;i!=s;i=P[i])
			dr=min(dr,C[P[i]][_P[i]]);
		res1+=dr;
		for(int i=e;i!=s;i=P[i]){
			C[P[i]][_P[i]]-=dr;
			C[i][R[P[i]][_P[i]]]+=dr;
		}
		res2+=E[e];
	}
	return {res1,res2};
}
void edge(int a,int b,int c,int d){
	R[a].push_back(A[b].size());
	R[b].push_back(A[a].size());
	A[a].push_back(b);
	A[b].push_back(a);
	C[a].push_back(c);
	C[b].push_back(0);
	D[a].push_back(d);
	D[b].push_back(-d);
}
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n,m;cin>>n>>m;
	for(int i=1;i<=n;i++){
		edge(0,i,1,0);
		int k;cin>>k;
		while(k--){
			int x,y;cin>>x>>y;
			edge(i,500+x,1,-y);
		}
	}
	for(int i=1;i<=m;i++)
		edge(500+i,999,1,0);
	auto res=flow(0,999);
	cout<<res.first<<'\n'<<-res.second;
}
