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
class BinarySearchTree: public dynamicSearchTable<KEY, OTHER>{
private:
    struct BinaryNode{
        SET<KEY, OTHER>data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const SET<KEY, OTHER>& thedata, BinaryNode* lt = NULL, BinaryNode* rt = NULL):
        data(thedata), left(lt), right(rt){}
    };
    BinaryNode *root;

public:
    BinarySearchTree();
    ~BinarySearchTree();
    SET<KEY, OTHER> *find(const KEY&x)const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY& x);

private:
    void insert(const SET<KEY, OTHER> &x, BinaryNode *& t);
    void remove(const KEY& x, BinaryNode *& t);
    SET<KEY, OTHER> *find(const KEY&x, BinaryNode *t)const;
    void makeEmpty(BinaryNode *& t);
};

template<class KEY, class OTHER>
SET<KEY, OTHER>* BinarySearchTree<KEY, OTHER>::find(const KEY &x, BinaryNode* t) const {
    if (t == NULL || t->data.key == x)
        return (SET<KEY, OTHER>*)t;
    if (t->data.key > x)
        return find(x, t->left);
    else
        return find(x, t->right);
}

template<class KEY, class OTHER>
SET<KEY, OTHER>* BinarySearchTree<KEY, OTHER>::find(const KEY &x) const {
    return find(x, root);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, BinaryNode *&t) {
    if (t == NULL)
        t = new BinaryNode(x, NULL, NULL);
    else if (x.key < (t->data).key )
        insert(x, t->left);
    else insert(x, t->right);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x) {
    insert(x, root);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::remove(const KEY &x) {
    remove(x, root);
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::remove(const KEY &x, BinaryNode *&t) {
    if (t == NULL) return;
    if (x < t->data.key) remove(x, t->left);
    else if (x > t->data.key) remove(x, t->right);
    else if (t->left != NULL && t->right != NULL){
        BinaryNode *tmp = t->right;
        while (tmp->left != NULL) tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data.key, t->right);
    } else{
        BinaryNode *oldNode = t;
        t = (t->left != NULL)?t->left:t->right;
        delete oldNode;
        //???
    }
}
template<class KEY, class OTHER>
BinarySearchTree<KEY, OTHER>::BinarySearchTree() {
    root = NULL;
}

template<class KEY, class OTHER>
void BinarySearchTree<KEY, OTHER>::makeEmpty(BinaryNode *&t) {
    if (t == NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

template<class KEY, class OTHER>
BinarySearchTree<KEY, OTHER>::~BinarySearchTree(){
    makeEmpty(root);
}

int main() {
    SET<int, string>a[] = {{10, "aaa"}, {8, "bbb"}, {21, "ccc"},
                          {87, "ddd"}, {56, "eee"}, {4, "fff"},
                          {11, "ggg"}, {3, "hhh"}, {22, "iiii"}};
    BinarySearchTree<int, string>tree;
    SET<int, string>x, *p;

    for (int i = 0; i < 9; ++i) tree.insert(a[i]);

    p = tree.find(21);
    if (p) cout << "find 21 is "<< p->key << " " << p->other << endl;
    else cout << "not found" << endl;

    x.key = 31; x.other = "jjjj";
    tree.insert(x);
    p = tree.find(31);
    if (p) cout << "find 31 is "<< p->key << " " << p->other << endl;
    else cout << "not found" << endl;

    tree.remove(21);
    p = tree.find(21);
    if (p) cout << "find 21 is "<< p->key << " " << p->other << endl;
    else cout << "not found" << endl;

    return 0;
}
