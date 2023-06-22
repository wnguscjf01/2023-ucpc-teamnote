#include <bits/stdc++.h>
using namespace std;
namespace FFT{
	#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
	typedef complex<double> base;
	void fft(vector <base> &a, bool inv)
{
    int n = sz(a);
    int i, j, k, bit; 
	for(i=1,j=0;i<n;i++) { 
		for(bit=n>>1;!((j^=bit)&bit);bit>>=1); 
		if(i<j) swap(a[i], a[j]); 
	} 
	for(i=1;i<n;i<<=1) { 
		double x = (inv ? 1 : -1) * 3.1415926535897932384626 / i; 
		std::complex<double> w={cos(x),sin(x)}, th, tmp; 
		for(j=0;j<n;j+=i<<1) for(k=0,th=1;k<i;k++) { 
			assert(i+j+k<n);
			tmp = a[i+j+k]*th; a[i+j+k] = a[j+k]-tmp; 
			a[j+k] += tmp; 
			th *= w; 
		} 
	} 
	if(inv) for(i=0;i<n;i++) a[i]/=n;
}
 
void multiply(const vector<int> &a,const vector<int> &b,vector<long long> &res)
{
    vector <base> fa(all(a)), fb(all(b));
    int n = 1;
    while (n <= max(sz(a),sz(b))) n <<= 1; n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,false); fft(fb,false);
    for (int i=0;i<n;i++) fa[i] *= fb[i];
    fft(fa,true);
    res.resize(n);
    for(int i=0;i<n;i++)res[i]=fa[i].real()+0.5;
}
#undef sz
#undef all
}
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	string sa,sb;cin>>sa>>sb;
	if(sa=="0"||sb=="0"){
		cout<<0;
		return 0;
	}
	int n=sa.size(),m=sb.size();
	vector<int> a(n),b(m);
	vector<long long>c;
	for(int i=0;i<n;i++)
		a[i]=sa[i]-'0';
	for(int i=0;i<m;i++)
		b[i]=sb[i]-'0';
	FFT::multiply(a,b,c);
	c.resize(n+m-1);
	long long ans=0;
	for(int i=c.size()-1;i>0;i--){
		c[i-1]+=c[i]/10;
		c[i]%=10;
	}
	for(long long i:c)
		cout<<i;
}
