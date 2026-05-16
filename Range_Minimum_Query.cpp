#include<bits/stdc++.h>
using namespace std;

using ll=long long;
using ull=unsigned long long;

#define rep(i,a,b) for(int i=(a); i<(b); ++i)
#define all(array) array.begin(), array.end()
#define bitcnt(x) ((sizeof(x) <= sizeof(int)) ? (32 - __builtin_clz(x)) : (64 - __builtin_clzll(x)))

//#define OJ
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
//intro to sparse table
inline void solve(){
    int n,q; cin>>n >>q;
    vector<vector<int>> mn(n,vector<int>(bitcnt(n))); //mn[i][j]=minimum of the range starting with index-i and length 2^j
    rep(i,0,n){
        cin>>mn[i][0];
    }
    rep(j,1,bitcnt(n)){ //pre-computation
        for(int i=0;i+(1<<j)-1<n;++i){
            mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
        }
    }
    rep(i,0,q){
        int l,r; cin>>l >>r; l--; r--;
        int x=bitcnt(r-l+1)-1;
        cout<<min(mn[l][x],mn[r-(1<<x)+1][x])<<'\n';
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