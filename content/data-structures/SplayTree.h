/**
 * Author: Thieu Nguyen Huy
 * Description: Splay tree to find add element, remove element and get the k-th element
 * Time: O(\log N) on average for each operation
 * Status: Tested on SPOJ
 */

struct Node {
    Node *parent, *child[2];
    int sz, value;
 
    Node(int _value = 0) {
        parent = child[0] = child[1] = nullptr;
        sz = 1, value = _value;
    }
 
    int get_dir(Node *x) {
        for (int i = 0; i < 2; ++i) if (child[i] == x) {
            return i;
        }
        return -1;
    }
 
    void push_up() {
        sz = 1;
        for (int i = 0; i < 2; ++i)
            if (child[i] != nullptr) sz += child[i]->sz;
    }
};
 
const int MAX_NODES = 1e6 + 5;
Node nodes[MAX_NODES];
int numNode = 0;
 
Node *newNode(int _value = 0) {
    nodes[numNode] = Node(_value);
    return &nodes[numNode++];
}
 
struct SplayTree {
    Node *root;
 
    SplayTree(Node *_root = nullptr) {
        root = _root;
    }
 
    void link(Node *a, Node *b, int dir) {
        if (a == nullptr) {
            root = b;
            if (root != nullptr) root->parent = nullptr;
            return;
        }
        a->child[dir] = b;
        if (b != nullptr) b->parent = a;
    }
 
    void rotation(Node *a, int dir) { // rotate (a, a->child[dir])
        Node *b = a->child[dir];
        Node *c = a->parent;
        int pdir = (c != nullptr ? c->get_dir(a) : -1);
        link(a, b->child[!dir], dir);
        link(b, a, !dir);
        link(c, b, pdir);
    }
 
    void splay(Node *a) { // set root = a
        while (a->parent != nullptr) {
            Node *p = a->parent;
            int pdir = p->get_dir(a);
 
            if (p->parent == nullptr) { // zig
                rotation(p, pdir);
                p->push_up();
                a->push_up();
            }
            else  {
                Node *q = p->parent;
                int qdir = q->get_dir(p);
                if (pdir == qdir) { // zig-zig
                    rotation(q, qdir);
                    rotation(p, pdir);
                }
                else { // zig-zag
                    rotation(p, pdir);
                    rotation(q, qdir);
                }
 
                q->push_up();
                p->push_up();
                a->push_up();
            }
        }
    }
 
    void find_and_splay(int k) { // find the k-th number and splay to root
        Node *p = root;
        while (true) {
            int cntLeft = (p->child[0] == nullptr ? 0 : p->child[0]->sz);
 
            if (cntLeft >= k) p = p->child[0];
            else if (cntLeft + 1 >= k) {
                splay(p);
                return;
            }
            else {
                if (p->child[1] != nullptr) {
                    k -= cntLeft + 1;
                    p = p->child[1];
                }
                else {
                    splay(p);
                    return;
                }
            }
        }
    }
 
    void insert(int k, int value) {
        if (root == nullptr) {
            root = newNode(value);
            return;
        }
 
        Node *new_node = newNode(value);
        find_and_splay(k);
        
        if (k <= root->sz) {
            link(new_node, root->child[0], 0);
            link(root, new_node, 0);
            new_node->push_up();
            root->push_up();
        }
        else {
            link(root, new_node, 1);
            root->push_up();
        }
        splay(new_node);
    }
 
    void remove(int k) {
        find_and_splay(k);
        if (root->sz == 1) root = nullptr;
        else {
            int dir = (root->child[0] != nullptr ? 0 : 1);
            Node *p = root->child[dir];
            while (p->child[!dir] != nullptr) p = p->child[!dir];
 
            Node *other_child = root->child[!dir];
            root->child[dir]->parent = nullptr;
            if (p == root->child[dir]) root = p;
 
            splay(p);
            link(p, other_child, !dir);
            p->push_up();
        }
    }
 
    int get(int k) {
        find_and_splay(k);
        return root->value;
    }
} splaytree;