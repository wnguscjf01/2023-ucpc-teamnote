#include<bits/stdc++.h>
#define MAXN 100001
#define logn 20
using namespace std;
vector<int> v[MAXN];
int lca[logn+1][MAXN], dep[MAXN], n;
int dfs(int p, int pa, int de){
	int i;
	lca[0][p]=pa;
	dep[p]=de;
	for(i=0; i<v[p].size(); i++){
		if(v[p][i]==pa) continue;
		dfs(v[p][i],p,de+1);
	}
	return 0;
}
int makelca(){
	int i, j;
	for(i=1; i<=logn; i++){
		for(j=1; j<=n; j++){
			lca[i][j] = lca[i-1][lca[i-1][j]];
		}
	}
	return 0;
}
int LCA(int a, int b){
	if(dep[a] < dep[b]) swap(a,b);
	int i;
	for(i=logn; i>=0; i--){
		if(dep[lca[i][a]] >= dep[b]) a=lca[i][a];
	}
	if(a==b) return a;
	for(i=logn; i>=0; i--){
		if(lca[i][a] != lca[i][b]){
			a=lca[i][a]; b=lca[i][b];
		}
	}
	return lca[0][a];
}
int main()
{
	int m, i, j;
	cin >> n;
	for(i=1; i<=n-1; i++){
		int a, b;
		scanf("%d%d",&a,&b);
		v[a].push_back(b);
		v[b].push_back(a);
	} 
	dfs(1,1,1);
	makelca();
	cin >> m;
	for(i=1; i<=m; i++){
		int a, b;
		scanf("%d%d",&a,&b);
		printf("%d\n",LCA(a,b));
	}
	return 0;
}
