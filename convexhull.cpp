#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
struct point:public std::pair<long long,long long>{
    long long&x;
    long long&y;
    point():pair(),x(first),y(second){}
    point(long long a,long long b):pair(a,b),x(first),y(second){}
    point(const point&a):pair(a.x,a.y),x(first),y(second){}
    point operator-(point a){
        return point(x-a.x,y-a.y);
    }
    long long operator*(point a){
        return x*a.y-a.x*y;
    }
    point operator=(point a){
        x=a.x;
        y=a.y;
        return*this;
    }
};
#define ccw(a,b,c) ((b-a)*(c-b))
point arr[100100];
std::vector<point> con;
int main(){
    int n,i,mini=0;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%lld %lld",&arr[i].x,&arr[i].y);
        if(arr[mini].x>arr[i].x||arr[mini].x==arr[i].x&&arr[mini].y>arr[i].y)
            mini=i;
    }
    std::swap(arr[mini],arr[0]);
    std::sort(arr+1,arr+n,[](point a,point b){return ccw(arr[0],a,b)?ccw(arr[0],a,b)>0:(a.x==b.x?a.y<b.y:a.x<b.x);});
    con.push_back(arr[0]);
    for(i=1;i<n;i++){
        while(con.size()>1&&ccw(con[con.size()-2],con[con.size()-1],arr[i])<=0)
            con.pop_back();
        con.push_back(arr[i]);
    }
    printf("%d\n",con.size());
    return 0;
}
