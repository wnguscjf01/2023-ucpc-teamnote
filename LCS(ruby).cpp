#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
#define x first
#define y second
ull _b[26][782],(*_B)[782]=_b-'A',s[782];
vector<int>nws(string A,string B){
	int b=B.size(),xb=b/64+1;
	memset(s,0,xb*8);
	for(int i=0;i<26;i++)
		memset(_b[i],0,xb*8);
	for(int j=0;j<b;j++)
		_B[B[j]][j/64]|=1ull<<j%64;
	for(char a:A){
		ull f1=0,f2=1;
		for(int i=0;i<xb;i++){
			ull x=_B[a][i]|s[i];
			ull y=s[i]<<1|f2;
			f2=s[i]>>63;
			ull z=x-y-f1;
			f1=z>x||z==x&&f1;
			s[i]=x&(x^z);
		}
	}
	vector<int> res;
	res.resize(B.size()+1);
	for(int i=0;i<B.size();i++)
		res[i+1]=res[i]+!!(s[i/64]&1ull<<i%64);
	return res;
}
string hir(string X,string Y){
	//cout<<X<<' '<<Y<<'\n';
	string Z,W;
	if(X.empty()||Y.empty())
		return Z;
	if(X.size()==1||Y.size()==1){
		for(char x:X)
			for(char y:Y)
				if(x==y){
					Z.push_back(x);
					return Z;
				}
		return Z;
	}
	string Xl,Xr,_Y=Y,Yl,Yr;int i=0;
	for(;i<X.size()/2;i++)
		Xl.push_back(X[i]);
	for(;i<X.size();i++)
		Xr.push_back(X[i]);
	reverse(Xr.begin(),Xr.end());
	reverse(_Y.begin(),_Y.end());
	vector<int> SL=nws(Xl,Y);
	vector<int> SR=nws(Xr,_Y);
	reverse(Xr.begin(),Xr.end());
	reverse(SR.begin(),SR.end());
	int yi=0;
	for(i=0;i<SL.size();i++)
		if(SL[i]+SR[i]>SL[yi]+SR[yi])
			yi=i;
	for(i=0;i<yi;i++)
		Yl.push_back(Y[i]);
	for(;i<Y.size();i++)
		Yr.push_back(Y[i]);
	return hir(Xl,Yl)+hir(Xr,Yr);
}
int main(){
	string A,B;
	cin>>A>>B;
	string C=hir(A,B);
	cout<<C.size()<<'\n'<<C;
}
