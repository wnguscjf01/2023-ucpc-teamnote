//Miller-Rabin / Pollard rho
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
bool isPrime(long long x){
	assert(x>0);
	if(x==1)
		return false;
	long long _x=x-1;
	int r=0;
	for(;_x%2==0;r++)
		_x/=2;
	for(int a:{2,3,5,7,11,13,17,19,23,29,31,37})
		if(x!=a){
			__int128 rp=1,r_=a%x;
			for(long long i=1;i<=_x;i*=2){
				if(i&_x)
					rp=rp*r_%x;
				r_=r_*r_%x;
			}
			if(rp==1||rp==x-1)
				continue;
			for(int i=1;i<r;i++){
				rp=rp*rp%x;
				if(rp==x-1)
					break;
			}
			if(rp!=x-1)
				return false;
		}
		else
			return true;
	return true;
}
vector<long long> V;
void f(long long n){
	if(isPrime(n)){
		V.push_back(n);
		return;
	}
	for(int i=2;;i++){
		__int128 x=i,y=i;
		for(;;){
			x=(x*x+1)%n;
			y=(y*y+1)%n;
			y=(y*y+1)%n;
			__int128 _x=x>y?x-y:y-x,_y=n;
			if(_x<_y)
				swap(_x,_y);
			while(_y){
				_x%=_y;
				swap(_x,_y);
			}
			if(_x!=1)
				if(_x==n)
					break;
				else{
					V.push_back(_x);
					f(n/_x);
					return;
				}
		}
	}
}
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	long long n;
	cin>>n;
	for(int i=2;i<1234567;i++){
		while(n%i==0){
			V.push_back(i);
			n/=i;
		}
	}
	if(n!=1)
		f(n);
	sort(V.begin(),V.end());
	for(auto i:V)
		cout<<i<<'\n';
}
