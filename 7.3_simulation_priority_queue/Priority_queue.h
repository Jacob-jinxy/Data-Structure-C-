//
// Created by Macbook pro on 2021/4/19.
//

#ifndef INC_7_3_SIMULATION_PRIORITY_QUEUE_PRIORITY_QUEUE_H
#define INC_7_3_SIMULATION_PRIORITY_QUEUE_PRIORITY_QUEUE_H
#include <iostream>
using namespace std;

template <class elemType>
class queue{
public:
    virtual bool isEmpty()const = 0;
    virtual void enQueue(const elemType &x) = 0;
    virtual elemType deQueue() = 0;
    virtual elemType getHead() const = 0;
    virtual ~queue(){};
};

template <class Type>
class priorityQueue: public queue<Type>{
public:
    priorityQueue(int capacity = 100);
    priorityQueue(const Type data[], int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const Type &x);
    Type deQueue();
    Type getHead() const;

private:
    int currentSize;
    Type *array;
    int maxSize;

    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
};

template <class Type>
priorityQueue<Type>::priorityQueue(int capacity) {
    array = new Type[capacity];
    maxSize = capacity;
    currentSize = 0;
}
template <class Type>
priorityQueue<Type>::~priorityQueue() {
    delete []array;
}

template <class Type>
bool priorityQueue<Type>::isEmpty() const {
    return currentSize == 0;
}

template <class Type>
Type priorityQueue<Type>::getHead() const {
    return array[1];
}

template <class Type>
void priorityQueue<Type>::enQueue(const Type &x) {
    if (currentSize == maxSize - 1) doubleSpace();

    //向上过滤
    int hole = ++currentSize;
    for(; hole > 1 && x < array[hole/2]; hole /= 2)
        array[hole] = array[hole / 2];
    array[hole] = x;
}

template <class Type>
Type priorityQueue<Type>::deQueue() {
    Type minItem;
    minItem = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return minItem;
}

template <class Type>
void priorityQueue<Type>::percolateDown(int hole) {
    int child;
    Type tmp = array[hole];

    for (; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;
        if (child != currentSize && array[child + 1] < array[child])//左儿子大
            child++;//左右结点中较小的那一个
        if (array[child] < tmp) array[hole] = array[child];
        else break;
    }
    array[hole] = tmp;
}

template <class Type>
void priorityQueue<Type>::buildHeap() {
    for (int i = currentSize / 2; i > 0; i--)
        percolateDown(i);
}

template <class Type>
priorityQueue<Type>::priorityQueue(const Type *data, int size) :maxSize(size + 10), currentSize(size){
    array = new Type[maxSize];
    for (int i = 0; i < size; ++i)
        array[i + 1] = data[i];
    buildHeap();
}

template <class Type>
void priorityQueue<Type>::doubleSpace() {
    Type *tmp = array;
    maxSize *= 2;
    array = new Type[maxSize];
    for (int i = 0; i <= currentSize; ++i)
        array[i] = tmp[i];
    delete []tmp;
}
#endif //INC_7_3_SIMULATION_PRIORITY_QUEUE_PRIORITY_QUEUE_H
