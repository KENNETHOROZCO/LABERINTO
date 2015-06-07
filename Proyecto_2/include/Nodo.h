#ifndef NODE_H
#define NODE_H
#include<DLinkedList.h>


using namespace std;


struct arista{
    struct Nodo *nodoDestino;//puntero al nodo de llegada
    struct arista *siguiente;
};

class Nodo{

public:
    Nodo *previo;
    int distancia;
    bool entrada;
    bool fruta;
    bool salida;
    bool visitado;
    DLinkedList<arista> *listaAristas;
    int numero; //Nombre del nodo
    Nodo *siguiente;
    int size; //Tamaño de la lista de nodos
    arista *listaAdyacencia; //Puntero al primer elemento de las aristas
    Nodo(int pnumero=0){
        listaAristas=new DLinkedList<arista>();
        numero=pnumero;
        siguiente=NULL;
        size=0;
        visitado=false;
        fruta=false;
        salida=false;
        entrada=false;
        previo=NULL;
        distancia=9999999;
    }
    void setEstrada(bool p){
        entrada=p;
    }
    void setFruta(bool p){
        fruta=p;
    }
    void setSalida(bool p){
        salida=p;
    }
    bool getFruta(){
        return fruta;
    }
    int getNumero(){
        return numero;
    }

    Nodo getSiguiente(){
        return *siguiente;
    }
    bool getSalida(){
        return salida;
    }
    void setSiguiente(Nodo *pSiguiente){
        siguiente=pSiguiente;
    }
    void setNombre(int pNumero){
        numero=pNumero;
    }
};

#endif // NODE_H
