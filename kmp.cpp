// sen, s를 비교하여 s가 sen에서 몇번 나타나고 sen의 어디서 나타나는지 출력 
#include<bits/stdc++.h>
#define MAXN 1000002
using namespace std;
char sen[MAXN], s[MAXN];
int p[MAXN], ans[MAXN], anscnt;
int main()
{
	int i, j; char trash;
	scanf("%[^\n]s",sen);
	scanf("%c",&trash);
	scanf("%[^\n]s",s);
	int n = strlen(sen), m = strlen(s);
	p[0]=0;
	for(i=1; i<m; i++){
		j = p[i-1];
		while(j>0 && s[j]!=s[i]) j=p[j-1];
		if(s[j]==s[i]) p[i] = j+1;
	}
	
	int cnt=0;
	if(s[0]==sen[0]) j=1;
	else j=0;
	if(j == m) ans[++anscnt] = 1;
	for(i=1; i<n; i++){
		if(j==m) j = p[m-1];
		while(j>0 && s[j]!=sen[i]) j = p[j-1];
		if(s[j] == sen[i]) j++;
		if(j == m){
			ans[++anscnt] = i-m+2;
		}
	}
	printf("%d\n",anscnt);
	for(i=1; i<=anscnt; i++) printf("%d ",ans[i]);
	
	return 0;
}
