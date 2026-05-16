#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
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
int mx;
vector<vector<int>> up, child;
vector<int> level;
void dfs(int p, int l){
    level[p]=l;
    for(int i=1;(1<<i)<=l;++i){
        up[p][i]=up[ up[p][i-1] ][i-1];
    }
    for(auto c:child[p]){
        dfs(c,l+1);
    }
}
inline int ancestor(int u, int k){
    int ind=0;
    while(k!=0){
        if((k&1)) u=up[u][ind];
        k/=2;
        ind++;
    }
    return u;
}
int lca(int u, int v){
    if(level[v]>level[u]) swap(u,v);
    if(level[u]>level[v]){
        //replace u by (level[v]-level[u])th ancestor of u
        u=ancestor(u,level[u]-level[v]);
    }
    if(u==v) return u;
    for(int i=mx-1; i>=0;--i){
        if(up[u][i]!=up[v][i]){
            u=up[u][i];
            v=up[v][i];
        }
    }
    return up[u][0];
}
inline void solve(){
    int n; cin>>n;
    mx=32-__builtin_clz(n);
    up=vector<vector<int>> (n,vector<int>(mx,0));
    level.resize(n);
    child.resize(n);
    for(int i=0;i<n;++i){
        int sz; cin>>sz;
        for(int j=0;j<sz;++j){
            int c; cin>>c;
            up[c][0]=i;
            child[i].push_back(c);
        }
    }
    dfs(0,0);
    int q; cin>>q;
    while(q-->0){
        int u,v; cin>>u >>v;
        cout<<lca(u,v)<<'\n';
    }
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t=1; //cin>>t;
    while(t-->0){
        solve();
    }
}
//time comp: O(n*log(n) + q*(log(n))^2)
//memory comp: O(n + n*log(n))