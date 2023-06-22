//시작점부터 도착점까지 최대유량 출력
#include<bits/stdc++.h>
#define MAXN 401
using namespace std;
pair<int,int> flow[MAXN][MAXN];	//.first 현재 유량 .second 용량 
vector<int> v[MAXN]; //거꾸로도 연결 
int par[MAXN];
int main()
{
	int n, m, i, j;
	cin >> n >> m;
	for(i=1; i<=m; i++){
		int a, b;
		scanf("%d%d",&a,&b);
		v[a].push_back(b);
		v[b].push_back(a);
		flow[a][b].second=1;
	}
	int ans=0, start=1, end=2;    //출발, 도착지 설정
	while(1){
		queue<int> q;
		bool ff[MAXN]={0,};
		q.push(start);
		fill(par+1,par+n+1,0);
		while(!q.empty()){
			int p=q.front();
			q.pop();
			if(ff[p]) continue;
			ff[p]=1;
			if(p==end) break;
			for(i=0; i<v[p].size(); i++){
				if(ff[v[p][i]] || flow[p][v[p][i]].first>=flow[p][v[p][i]].second) continue;
				par[v[p][i]]=p;
				q.push(v[p][i]);
			}
		}
		if(par[end]==0) break;
		int mini=INT_MAX;
		for(i=end; i!=start; i=par[i]){
			mini=min(mini,flow[par[i]][i].second-flow[par[i]][i].first);
		}
		for(i=end; i!=start; i=par[i]){
			flow[par[i]][i].first+=mini;
			flow[i][par[i]].first-=mini;
		}
		ans+=mini;
	}
	printf("%d\n",ans);
	return 0;
}
