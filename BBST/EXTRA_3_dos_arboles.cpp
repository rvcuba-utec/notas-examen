/*
EXTRA-3. Split en AVL
Conjunto dinámico de enteros con operaciones:
  1 x: insertar x.
  2 x: eliminar x.
  3 k: SPLIT en k: quedarse solo con los elementos <= k.
        Imprimir cuántos elementos quedan.
  4:   imprimir el mínimo y máximo del conjunto (o "VACIO" si está vacío).

Input:
  q (1 <= q <= 2*10^5)
  q líneas: op [args]

Output: línea por cada op 3 y 4.

Example:
Input:
9
1 5
1 3
1 8
1 1
4
3 5
4
1 7
4

Output:
1 8
3
1 5
1 7
*/
#include<bits/stdc++.h>
using namespace::std;

struct AVL {
    struct Node {
        int h, data, cnt;
        Node *l, *r;
        Node(int d) : h(0), data(d), cnt(1), l(nullptr), r(nullptr) {}
    };
    Node* root = nullptr;

    int h(Node* u) { return u ? u->h : -1; }
    int c(Node* u) { return u ? u->cnt : 0; }
    void upd(Node* u) { u->h = 1+max(h(u->l),h(u->r)); u->cnt = 1+c(u->l)+c(u->r); }

    Node* rl(Node* u){auto v=u->r;u->r=v->l;v->l=u;upd(u);upd(v);return v;}
    Node* rr(Node* u){auto v=u->l;u->l=v->r;v->r=u;upd(u);upd(v);return v;}
    Node* bal(Node* u){
        upd(u);
        if(h(u->l)-h(u->r)>1){if(h(u->l->r)>h(u->l->l))u->l=rl(u->l);return rr(u);}
        if(h(u->r)-h(u->l)>1){if(h(u->r->l)>h(u->r->r))u->r=rr(u->r);return rl(u);}
        return u;
    }
    Node* ins(Node* u, int v){if(!u)return new Node(v);if(v<u->data)u->l=ins(u->l,v);else u->r=ins(u->r,v);return bal(u);}
    void insert(int v){root=ins(root,v);}

    Node* mn(Node* u){while(u->l)u=u->l;return u;}
    Node* del(Node* u, int v){
        if(!u)return nullptr;
        if(v<u->data)u->l=del(u->l,v);
        else if(v>u->data)u->r=del(u->r,v);
        else{
            if(!u->l||!u->r){auto ch=u->l?u->l:u->r;delete u;return ch;}
            auto s=mn(u->r);u->data=s->data;u->r=del(u->r,s->data);
        }
        return bal(u);
    }
    void erase(int v){root=del(root,v);}

    // collect all elements <= k in order
    void collect_leq(Node* u, int k, vector<int>& res){
        if(!u) return;
        if(u->data > k){
            collect_leq(u->l, k, res);
        } else {
            collect_leq(u->l, k, res);
            res.push_back(u->data);
            if(u->data < k) collect_leq(u->r, k, res);
        }
    }

    void keep_leq(int k){
        vector<int> elems;
        collect_leq(root, k, elems);
        root = nullptr;
        for(int v : elems) root = ins(root, v);
    }

    int size(){ return c(root); }
    bool empty(){ return root == nullptr; }
    int min_val(){ auto u=root; while(u->l)u=u->l; return u->data; }
    int max_val(){ auto u=root; while(u->r)u=u->r; return u->data; }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q; cin>>q;
    AVL T;
    while(q--){
        int op; cin>>op;
        if(op==1){int x;cin>>x;T.insert(x);}
        else if(op==2){int x;cin>>x;T.erase(x);}
        else if(op==3){
            int k;cin>>k;
            T.keep_leq(k);
            cout<<T.size()<<"\n";
        } else {
            if(T.empty()) cout<<"VACIO\n";
            else cout<<T.min_val()<<" "<<T.max_val()<<"\n";
        }
    }
    return 0;
}
