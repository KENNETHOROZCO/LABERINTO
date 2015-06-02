#ifndef DNODE_H
#define DNODE_H
#include<Nodo.h>
template<typename E>

class DNode
{
    public:
        E *element;
        DNode<E>*next;
        DNode<E>*previous;
        DNode(E *pElement, DNode<E>*pNext=NULL, DNode<E>*pPrevious=NULL) {
            element=pElement;
            next=pNext;
            previous=pPrevious;
        }
        DNode(DNode<E>*pNext=NULL, DNode<E>*pPrevious=NULL){
            next=pNext;
            previous=pPrevious;
        }
};

#endif // DNODE_H
