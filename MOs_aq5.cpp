//arr&Query 5 : 구간 [x,y] 중 서로 다른 수의 개수를 구하는 예제 
#include<bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef pair<int,int> pii;
int arr[100100];
pair<pii,int> qrr[100100];
int ans[100100];
int cnt[1000100];
int main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)
		cin>>arr[i];
	int m;cin>>m;
	for(int i=0;i<m;i++){
		cin>>qrr[i].x.x>>qrr[i].x.y;
		qrr[i].y=i;
	}
	sort(qrr,qrr+m,[](pair<pii,int>a,pair<pii,int>b){
		if(a.x.x/400==b.x.x/400)
			return a.x.y<b.x.y;
		return a.x.x<b.x.x;
	});
	int res=0;
	for(int i=0;i<m;i++){
		pii pre=i?qrr[i-1].x:pii(0,0);
		for(int j=pre.x-1;j>=qrr[i].x.x;j--)
			if(!cnt[arr[j]]++)
				res++;
		for(int j=pre.x;j<qrr[i].x.x;j++)
			if(!--cnt[arr[j]])
				res--;
		for(int j=pre.y;j>qrr[i].x.y;j--)
			if(!--cnt[arr[j]])
				res--;
		for(int j=pre.y+1;j<=qrr[i].x.y;j++)
			if(!cnt[arr[j]]++)
				res++;
		ans[qrr[i].y]=res;
	}
	for(int i=0;i<m;i++)
		cout<<ans[i]<<'\n';
}
