#include <bits/stdc++.h>
using namespace std;
class LCT{
private:
	struct nod{
		int l,r,p,cnt;
		nod():l(0),r(0),p(0),cnt(1){}
	};
	vector<nod> arr;
	bool isr(int x){
		return !arr[x].p||arr[arr[x].p].l!=x&&arr[arr[x].p].r!=x;
	}
	void mer(int x){
		arr[x].cnt=1;
		if(arr[x].l)arr[x].cnt+=arr[arr[x].l].cnt;
		if(arr[x].r)arr[x].cnt+=arr[arr[x].r].cnt;
	}
	void rot(int x){
	    int p=arr[x].p;
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
	        if(!isr(p)){
	            if((x==arr[p].l)==(p==arr[arr[p].p].l))rot(p);
	            else rot(x);
	        }
	        rot(x);
	    }
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
};
