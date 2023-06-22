// manacher알고리즘은 문자열 길이가 홀수일 때만 가능하기 때문에 중간에 #문자를 삽입한다.
// banana -> b#a#n#a#n#a 
// 문자열 속 가장 긴 팰린드롬의 길이 츨력 
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
char in[MAXN], s[MAXN*2];
int d[MAXN*2];	//i번째를 중심으로 한 팰린드롬의 반지름 
int main()
{
	int n, i, j, inn;
	scanf(" %s",in);
	inn = strlen(in);
	for(i=0; i<inn; i++){
		s[i*2]=in[i]; s[i*2+1]='#';
	}
	n=strlen(s);
	int p=0, r=0;
	d[0]=0;
	for(i=1; i<n; i++){
		int le=i-1, ri=i+1;
		if(p+r>=i){
			d[i]=min(d[p-(i-p)], p+r-i);
			le=i-d[i]; ri=i+d[i];
		}
		for(; le>=0 && ri<n && s[le]==s[ri]; le--,ri++);
		ri--;
		d[i]=ri-i;
		if(p+r<ri){
			p=i; r=d[i];
		}
	}
	int maxi=0;
	for(i=0; i<n; i++){
		int cmp=0;
		if(i%2==0) cmp=1+2*(d[i]/2);
		else cmp = 2*((d[i]+1)/2);
		maxi=max(maxi,cmp);
	}
	printf("%d\n",maxi);
	return 0;
}
