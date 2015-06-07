#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "HeapNode.h"
#include <stdexcept>
#include<Nodo.h>

using namespace std;


class MinHeap{
private:
    int maxSize;
    int size;
    HeapNode* elements;

    int leftChild(int pIndex) {
        return 2 * pIndex + 1;
    }
    int rightChild(int pIndex) {
        return 2 * pIndex + 2;
    }
    int parent(int pIndex) {
        if (pIndex == 0) {
            return -1;
        }
        return (pIndex - 1) / 2;
    }
    int isLeaf(int pIndex) throw (runtime_error) {
        if ((pIndex > size) || (pIndex < 0)) {
            throw runtime_error("Position out of range.");
        }
        return leftChild(pIndex) >= size;
    }
    void swap(int pIndex1, int pIndex2) {
        int tempKey;
        Nodo *tempElement;

        tempKey = elements[pIndex1].getKey();
        tempElement = elements[pIndex1].getElement();
        elements[pIndex1].setKey(elements[pIndex2].getKey());
        elements[pIndex1].setElement(elements[pIndex2].getElement());
        elements[pIndex2].setKey(tempKey);
        elements[pIndex2].setElement(tempElement);
    }
    void siftUp(int pos) {
       while (pos>0 && elements[parent(pos)].getKey()<elements[pos].getKey()){
                swap(pos,parent(pos));
                pos = parent(pos);
            }
    }
    void siftDown(int pos) {
            while(!isLeaf(pos) && (greaterChild(pos)<size) && (elements[pos].getKey()<elements[greaterChild(pos)].getKey())){
            int gChild = greaterChild(pos);
            swap(pos,gChild);
            pos = gChild;
        }
    }
    int greaterChild(int pos) {
        if (rightChild(pos)>=size){  //no hay hijo derefffff
                return leftChild(pos);
            }
            if (elements[leftChild(pos)].getKey()>elements[rightChild(pos)].getKey()){ //si el hijo mayor es el izquierdo
                return leftChild(pos);
            }
            else{
                return rightChild(pos);
            }
    }

public:
    MinHeap(int pMaxSize = 1024) {
        maxSize = pMaxSize;
        size = 0;
        elements = new HeapNode[maxSize];
    }
    ~MinHeap() {
        delete [] elements;
    }
    void insert(Nodo *pElement) throw (runtime_error) {
        if( size == maxSize){
            throw runtime_error("Heap is full");
         }
         elements[size].setKey(pElement->numero); //inserta la llave en el nodo
         elements[size].setElement(pElement); //inserta el elemento en el nodo
         siftUp(size); //esta funcion recibe la posicion en el arreglo
         size++;
    }
    Nodo *removeFirst() throw (runtime_error) {
        if(size == 0){
            throw runtime_error("Heap us empty");
          }
          return removeAt(0);
    }
    Nodo *removeAt(int pos) throw (runtime_error) {
       if(size == 0){
           throw runtime_error("Heap is empty");
         }
         if(pos < 0 || pos >= size ){
            throw runtime_error("Out of range");
         }
         Nodo *result = elements[pos].getElement();
         size--; // borra el elemento
         swap(pos,size);//intercambia posicion  y el ultimo elemento
         siftDown(pos);
         return result;
    }
    int getSize() {
        return size;
    }
};

#endif // MAXHEAP_H
