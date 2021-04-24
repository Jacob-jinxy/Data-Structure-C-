#include <iostream>
#include <iostream>
using namespace std;

template<class KEY, class OTHER>
struct SET{
    KEY key;
    OTHER other;
};

template<class KEY, class OTHER>
class dynamicSearchTable{
public:
    virtual SET<KEY, OTHER> *find(const KEY&x)const = 0;
    virtual void insert(const SET<KEY, OTHER> &x) = 0;
    virtual ~dynamicSearchTable(){};
};

template<class KEY, class OTHER>
class AvlTree: public dynamicSearchTable<KEY, OTHER>{
    struct AvlNode{
        SET<KEY, OTHER> data;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const SET<KEY, OTHER>&element, AvlNode *lt, AvlNode *rt, int h = 1)
            : data(element), left(lt), right(rt), height(h){}
    };

    AvlNode *root;

public:
    AvlTree(){root = NULL;}
    ~AvlTree(){makeEmpty(root);}
    SET<KEY, OTHER> *find(const KEY&x) const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);

private:
    void insert(const SET<KEY, OTHER> &x, AvlNode *&t);
    bool remove(const KEY &x, AvlNode *&t);
    void makeEmpty(AvlNode *t);
    int height(AvlNode *t){return t == NULL ? 0 : t->height;}
    void LL(AvlNode *&t);
    void LR(AvlNode *&t);
    void RR(AvlNode *&t);
    void RL(AvlNode *&t);
    int max(int a, int b){return (a > b) ? a : b;}
    bool adjust(AvlNode *&t, int subTree);
};

template<class KEY, class OTHER>
SET<KEY, OTHER> *AvlTree<KEY, OTHER>::find(const KEY &x) const {
    AvlNode *t = root;

    while (t != NULL && t->data.key != x)
        if (t->data.key > x) t = t->left;
        else t = t->right;

    if (t == NULL) return NULL;
    else return (SET<KEY, OTHER> *)t;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(AvlNode *&t) {
    AvlNode *t1 = t->left;
    t->left = t1->right;
    t1->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t->left), height(t)) + 1;
    t = t1; //It is very important so that the new node can be connected with the parental tree.
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode *&t) {
    AvlNode *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t->right), height(t)) + 1;
    t = t1;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(AvlNode *&t) {
    RR(t->left);
    LL(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(AvlNode *&t) {
    LL(t->right);
    RR(t);
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
    insert(x, root);
}
template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, AvlNode *&t) {
    if (t == NULL)
        t = new AvlNode(x, NULL, NULL);
    else if (x.key < t->data.key){
        insert(x, t->left);
        if (height(t->left) - height(t->right) == 2)
        {if (x.key < t->left->data.key) LL(t); else LR(t);}
    }
    else if (x.key > t->data.key){
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2)
        {if (x.key > t->left->data.key) RR(t); else RL(t);}
    }

    t->height = max(height(t->left), height(t->right)) + 1;
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::remove(const KEY &x) {
    remove(x, root);
}

template<class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::remove(const KEY &x, AvlNode *&t) {
    if (t == NULL) return true;
    if (x == t->data.key){
        if (t->left == NULL || t->right == NULL){
            AvlNode *oldNode = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete oldNode;
            return false;
        } else{                     //被删结点有两个儿子
            AvlNode *tmp = t->right;
            while (tmp->left != NULL) tmp = tmp->left;
            t->data = tmp->data;
            if (remove(tmp->data.key, t->right)) return true;   //删除后右子树没有变矮
            return adjust(t, 1);
        }

    }
    if (x < t->data.key){                   //在左子树上删除
        if (remove(x, t->left)) return true;
        return adjust(t, 0);
    } else{
        if (remove(x, t->right)) return true;
        return adjust(t, 1);
    }
}


template<class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode *&t, int subTree) {
    if (subTree){                       //在右子树上删除，使右子树变矮
        if (height(t->left) - height(t->right) == 1) return true;
        if (height(t->left) == height(t->right)) return false;
        if (height(t->left->right) > height(t->left->left)){
            LR(t);
            return false;
        }
        LL(t);
        if (height(t->right) == height(t->left)) return false; else return true;
    } else{
        if (height(t->right) - height(t->left) == 1) return true;
        if (height(t->right) == height(t->left)) return false;
        if (height(t->right->left) > height(t->right->right)){
            RL(t);
            return false;
        }
        RR(t);
        if (height(t->right) == height(t->left)) return false; else return true;
    }
}

template<class KEY, class OTHER>
void AvlTree<KEY, OTHER>::makeEmpty(AvlNode *t) {
    if (t == NULL) return;
    makeEmpty(t->right);
    makeEmpty(t->left);
    delete t;
}

int main() {
    SET<int, string> a[] = {{10, "aaa"}, {8, "bbb"}, {88, "ccc"}, {26, "ddd"}};
    AvlTree<int, string> tree;

    SET<int, string> x;
    SET<int, string> *p;

    for (int i = 0; i < 4; ++i) {
        tree.insert(a[i]);
    }

    p = tree.find(26);
    if (p) cout << "fins 26 is   " << p->key << "   " << p->other << endl;
    else cout << "not found" << endl;

    tree.remove(26);
    p = tree.find(26);
    if (p) cout << "fins 26 is" << p->key << "   " << p->other << endl;
    else cout << "not found" << endl;
    return 0;

}
