#include<bits/stdc++.h>
using namespace std;

using ll=long long;
using ull=unsigned long long;

#define rep(i,a,b) for(int i=(a); i<(b); ++i)
#define all(array) array.begin(), array.end()
#define bitcnt(x) ((sizeof(x) <= sizeof(int)) ? (32 - __builtin_clz(x)) : (64 - __builtin_clzll(x)))

#define OJ
#ifndef OJ
#define debug(x) cerr<<"line "<<__LINE__<<": "<<#x<<" "; _print(x); cerr<<'\n';
#else
#define debug(x)
#endif

template<class T> void _print(T a);
template<class T, class V> void _print(pair<T, V> &p);
template<class T> void _print(vector<T> &a);
template<class T> void _print(set<T> &s);
template<class T, class V> void _print(map<T, V> &mp);
template<class T> void _print(deque<T> &d);
template<class T> void _print(stack<T> st);
template<class T> void _print(queue<T> q);
template<class T> void _print(priority_queue<T> pq);

template<class T> void _print(T a){cerr<<a;}
template<class T, class V> void _print(pair<T, V> &p){cerr<<"{"; _print(p.first); cerr<<", "; _print(p.second); cerr<<"}";}
template<class T> void _print(vector<T> &a){cerr<<"[ "; for(auto c:a){_print(c);cerr<<" ";} cerr<<"]";}
template<class T> void _print(set<T> &s){cerr<<"[ "; for(auto c:s){_print(c);cerr<<" ";} cerr<<"]";}
template<class T, class V> void _print(map<T, V> &mp){cerr<<"[ ";for(auto c:mp){_print(c); cerr<<" ";} cerr<<"]";}
template<class T> void _print(deque<T> &d){cerr<<"[ "; for(auto c:d){_print(c); cerr<<" ";} cerr<<"]";}
template<class T> void _print(stack<T> st){cerr<<"| "; while(!st.empty()){auto c=st.top(); st.pop(); _print(c); cerr<<" ";} cerr<<"|";}
template<class T> void _print(queue<T> q){cerr<<"( "; while(!q.empty()){auto c=q.front(); q.pop(); _print(c); cerr<<" ";} cerr<<")";}
template<class T> void _print(priority_queue<T> pq){cerr<<"< ";while(!pq.empty()){auto c=pq.top(); pq.pop(); _print(c); cerr<<" ";} cerr<<">";}
//===============================================================MAIN CODE=============================================================================================
struct vertex{
    vertex *l, *r;
    ll sum;
    vertex(int val):sum(val){}
    vertex(vertex *l, vertex *r):l(l),r(r){
        sum=l->sum + r->sum;
    }
};
vertex* build(const vector<int>&a, int low, int high){
    if(low==high) return new vertex(a[low]);
    int mid=(low+high)/2;
    return new vertex(build(a,low,mid),build(a,mid+1,high));
}
ll get_sum(const vertex *v, int low, int high, int l, int r){
    if(high<l||low>r) return 0;
    if(low>=l && high<=r) return v->sum;
    int mid=(low+high)/2;
    return get_sum(v->l,low,mid,l,r)+get_sum(v->r,mid+1,high,l,r);
}
vertex* update(const vertex *v, int low, int high, int pos, int val){
    if(low==high) return new vertex(val);
    int mid=(low+high)/2;
    if(pos<=mid) return new vertex(update(v->l, low, mid, pos, val),v->r);
    return new vertex(v->l, update(v->r,mid+1,high,pos,val));
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,q; cin>>n >>q;
    vector<int> a(n);
    vector<vertex*> version;
    rep(i,0,n) cin>>a[i];
    version.emplace_back(build(a,0,n-1));
    while(q--){
        int op,k; cin>>op >>k; --k;
        if(op==1){
            int a,x; cin>>a >>x; --a;
            version[k]=update(version[k],0,n-1,a,x);
        }
        else if(op==2){
            int a,b; cin>>a >>b; --a; --b;
            cout<<get_sum(version[k],0,n-1,a,b)<<'\n';
        }
        else version.emplace_back(version[k]);
    }
    return 0;
}