#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
vector<int> arr[10001];
int vis[10001];
vector<int> _arr[10001];
int _vis[10001];
int cnt,vn[10001];
int n;
void _dfs(int idx){
    _vis[idx]=1;
    for(int i=0;i<_arr[idx].size();i++)
        if(!_vis[_arr[idx][i]])
            _dfs(_arr[idx][i]);
    vn[cnt++]=idx;
}
vector<int> result[10001];
int rcn;
void dfs(int idx){
    vis[idx]=1;
    result[rcn].push_back(idx);
    for(int i=0;i<arr[idx].size();i++)
        if(!vis[arr[idx][i]])
            dfs(arr[idx][i]);
}
int main(){
    int e,i,x,y;
    scanf("%d %d",&n,&e);
    for(i=0;i<e;i++){
        scanf("%d %d",&x,&y);
        arr[x].push_back(y);
        _arr[y].push_back(x);
    }
    for(i=1;i<=n;i++){
        if(!_vis[i])
            _dfs(i);
    }
    for(i=cnt-1;i>=0;i--){
        if(!vis[vn[i]]){
            dfs(vn[i]);
            sort(result[rcn].begin(),result[rcn].end());
            rcn++;
        }
    }
    sort(result,result+rcn,[](vector<int>&a,vector<int>&b){return a[0]<b[0];});
    printf("%d\n",rcn);
    for(i=0;i<rcn;i++){
        for(int j=0;j<result[i].size();j++)
            printf("%d ",result[i][j]);
        printf("-1\n");
    }
    return 0;
}
