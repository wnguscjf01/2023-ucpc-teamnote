/*
sum : weight of path x <-> y
*/

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
template<class data_t>
class LCT{
private:
	struct nod{
		int l,r,p,cnt;
		data_t val,sum;
		bool inv;
		nod():l(0),r(0),p(0),cnt(1),inv(false){}
	};
	vector<nod> arr;
	bool isr(int x){
		return !arr[x].p||arr[arr[x].p].l!=x&&arr[arr[x].p].r!=x;
		//return !arr[x].p;
	}
	void lazy(int x){
		if(arr[x].inv){
			arr[x].inv=false;
			swap(arr[x].l,arr[x].r);
			if(arr[x].l)arr[arr[x].l].inv=!arr[arr[x].l].inv;
			if(arr[x].r)arr[arr[x].r].inv=!arr[arr[x].r].inv;
		}
	}
	void mer(int x){
		arr[x].cnt=1;
		arr[x].sum=arr[x].val;
		if(arr[x].l){
			arr[x].cnt+=arr[arr[x].l].cnt;
			arr[x].sum=arr[arr[x].l].sum+arr[x].sum;
		}
		if(arr[x].r){
			arr[x].cnt+=arr[arr[x].r].cnt;
			arr[x].sum=arr[x].sum+arr[arr[x].r].sum;
		}
	}
	void rot(int x){
	    int p=arr[x].p;//cout<<"!p="<<p<<endl;
	    if(x==arr[p].l){
	        arr[p].l=arr[x].r;
	        arr[x].r=p;
	        if(arr[p].l)
	            arr[arr[p].l].p=p;
	    }
	    else{
	        arr[p].r=arr[x].l;
	        arr[x].l=p;
	        if(arr[p].r)
	            arr[arr[p].r].p=p;
	    }
	    arr[x].p=arr[p].p;
	    arr[p].p=x;
	    if(arr[x].p){
	        if(p==arr[arr[x].p].l)arr[arr[x].p].l=x;
	        else if(p==arr[arr[x].p].r)arr[arr[x].p].r=x;
	    }
	    mer(p);
	    mer(x);
	}
	void splay(int x){
	    while(!isr(x)){
	        int p=arr[x].p;
	        if(!isr(p))lazy(arr[p].p);
	        lazy(p);
	        lazy(x);
	        if(!isr(p)){
	            if((x==arr[p].l)==(p==arr[arr[p].p].l))rot(p);
	            else rot(x);
	        }
	        rot(x);
	        //cout<<'!'<<x<<' '<<arr[x].p<<endl;
	    }
	    lazy(x);
	}
	int access(int x){
		splay(x);
		arr[x].r=0;
		mer(x);
		int ret=x;
		while(arr[x].p){
			int y=arr[x].p;
			ret=y;
			splay(y);
			arr[y].r=x;
			mer(y);
			splay(x);
		}
		return ret;
	}
public:
	LCT(int n):arr(n){}
	void link(int x,int p){
		access(x);
		splay(x);
		arr[x].inv=!arr[x].inv;
		access(x);
		access(p);
		arr[x].l=p;
		arr[p].p=x;
		mer(x);
	}
	void cut(int x){
		access(x);
		arr[arr[x].l].p=0;
		arr[x].l=0;
		mer(x);
	}
	int lca(int x,int y){
		access(x);
		return access(y);
	}
	int root(int x){
		access(x);
		while(arr[x].l)
			x=arr[x].l;
		splay(x);
		return x;
	}
	int parent(int x){
		access(x);
		x=arr[x].l;
		if(!x)return 0;
		while(arr[x].r)
			x=arr[x].r;
		splay(x);
		return x;
	}
	int depth(int x){
		access(x);
		if(arr[x].l)
			return arr[arr[x].l].cnt;
		return 0;
	}
	data_t sum(int x,int y){
		int p=lca(x,y);//cout<<p<<endl;
		data_t res=arr[p].val;
		access(x);
		splay(p);
		if(arr[p].r) res=res+arr[arr[p].r].sum;
		access(y);
		splay(p);
		if(arr[p].r) res=res+arr[arr[p].r].sum;
		return res;
	}
	void to_root(int x){
		access(x);
		arr[x].inv=!arr[x].inv;
	}
	void upd(int x,data_t v){
		splay(x);
		arr[x].val=v;
		mer(x);
	}
};
struct m_t{
	pair<int,int> m;
	m_t(int a=1987654321,int b=-1):m(a,b){}
	m_t(pair<int,int> ab):m(ab){}
	m_t operator+(m_t y){
		return min(m,y.m);
	}
};
set<pair<int,int>> S;
int main(){
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	int n,q;cin>>n>>q;
	LCT<m_t> tree(720100);
	int iii=316316;
	while(q--){
		int t;cin>>t;
		if(t==1){
			int i,j,d;cin>>i>>j>>d;
			if(tree.root(i)==tree.root(j)){
				m_t cr=tree.sum(i,j);
				if(cr.m.first>=d){
					//cout<<'!'<<d<<' '<<cr.m.first<<endl;
					continue;
				}
				tree.cut(cr.m.second);
				S.erase(cr.m);
				//cout<<'!'<<cr.m.first<<endl;
			}
			tree.upd(iii,{d,iii});
			tree.link(i,iii);
			tree.link(iii,j);
			S.emplace(d,iii);
			iii++;
		}
		else if(t==2){
			int x;cin>>x;
			auto e=S.lower_bound({x,0});
			for(auto it=S.begin();it!=e;it++){
				//cout<<'!'<<it->first<<' '<<it->second<<'\n';
				tree.cut(it->second);
			}
			S.erase(S.begin(),e);
		}
		else{
			int i,j;cin>>i>>j;
			//cout<<tree.root(i)<<' '<<tree.root(j)<<endl;
			if(tree.root(i)==tree.root(j))
				cout<<tree.sum(i,j).m.first<<'\n';
			else
				cout<<"0\n";
		}
	}
}
