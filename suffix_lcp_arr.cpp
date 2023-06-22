//13264
#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;
namespace SUF{
	vector<int> f(string s){
		int n=s.size();
		vector<int> arr(n);
		vector<int> group(n+1),_group(n+1);
		group[n]=_group[n]=-1;
		for(int i=0;i<n;i++){
			arr[i]=i;
			group[i]=s[i];
		}
		for(int k=1;k<n;k*=2){
			sort(arr.begin(),arr.end(),[&](int a,int b){
				if(group[a]==group[b])
					return group[a+k]<group[b+k];
				return group[a]<group[b];
			});
			_group[arr[0]]=0;
			for(int i=1;i<n;i++)
				_group[arr[i]]=_group[arr[i-1]]+
				(group[arr[i-1]]!=group[arr[i]]?
				group[arr[i-1]]<group[arr[i]]:
				group[arr[i-1]+k]<group[arr[i]+k]);
			group=_group;
		}
		return arr;
	}
}
namespace LCP{
	vector<int> f(string s,vector<int> arr){
		int n=s.size();
		vector<int> brr(n);
		vector<int> res(n);
		for(int i=0;i<n;i++)
			brr[arr[i]]=i;
		int k=0;
		for(int i=0;i<n;i++){
			if(brr[i]==0){
				k=0;
				continue;
			}
			if(k>0)
				k--;
			while(i+k<n&&arr[brr[i]-1]+k<n&&s[i+k]==s[arr[brr[i]-1]+k])
				k++;
			res[brr[i]]=k;
		}
		return res;
	}
}
int main(){
	string s;cin>>s;
	auto arr=SUF::f(s);
	auto brr=LCP::f(s,arr);
	brr.erase(brr.begin());
	for(int i:arr)
		cout<<i+1<<' ';
	cout<<"\nx ";
	for(int i:brr)
		cout<<i<<' ';
}
