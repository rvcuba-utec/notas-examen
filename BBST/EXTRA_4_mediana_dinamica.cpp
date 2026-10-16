/*
EXTRA-4. Mediana Dinámica
Dado un flujo de números, mantener la mediana después de cada inserción o borrado.
  1 x: insertar x. Imprimir la mediana actual.
  2 x: borrar x (garantizado existe). Imprimir la mediana actual.
  3:   imprimir la mediana actual (sin modificar el conjunto).

La mediana de n elementos es el elemento en la posición ceil(n/2) cuando están ordenados.
Si n=0, responder "VACIO".

Estrategia: usar dos heaps (max-heap izquierdo, min-heap derecho), o AVL con kth.
Aquí usamos un AVL augmentado con subtree_cnt y kth.

Input:
  q (1 <= q <= 5*10^5)
  q líneas: 1 x, 2 x, o 3

Output: una línea por cada operación (la mediana actual después de cada op).

Example:
Input:
7
1 5
1 3
1 8
3
2 5
1 1
3

Output:
5
3
5
5
3
3
3
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
    int n = 0;

    int h(Node* u) { return u ? u->h : -1; }
    int c(Node* u) { return u ? u->cnt : 0; }
    void upd(Node* u) { u->h = 1+max(h(u->l),h(u->r)); u->cnt = 1+c(u->l)+c(u->r); }

    Node* rl(Node* u){auto v=u->r;u->r=v->l;v->l=u;upd(u);upd(v);return v;}
    Node* rr(Node* u){auto v=u->l;u->l=v->r;v->r=u;upd(u);upd(v);return v;}
    Node* bal(Node* u){
        upd(u);
        if(h(u->l)-h(u->r)>1){if(h(u->l->l)<h(u->l->r))u->l=rl(u->l);return rr(u);}
        if(h(u->r)-h(u->l)>1){if(h(u->r->r)<h(u->r->l))u->r=rr(u->r);return rl(u);}
        return u;
    }
    Node* ins(Node* u, int v){if(!u)return new Node(v);if(v<u->data)u->l=ins(u->l,v);else u->r=ins(u->r,v);return bal(u);}
    void insert(int v){root=ins(root,v);n++;}

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
    void erase(int v){root=del(root,v);n--;}

    int kth(Node* u, int k){
        int lc=c(u->l);
        if(k==lc+1)return u->data;
        if(k<=lc)return kth(u->l,k);
        return kth(u->r,k-lc-1);
    }
    int median(){
        if(n==0)return -1;
        return kth(root,(n+1)/2);
    }
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
        if(T.n==0)cout<<"VACIO\n";
        else cout<<T.median()<<"\n";
    }
    return 0;
}
