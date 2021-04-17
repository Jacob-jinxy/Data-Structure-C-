#include <iostream>
using namespace std;

template<class Type>
class hfTree{
private:
    struct Node{
        Type data;
        int weight;
        int parent, left, right;
    };

    Node *elem;
    int length;
public:
    struct hfCode{
        Type data;
        string code;
    }; //公用的储存结果的数组，在主函数中定义，传到getCode函数中去

    hfTree(const Type*x, const int *w, int size);
    void getCode(hfCode result[]);
    ~hfTree(){delete []elem;}

};

template<class Type>
hfTree<Type>::hfTree(const Type *v, const int *w, int size) {

    const int MAX_INT = 32767;
    int min1, min2;
    int x, y;

    length = 2 * size;
    elem = new Node[length];

    for (int i = size; i < length; ++i) {//初始化
        elem[i].weight = w[i - size];
        elem[i].data = v[i - size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }

    //归并
    for (int i = size - 1;  i > 0; --i) {
        min1 = min2 = MAX_INT;
        x = y = 0;
        for (int j = i + 1; j < length; ++j){
            if (elem[j].parent == 0)//还未归并
            {
                if (elem[j].weight < min1){
                    //元素最小
                    min2 = min1;
                    min1 = elem[j].weight;
                    x = y;
                    y = j;   //最小的在右子结点
                }
                else if (elem[j].weight < min2){
                    min2 = elem[j].weight;
                    x = j;
                }
            }
        }

        elem[i].weight = min1 + min2;
        elem[i].left = x;
        elem[i].right = y;
        elem[i].parent = 0;
        elem[x].parent = i;
        elem[y].parent = i;
    }


}

template<class Type>
void hfTree<Type>::getCode(hfCode *result) {
    int size = length / 2;
    int p, s;//s是追溯过程中正在处理的结点，p是s的父节点下标;
    for (int i = size; i < length; ++i) {
        result[i - size].data = elem[i].data;
        result[i - size].code = "";
        p = elem[i].parent; s=i;

        while (p){
            if (elem[p].left == s)
                result[i - size].code  = '0' + result[i - size].code;
            else result[i - size].code  = '1' + result[i - size].code;
            s = p;
            p = elem[p].parent;

        }
    }

    cout<<"finished"<<endl;
}




int main() {
    char ch[]={"aeistop"};
    int w[] = {10, 15, 12, 3, 4, 13, 1};

    hfTree<char> tree(ch, w, 7);
    hfTree<char>::hfCode result[7];//类中定义的struct如何引用

    tree.getCode(result);

    for (int i = 0; i < 7; ++i) {
        cout << result[i].data << "  " << result[i].code << endl;
    }

    return 0;
}
