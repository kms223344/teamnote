struct Node
{
    Node *p, *l, *r;
    int cnt;
    ll val; ll m, M, sum; ll lazy;
    bool flip; bool dum;
    
    Node(ll val, bool dum = false):p(0),l(0), r(0), cnt(1), val(val), m(val), M(val), sum(val), lazy(0), flip(0), dum(dum){}
    
    void fix(){
        cnt = 1+(l?l->cnt:0)+(r?r->cnt:0);
        sum = val+(l?l->sum:0)+(r?r->sum:0);
        m = min({val, (l?l->m:inf), (r?r->m:inf)});
        M = max({val, (l?l->M:-1), (r?r->M:-1)});
    }
    void prop(){
        if(flip){
            swap(l, r);
            if(l) l->flip = !l->flip;
            if(r) r->flip = !r->flip;
            
            flip = false;
        }
        if(lazy){
            val += lazy; sum += cnt * lazy;
            if(l) l->lazy += lazy;
            if(r) r->lazy += lazy;
            
            lazy = 0;
        }
    }
    
} *root;

// 자기보다 더 높은 노드를 루트로 하는 SplayTree를 조작하는 경우, 하위 SplayTree는 unvalid된다.
struct SplayTree{
    Node *root = NULL, *rp = NULL;
    
    SplayTree(){}
    SplayTree(Node *rt){
        if(!rt) return;
        
        root = rt;
        rp = rt->p;
    }
    
    void mop(Node *node){
        if(node == root) node->prop();
        else mop(node->p);
        
        if(node->l) node->l->prop();
        if(node->r) node->r->prop();
    }
    
    void rotate(Node *node){
        if(!root) return;
        
        if(node->p == rp) return;
        if(node->p->l == node){
            Node *p = node->p, *g = p->p;
            Node *a = node->l, *b = node->r, *c = p->r;
            
            p->l = b; if(b) b->p = p;
            p->r = c; if(c) c->p = p;
            
            node->l = a; if(a) a->p = node;
            node->r = p; p->p = node;
            
            node->p = g; if(g) (g->l == p?g->l:g->r) = node;
            
            p->fix(); node->fix();
            
            if(p == root) root = node;
        }
        else{
            Node *p = node->p, *g = p->p;
            Node *a = p->l, *b = node->l, *c = node->r;
            
            p->l = a; if(a) a->p = p;
            p->r = b; if(b) b->p = p;
            
            node->l = p; p->p = node;
            node->r = c; if(c) c->p = node;
            
            node->p = g; if(g) (g->l == p?g->l:g->r) = node;
            
            p->fix(); node->fix();
            
            if(p == root) root = node;
        }
    
    }
    
    void splay(Node* node){
        if(!root) return;
        assert(node); mop(node);
        
        while(node->p != rp){
            Node *p, *g;
            p = node->p; g = p->p;
            
            if(g == rp) rotate(node);
            else if((p->l == node) == (g->l == p)) rotate(p), rotate(node);
            else rotate(node), rotate(node);
        }
        
        root = node;
    }
    
    Node* insert(ll val, bool dum = false){
        if(!root){
            root = new Node(val, dum);
            return root;
        }
        else{
            Node *now = root;
            while(now->r) now = now->r;
            Node* ret = now->r = new Node(val, dum);
            now->r->p = now;
            
            splay(ret); return ret;
        }
    }
    
    Node* find_kth(int k) { // 0-indexed
        assert(root);
        assert(root->cnt > k);
        Node *now = root; now->prop();
        while(true){
            while(now->l and now->l->cnt > k) now = now->l, now->prop();
            k -= now->l?now->l->cnt:0;
            
            if(k == 0) break;
            k--; now = now->r;
            now->prop();
        }
        
        splay(now);
        return now;
    }
    // s-1, e+1번째 노드가 항상 존재해야 한다.
    Node* gather(int s, int e){
        find_kth(e+1);
        SplayTree(root->l).find_kth(s-1);
        
        assert(root->l->r);
        return root->l->r;
    }
    void update(int i, int j, ll val){
        Node *node = gather(i, j);
        
        node->lazy += val; node->prop(); 
        node->p->fix(); node->p->p->fix();
    }
    void reverse(int i, int j){
        Node *node = gather(i, j);
        node->flip = !node->flip;
    }
    
    void p_vals(){p_vals(root, 0, false);}
    void p_vals(Node* node, ll lz, bool flip){
        lz += node->lazy; flip ^= node->flip;
        if(!flip){
            if(node->l) p_vals(node->l, lz, flip);
            if(!node->dum) printf("%lld ", node->val+lz);
            if(node->r) p_vals(node->r, lz, flip);
        }
        else{
            if(node->r) p_vals(node->r, lz, flip);
            if(!node->dum) printf("%lld ", node->val+lz);
            if(node->l) p_vals(node->l, lz, flip);
        }
    }
};