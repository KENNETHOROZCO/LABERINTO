#ifndef ARISTA_H
#define ARISTA_H
#include<Nodo.h>
#include<Nodo.h>

using namespace std;
template<typename E>
class Arista
{
private:

    Arista *siguiente;  //Siguiente arista en la lista virtual
    Nodo nodoDestino; //Puntero al nodo de llegada
    int size; //Tamaño de la lista de adyacencia

public:
    Arista(){
        nodoDestino=NULL;
        siguiente=NULL;
    }
    Arista(Nodo<E> *pNodo=NULL, Arista pArista=NULL){
        nodoDestino=pNodo;
        siguiente=pArista;

    }
    *Nodo<E> getNodoDestino(){
        return nodoDestino();
    }
    *Arista getSiguiente(){
        return siguiente;
    }
    void setNodoDestino(Nodo<E> pNodo){
        nodoDestino=pNodo;
    }
    void setSiguiente(Arista *pArista){
        siguiente=pArista;
    }

};

#endif // ARISTA_H
