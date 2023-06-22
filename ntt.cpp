#include <bits/stdc++.h>
using namespace std;
namespace NTT{
	typedef long long ll;
	ll mpow(ll a,ll b,ll m){
		ll res=1;
		for(;b;b>>=1){
			if(b&1)
				res=res*a%m;
			a=a*a%m;
		}
		return res;
	}
	void ntt(vector<ll>& f,int inv,ll mod,ll w) {
        int n=f.size(),j=0;
        vector<ll> r(n>>1);
        for(int i=1;i<n;i++) {
            int bit=n>>1;
            for(;j>=bit;bit>>=1)
                j-=bit;
            j+=bit;
            if(i<j)
				swap(f[i],f[j]);
        }
        ll ang=mpow(w,(mod-1)/n,mod);
		if(inv)
			ang=mpow(ang,mod-2,mod);
        r[0]=1;
		for(int i=1;i<n>>1;i++)
			r[i]=r[i-1]*ang%mod;
        for(int i=2;i<=n;i<<=1){
            int stp=n/i;
            for(int j=0;j<n;j+=i){
                for(int k=0;k<i>>1;k++){
                    ll u=f[j|k],v=f[j|k|i>>1]*r[stp*k]%mod;
                    f[j|k]=(u+v)%mod;
                    f[j|k|i>>1]=((u-v)%mod+mod)%mod;
                }
            }
        }
        if(inv){
        	ll t=mpow(n,mod-2,mod);
        	for(int i=0;i<n;i++)
				f[i]=f[i]*t%mod;
		}
    }
    vector<ll> mul(vector<ll>a,vector<ll>b,ll mod,ll w) {
        int n=2;
        while(n<a.size()+b.size())
			n<<=1;
        a.resize(n);
		b.resize(n);
        ntt(a,0,mod,w);
		ntt(b,0,mod,w);
        for(int i=0;i<n;i++)
			a[i]=a[i]*b[i]%mod;
        ntt(a,1,mod,w);
        return a;
    }
}
long long inv(long long x,long long mod){
	long long y=mod,i=1,j=0;
	while(x){
		j-=y/x*i;
		y%=x;
		swap(x,y);
		swap(i,j);
	}
	return (j%mod+mod)%mod;
}
#define p1 2281701377ll
#define p2 2483027969ll
#define pp (p1*p2)
/*example : c=a*b (´ÙÇ×½ÄÀÇ °ö¼À)*/
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n,m;cin>>n>>m;
	vector<long long> a(n+1),b(m+1),c1,c2;
	for(int i=0;i<=n;i++)
		cin>>a[i];
	for(int i=0;i<=m;i++)
		cin>>b[i];
	c1=NTT::mul(a,b,p1,3);
	c2=NTT::mul(a,b,p2,3);
	assert(c1.size()==c2.size());
	long long _21=inv(p2,p1),_12=inv(p1,p2),res=0;
	for(int i=0;i<c1.size();i++){
		long long q1=c1[i],q2=c2[i];
		res^=(long long)(((__int128)q1*p2*_21+(__int128)q2*p1*_12)%pp);
	}
	cout<<res;
}
