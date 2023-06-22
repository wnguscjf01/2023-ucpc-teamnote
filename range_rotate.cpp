/*
splay tree with range rotate query
*/

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
template<class data_t>
class splay_tree{
private:
	struct nod{
		nod *l,*r,*p;
		data_t num;
		data_t dat;
		int cnt;
		bool inv;
		nod(data_t x,nod *par=0):num(x),p(par),l(0),r(0),inv(false),cnt(1){
			dat=data_t(num);
		}
		void lazy(){
			if(inv){
				inv=false;
				swap(l,r);
				//dat.reverse();//erase this line when data type is symmetric
				if(l)l->inv=!l->inv;
				if(r)r->inv=!r->inv;
			}
		}
		void _mer(){
			lazy();
			dat=num;
			cnt=1;
			if(l){
				l->lazy();
				dat=l->dat+dat;
				cnt+=l->cnt;
			}
			if(r){
				r->lazy();
				dat=dat+r->dat;
				cnt+=r->cnt;
			}
		}
	};
	nod *root;
	void rot(nod *x){
   		nod *p=x->p,*b;
	    if(x==p->l){
	        p->l=b=x->r;
	        x->r=p;
	    }
		else{
	        p->r=b=x->l;
	        x->l=p;
	    }
	    x->p=p->p;
	    p->p=x;
	    if(b)b->p=p;
	    (x->p?p==x->p->l?x->p->l:x->p->r:root)=x;
		p->_mer();
		x->_mer();
	}
	void splay(nod *x){
		while (x->p) {
	        nod *p=x->p;
	        nod *g=p->p;
	        if(g)rot((x==p->l)==(p==g->l)?p:x);
	        rot(x);
	    }
	}
	void kth(int k){
		nod *x=root;
		x->lazy();
		for(;;){
	        while(x->l&&x->l->cnt>k){
	            x=x->l;
	            x->lazy();
	        }
	        if(x->l)
				k-=x->l->cnt;
	        if(!k--)break;
	        x=x->r;
	        x->lazy();
	    }
    	splay(x);
	}
	void intv(int l,int r){
		kth(l-1);
		nod *s=root;
		root=s->r;
		root->p=0;
		kth(r-l+1);
		s->r=root;
		root->p=s;
		root=s;
	}
	void prn(nod *x){
		x->lazy();
		if(x->l)
			prn(x->l);
		if(x->num._max)
			cout<<x->num._max<<' ';
		if(x->r)
			prn(x->r);
	}
public:
	splay_tree():root(0){}
	void* ins_back(data_t num){
	    if(!root){
	        root=new nod(num);
	        return root;
	    }
	    nod *p=root;
	    while(p->r)
	    	p=p->r;
	    nod* res=p->r=new nod(num,p);
	    splay(p->r);
	    return res;
	}
	void ins_kth(int k,data_t num){
	    kth(k);
	    nod *p=root->r;
	    p->lazy();
	    while(p->l){
	    	p=p->l;
	    	p->lazy();
	    }
	    p->l=new nod(num,p);
	    splay(p->l);
	}
	void del_kth(int k){
		kth(k);
		nod *p=root->r;
		p->lazy();
		while(p->l){
	    	p=p->l;
	    	p->lazy();
	    }
	    if(p->r)
	    	p->r->p=p->p;
    	if(p->p->l==p)
    		p->p->l=p->r;
    	else
    		p->p->r=p->r;
    	splay(p->p);
		delete p;
	}
	void rep_kth(int k,data_t num){
		kth(k+1);
		root->num=num;
		root->_mer();
	}
	//[l, ... , r]
	//[r-k+1, ... , r, l, ... , r-k]
	void query(int l,int r,int k){ 
		intv(l, r-k);
		root->r->lazy();
		auto ptr=root->r->l;
		root->r->l=NULL;
		root->r->_mer();
		root->_mer();
		kth(l+k-1);
		nod *p=root->r;
	    while(p->lazy(),p->l){
	    	p=p->l;
	    }
	    p->l=ptr;
	    p->_mer();
	    splay(p);
	}
	data_t sum(int l,int r){
		intv(l,r);
		return root->r->l->dat;
	}
	void rev(int l,int r){
		intv(l,r);
		root->r->l->inv=!root->r->l->inv;
		root->r->_mer();
		root->_mer();
	}
	int whereisit(void* q){
		nod* p=(nod*)q;
		vector<nod*> loot;
		loot.push_back(p);
		while(p!=root){
			p=p->p;
			loot.push_back(p);
		}
		while(!loot.empty()){
			loot.back()->lazy();
			loot.pop_back();
		}
		p=(nod*)q;
		splay(p);
		return root->l->cnt;
	}
	void prn(){
		prn(root);
		cout<<'\n';
	}
};
typedef long long ll;
struct mydata{
	int _min;
	int _max;
	ll _sum;
	mydata():_min(1987654321),_max(0),_sum(0){}
	mydata(int x):_min(x),_max(x),_sum(x){}
};
mydata operator+(mydata a,mydata b){
	mydata res;
	res._min=min(a._min,b._min);
	res._max=max(a._max,b._max);
	res._sum=a._sum+b._sum;
	return res;
}
void* arr[300300];
int main(){
	cin.tie(0);cout.tie(0);
	ios::sync_with_stdio(false);
	splay_tree<mydata> T;
	int n,q;cin>>n>>q;
	T.ins_back(mydata());
	for(int i=1;i<=n;i++)
		arr[i]=T.ins_back(mydata(i));
	T.ins_back(mydata());
	//T.prn();
	while(q--){
		int t;cin>>t;
		if(t==1){
			int l,r;cin>>l>>r;
			mydata res=T.sum(l,r);
			cout<<res._min<<' '<<res._max<<' '<<res._sum<<'\n';
			T.rev(l,r);
		}
		else if(t==2){
			int l,r,k;cin>>l>>r>>k;
			mydata res=T.sum(l,r);
			cout<<res._min<<' '<<res._max<<' '<<res._sum<<'\n';
			k%=r-l+1;
			if(k<0)k+=r-l+1;
			T.query(l,r,k);
		}
		else if(t==3){
			int i;cin>>i;
			mydata res=T.sum(i,i);
			cout<<res._max<<'\n';
		}
		else if(t==4){
			int x;cin>>x;
			int res=T.whereisit(arr[x]);
			cout<<res<<'\n';
		}
		//T.prn();
	}
	T.prn();
}
