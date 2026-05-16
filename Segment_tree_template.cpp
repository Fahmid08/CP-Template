#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct segtree{
    int size;
    vector<ll> tree;
    void init(int n){
        size=32-__builtin_clz(n);
        if(n&(n-1)){size++;}
        size=(1<<size)-1;
        tree.assign(size,0);
    }
    void build(vector<int> &a, int n){
        for(int i=0; i<n; ++i){
            tree[size/2 + i]=a[i];
        }
        for(int i=size-1;i>0;--i){
            tree[(i-1)/2]+=tree[i];
        }
    }
    void set(int i, int v){
        int u=size/2 + i;
        tree[u]=v;
        while(u!=0){
            u=(u-1)/2;
            tree[u]=tree[2*u+1]+tree[2*u+2];
        }
    }
    void cng(int node, int node_l, int node_h, int i, int v){
        if(node_l==i && node_h==i){
            tree[node]=v;
            return;
        }
        if(node_h<i||node_l>i) return;
        int mid=node_l+(node_h-node_l)/2;
        cng(2*node+1,node_l,mid,i,v);
        cng(2*node+2,mid+1,node_h,i,v);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    void change(int i, int v){
        cng(0,0,size/2,i,v);
    }
    ll sum_calc(int l, int r, int node_l, int node_h, int node){
        if(node_h<l|| node_l>r){return 0;}
        if(node_l>=l && node_h<=r){return tree[node];}
        int mid=node_l+(node_h-node_l)/2;
        return sum_calc(l,r,node_l,mid,2*node+1)+sum_calc(l,r,mid+1,node_h,2*node+2);
    }
    ll sum(int l, int r){
        return sum_calc(l,r,0,size/2,0);
    }
};
int main(){
    ios::sync_with_stdio(0); cin.tie(nullptr);
    int n,q; cin>>n >>q;
    segtree st;
    st.init(n);
    vector<int> a(n);
    for(int i=0;i<n;++i){
        cin>>a[i];
    }
    st.build(a,n);
    while(q-->0){
        int op; cin>>op;
        if(op==1){
            int i,v; cin>>i >>v;
            st.change(i,v);
        }
        else{
            int l,r; cin>>l >>r;
            r--;
            cout<<st.sum(l,r)<<'\n';
        }
    }
}
