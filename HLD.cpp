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
struct segtree{
    int sz;
    vector<int> tree;
    segtree()=default;
    segtree(int n): sz(bitcnt(n)+((n&(n-1))!=0)){
        sz=(1<<sz)-1;
        tree.resize(sz);
    }
    void upd(int i, int v){
        int u=sz/2 + i;
        tree[u]=v;
        while(u!=0){
            u=(u-1)/2;
            tree[u]=tree[2*u+1]^tree[2*u+2];
        }
    }
    int get(int x, int low, int high, int l, int r){
        if(low>r||high<l) return 0;
        if(low>=l && high<=r) return tree[x];
        int mid=(low+high)/2;
        return get(2*x+1,low,mid,l,r)^get(2*x+2,mid+1,high,l,r);
    }
    int calc(int l, int r){
        return get(0,0,sz/2,l,r);
    }
};
struct graph{
    int curr=0,LOG;
    vector<int> depth,sz,label,val,start, par;
    vector<bool> heavy;
    vector<vector<int>> adj,up;
    segtree st;
    void dfs1(int u, int p){
        ++sz[u];
        int h,mx=-1;
        for(int c:adj[u]){
            if(c==p) continue;
            dfs1(c,u);
            sz[u]+=sz[c];
        }
    }
    void dfs2(int u, int p, int d){
        par[u]=p;
        depth[u]=d;
        label[u]=curr;
        st.upd(label[u],val[u]);
        ++curr;
        up[u][0]=p;
        rep(i,1,LOG) up[u][i]=up[up[u][i-1]][i-1];
        int h,mx=-1;
        for(int c:adj[u]){
            if(c!=p){
                if(sz[c]>mx){h=c; mx=sz[c];}
            }
        }
        if(mx!=-1) {start[h]=start[u]; heavy[h]=1; dfs2(h,u,d+1);}
        for(int c:adj[u]){
            if(c==p||c==h) continue;
            dfs2(c,u,d+1);
        }
    }
    graph(int n, vector<vector<int>> &adj,vector<int> &val):LOG(bitcnt(n)),adj(adj),val(val){
        depth.resize(n); sz.resize(n); label.resize(n); start.resize(n); heavy.resize(n); par.resize(n);
        iota(all(start),0);
        up=vector<vector<int>>(n,vector<int>(LOG));
        st=segtree(n);
        dfs1(0,0);
        dfs2(0,0,0);
    }
    int ancestor(int u, int k){
        int i=0;
        while(k!=0){
            if(k&1) u=up[u][i];
            k/=2;
            i++;
        }
        return u;
    }
    int lca(int a, int b){
        if(depth[b]>depth[a]) swap(a,b);
        a=ancestor(a,depth[a]-depth[b]);
        if(a==b) return a;
        for(int i=LOG-1; i>=0; --i){
            if(up[a][i]!=up[b][i]){
                a=up[a][i];
                b=up[b][i];
            }
        }
        return up[a][0];
    }
    void upd(int x, int v){
        st.upd(label[x],v);
        val[x]=v;
    }
    int vert_calc(int a, int b){ //calculate the function for the nodes in the vertical path from a to b.
        if(depth[b]>depth[a]) swap(a,b);
        if(a==b) return val[a];
        int x=start[a];
        if(depth[x]<=depth[b]) return st.calc(label[b],label[a]);
        return st.calc(label[x],label[a])^vert_calc(par[x],b);
    }
    int calc(int a, int b){
        int l=lca(a,b);
        return vert_calc(a,l)^vert_calc(b,l)^val[l];
    }
};
inline void solve(){
    int n,q; cin>>n >>q;
    vector<vector<int>> adj(n);
    vector<int> val(n);
    rep(i,0,n) cin>>val[i];
    rep(i,0,n-1){
        int u,v; cin>>u >>v; u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    graph g(n,adj,val);
    while(q-->0){
        int op,l,r; cin>>op >>l >>r;
        if(op==1){
            l--;
            g.upd(l,r);
            continue;
        }
        l--; r--;
        cout<<g.calc(l,r)<<'\n';
    }
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    freopen("cowland.in","r",stdin);
    freopen("cowland.out","w",stdout);
    int t=1; //cin>>t;
    for(int i=0;i<t;++i){
        //cout<<"Case "<<i+1<<": "<<'\n';
        solve();
    }
}