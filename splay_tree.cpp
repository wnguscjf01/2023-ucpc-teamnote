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
				dat.reverse();//erase this line when data type is symmetric
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
		cout<<'(';
		if(x->l)
			prn(x->l);
		cout<<x->num;
		if(x->r)
			prn(x->r);
		cout<<')';
	}
public:
	splay_tree():root(0){}
	void ins_back(data_t num){
	    if(!root){
	        root=new nod(num);
	        return;
	    }
	    nod *p=root;
	    while(p->r)
	    	p=p->r;
	    p->r=new nod(num,p);
	    splay(p->r);
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
	void prn(){
		prn(root);
	}
};
