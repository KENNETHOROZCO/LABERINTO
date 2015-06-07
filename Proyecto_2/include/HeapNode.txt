#ifndef HEAPNODE_H
#define HEAPNODE_H
#include<Nodo.h>

class HeapNode
{
private:
    int key;
    Nodo *element;

public:
    HeapNode() {}
    ~HeapNode() {}
    int getKey() {
        return key;
    }
    void setKey(int pKey) {
        key = pKey;
    }
    Nodo *getElement() {
        return element;
    }
    void setElement(Nodo *pElement) {
        element = pElement;
    }
};

#endif // HEAPNODE_H
