namespace GMS
{
    template<typename D, D (*join)(D,D), D _e>
    class Segtree {
        class Node {
            Node *l, *r;
            int s,e; D v;
        public:
            Node(int s, int e) :l(0), r(0), s(s), e(e), v(_e){};
            ~Node(){delete l; delete r;}
            
            template<typename Dini>
            friend void init(Node* node, Dini arr[] = NULL) {
                int s = node->s, e=node->e, mid=(s+e)/2;
                if(s == e) {
                    node->v = D(arr?arr[s]:_e);
                    return;
                }
                
                node->l = new Node(s, mid);
                init(node->l, arr);
                node->r = new Node(mid+1, e);
                init(node->r, arr);
                
                node->v = join(node->l->v, node->r->v);
            }
            friend D _query(Node* node, int a, int b) {
                int s=node->s, e=node->e;
                if(a <= s and e <= b) return node->v;
                if(b < s or e < a) return _e;
                
                return join(_query(node->l, a, b), _query(node->r, a, b));
            }
            friend void _update
                      (Node* node, int i, function<D(D)> upd) {
                int s=node->s, e=node->e;
                if(i < s or e < i) return;
                if(s == e)
                {
                    node->v = upd(node->v);
                    return;
                }
                
                _update(node->l, i, upd);
                _update(node->r, i, upd);
                
                node->v = join(node->l->v, node->r->v);
            }
        };
        
        Node *root;
    public:
        template<typename Dini>
        Segtree(int s,int e, Dini arr[] = NULL) {
            root = new Node(s, e);
            init(root, arr);
        }
        ~Segtree(){delete root;}
        D query(int s, int e)
                          {return _query(root, s, e);}
        void update(int i, function<D(D)> upd)
                          {_update(root, i, upd);}
    };
    
    
    template<typename D, D (*join)(D,D), D _e, typename L, D (*apply)(D, L, int), L (*give)(L, L), L _l>
    class LZSegtree {
        class Node {
            Node *l, *r;
            int s,e;
            D v; L lz;
            
            void prop() {
                v = apply(v, lz, e-s+1);
                if(l) l->lz = give(l->lz, lz);
                if(r) r->lz = give(r->lz, lz);
                
                lz = _l;
            }
            
        public:
            Node(int s, int e)
                  :l(0), r(0), s(s), e(e), v(_e), lz(_l){};
            ~Node(){delete l; delete r;}
            
            template<typename Dini>
            friend void init(Node* node, Dini arr[] = NULL) {
                int s = node->s, e=node->e, mid=(s+e)/2;
                if(s == e)
                {
                    node->v = D(arr?arr[s]:_e);
                    return;
                }
                
                node->l = new Node(s, mid);
                init(node->l, arr);
                node->r = new Node(mid+1, e);
                init(node->r, arr);

                node->v = join(node->l->v, node->r->v);
            }
            friend D _query(Node* node, int a, int b) {
                node->prop();
                int s=node->s, e=node->e;
                if(a <= s and e <= b) return node->v;
                if(b < s or e < a) return _e;
                
                return join(_query(node->l, a, b), _query(node->r, a, b));
            }
            friend void _update
               (Node* node, int a, int b, function<L(L)> upd){
                node->prop();
                int s=node->s, e=node->e;
                if(b < s or e < a) return;
                if(a <= s and e <= b)
                {
                    node->lz = upd(node->lz);
                    node->prop();
                    return;
                }
                
                _update(node->l, a, b, upd);
                _update(node->r, a, b, upd);
                
                node->v = join(node->l->v, node->r->v);
            }
        };
        
        Node *root;
    public:
        template<typename Dini>
        LZSegtree(int s,int e, Dini arr[] = NULL)
        {
            root = new Node(s, e);
            init(root, arr);
        }
        ~LZSegtree(){delete root;}
        D query(int s, int e){return _query(root, s, e);}
        void update(int s, int e, function<L(L)> upd){_update(root, s, e, upd);}
    };
} // namespace GMS

//////////////////////////////////////////////////////
#define data _data

struct data {
    int m, m_cnt;
    constexpr data(int m):m(m), m_cnt(1){}
    constexpr data(int m, int m_cnt):m(m), m_cnt(m_cnt){}
};
data join(data A, data B) {
    if(A.m == B.m) return data(A.m, A.m_cnt+B.m_cnt);
    if(A.m < B.m) return A;	
    else return B;
}
data apply(data A, int lz, int len)
                     {return {A.m+lz, A.m_cnt};}
int give(int a, int b){return a+b;}

using Seg = GMS::LZSegtree<data, join, {(int)1e9, 0}, int, apply, give, 0>;
