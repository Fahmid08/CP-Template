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
struct line{
    ll slope, y_interp;
    ll val(int x) {return slope*x+y_interp;}
};
struct cht{
    ll intersect(line l1, line l2) {return ceil(1.0000*(l2.y_interp-l1.y_interp)/(l1.slope-l2.slope));}
    deque<pair<line,ll>> hull;
    void insert(line l){
        while(!hull.empty() && intersect(l,hull.back().first)<hull.back().second) hull.pop_back();
        if(!hull.empty()) hull.push_back({l,intersect(l,hull.back().first)});
        else hull.push_back({l,-1});
    }
    ll query(int x){
        while(hull.size()>1 && hull[1].second<=x) hull.pop_front();
        return hull[0].first.val(x);
    }
};
inline void solve(){
    ll n,C; cin>>n >>C;
    vector<ll> h(n); //height of the stones
    rep(i,0,n) cin>>h[i]; 
    cht H;
    line l;
    l.slope=-2*h[0]; l.y_interp=h[0]*h[0];
    H.insert(l);
    rep(i,1,n){
        ll dp=H.query(h[i])+h[i]*h[i]+C;
        if(i==n-1){cout<<dp; return;}
        l.slope=-2*h[i];
        l.y_interp=dp+h[i]*h[i];
        H.insert(l);
    }
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t=1; //cin>>t;
    for(int i=0;i<t;++i){
        //cout<<"Case "<<i+1<<": "<<'\n';
        solve();
    }
}