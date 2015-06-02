#ifndef GRAFO_H
#define GRAFO_H
#include<iostream>
#include<conio.h>
#include<Nodo.h>
#include<DLinkedList.h>
#include<stdlib.h>
#include<time.h>

using namespace std;


struct nodo{
            int numero;//nombre del vertice o nodo
            struct Nodo *siguiente;
            struct arista *listaAdyacencia;//puntero hacia la primera arista del nodo
            };

class Grafo
{
    DLinkedList<Nodo> *listaNodos;
    Nodo *principal;
public:
Grafo(){
    principal= NULL;
    listaNodos=new DLinkedList<Nodo>();
}
void insertar_nodo(int indice){
    Nodo *nuevo=new Nodo();
    Nodo *t=new Nodo();
    nuevo->numero=indice;
    nuevo->siguiente = NULL;
    nuevo->listaAdyacencia=NULL;
    listaNodos->append(nuevo);
    if(principal==NULL){
        principal = nuevo;
    }
    else{
        t = principal;
        while(t->siguiente!=NULL){
            t = t->siguiente;
        }
        t->siguiente = nuevo;
    }
 }

 void vaciar_aristas(Nodo *aux){
    arista *q,*r;
    q=aux->listaAdyacencia;
    while(q->siguiente!=NULL){
        r=q;
        q=q->siguiente;
        delete(r);
    }
}

void agrega_arista(Nodo *aux, Nodo *aux2, arista *nuevo,bool bandera){
    arista *q;
    if(bandera){
        if(aux->listaAristas->getSize()==-1){
            nuevo->nodoDestino=aux2;
            aux->listaAristas->append(nuevo);
        }
        else{
            nuevo->nodoDestino=aux2;
            aux->listaAristas->append(nuevo);
        }
        return;
    }
    if(aux->listaAristas->getSize()==-1){
        nuevo->nodoDestino=new Nodo();
        aux->listaAristas->append(nuevo);
    }
    else{
        nuevo->nodoDestino=new Nodo();
        aux->listaAristas->append(nuevo);
    }
}

void insertar_arista(int inicio,int fin,bool bandera){
    arista *nuevo=new struct arista;
    Nodo *aux;
    Nodo *aux2;
    listaNodos->goToStart();
    if(listaNodos->getSize()==0){
        return;
    }
    nuevo->siguiente=NULL;
    while(aux2!=NULL){
        aux2=listaNodos->getElement();
        if(aux2->numero==fin){
            break;
        }
        listaNodos->next();
    }
    listaNodos->goToStart();
    aux=listaNodos->getElement();
    while(aux!=NULL){
        if(aux->numero==inicio){
            agrega_arista(aux,aux2, nuevo,bandera);
            return;
        }
        listaNodos->next();
        aux = aux->siguiente;
    }
}

Nodo buscarNodo(int indice){
    Nodo *temp=principal;
    while(temp->siguiente!=NULL){
        temp=temp->siguiente;
    }
    return *temp;
}

void eliminar_nodo(int indice){
    for(int i=0;i<listaNodos->getSize();i++){
        eliminar_arista(i,indice-1);
    }
    if(listaNodos->getSize()==-1){
        return;
    }
    listaNodos->goToPos(indice-1);
    listaNodos->remove();
}

void generarLaberinto(int x, int y){
    for(int i=1;i<x*y+2;i++){
        insertar_nodo(i);
        if(i-1>0&&i%y!=1){
            addArista(i,i-1,true);
        }
        if(i-y>0){
            addArista(i,i-y,true);
        }
    }
    eliminar_nodo(x*y+1);
}

void generar(DLinkedList<int> *lista){
    listaNodos->clear();
    for(int i=0;i<lista->getSize()-1;i++){
        lista->goToPos(i);
        int indice1=*lista->getElement();
        insertar_nodo(indice1);
        lista->goToPos(i+1);
        int indice2=*lista->getElement();
        insertar_nodo(indice2);
        addArista(indice1,indice2,true);
    }
    mostrar_grafo();
}

DLinkedList<Nodo> *getFinal(DLinkedList<Nodo> *lista){
    DLinkedList<Nodo> *temp=new DLinkedList<Nodo>();
    for(int i =0;i<listaNodos->getSize();i++){
        listaNodos->goToPos(i);
        temp->append(listaNodos->getElement());
    }
    for(int i=0;i<temp->getSize();i++){
        temp->goToPos(i);
        insertar_nodo(lista->getElement()->numero);
    }
    for(int i =0;i<listaNodos->getSize();i++){
        listaNodos->goToPos(i);
        int indice1=listaNodos->getElement()->numero;
        listaNodos->goToPos(3);
        int indice2=listaNodos->getElement()->numero;
        addArista(indice1,indice2,true);
    }
    mostrar_grafo();
    return temp;
}

void arbol(int x,int y){
    generarLaberinto(x,y);
    srand(time(NULL));
    DLinkedList<Nodo> *pila=new DLinkedList<Nodo>();
    DLinkedList<Nodo> *nuevoArbol=new DLinkedList<Nodo>();
    listaNodos->goToStart();
    nuevoArbol=listaNodos;
    cout<<"El tamaño de la lista es de: "<<nuevoArbol->getSize()<<endl;
    Nodo *temp=nuevoArbol->getElement();
    temp->visitado=true;
    listaNodos->clear();
    insertar_nodo(temp->numero);
    pila->append(temp);
    int numero;
    bool bandera=false;
    for(int i=0;pila->getSize()!=0;i++){
        numero=temp->numero;
        temp->listaAristas->goToStart();
        for(int e=0;e<temp->listaAristas->getSize()+2;e++){
            int num = rand()%temp->listaAristas->getSize();
            temp->listaAristas->goToPos(num);
            if(!temp->listaAristas->getElement()->nodoDestino->visitado){
                temp->listaAristas->getElement()->nodoDestino->visitado=true;
                pila->append(temp);
                temp=temp->listaAristas->getElement()->nodoDestino;
                insertar_nodo(temp->numero);
                insertar_arista(numero,temp->numero,true);
                insertar_arista(temp->numero,numero,true);
                bandera=false;
                break;
            }
            else{
                bandera=true;
            }
        }
        if(bandera){
            pila->goToPos(pila->getSize()-1);
            temp=pila->remove();
            bandera=false;
        }
    }
    cout<<pila->getSize()<<endl;
    cout<<"El tamaño de la lista es de: "<<listaNodos->getSize()<<endl;
    agregarAristasExtras(x,y);
    reordenar(x,y);
    mostrar_grafo();
    cout<<"Tamaño del labrinto: "<<listaNodos->getSize()<<endl;
}

bool existe(int indice, DLinkedList<arista> *lista){
    for(int i=0;i<lista->getSize();i++){
        if(indice==lista->getElement()->nodoDestino->numero)
            return true;
        }
        return false;
    }

void reordenar(int x,int y){
    listaNodos->goToStart();
    for(int i =0; i<listaNodos->getSize()+1; i++){
        Nodo *temp=listaNodos->getElement();
        DLinkedList<arista> *lista=temp->listaAristas;
        for(int e=0; 4>lista->getSize(); e++){
            anadirVacio(temp->numero);
        }
        listaNodos->goToPos(i);
    }
    listaNodos->goToStart();
    for(int i=0; i<listaNodos->getSize(); i++){
        bool bandera=false;
        Nodo *temp=listaNodos->getElement();
        DLinkedList<arista> *lista=temp->listaAristas;
        lista->goToStart();
        for(int e=0; e<lista->getSize(); e++){
            lista->goToPos(e);
            if(lista->getElement()->nodoDestino->numero==temp->numero-1){
                arista *aristemp=lista->remove();
                lista->goToPos(0);
                lista->insert(aristemp);
            }
            lista->goToPos(e);
            if(lista->getElement()->nodoDestino->numero==temp->numero+1){
                arista *aristemp=lista->remove();
                lista->goToPos(1);
                lista->insert(aristemp);
            }
            lista->goToPos(e);
            if(lista->getElement()->nodoDestino->numero==temp->numero-y){
                arista *aristemp=lista->remove();
                lista->goToPos(2);
                lista->insert(aristemp);
            }
            lista->goToPos(e);
            if(lista->getElement()->nodoDestino->numero==temp->numero+y){
                arista *aristemp=lista->remove();
                lista->goToPos(3);
                lista->insert(aristemp);
            }
            lista->goToPos(e);
        }
        listaNodos->goToPos(i);
    }
    Nodo *temp;
    for(int i =0; i<listaNodos->getSize(); i++){
        for(int e =0; i<listaNodos->getSize(); e++){
            listaNodos->goToPos(e);
            if(listaNodos->getElement()->numero==i+1){
                temp=listaNodos->remove();
                listaNodos->goToPos(i);
                listaNodos->insert(temp);
                break;
            }
        }
    }
}
void agregarAristasExtras(int x, int y){
    srand(time(NULL));
    int res=x*y;
    for(int i =0;i<(res*0.05);i++){
        int num1 = rand()%x*y;
        int num2 = rand()%x*y;
        if(num1!=0||num2!=0){
            if(num2-1>0&&num2%y!=1){
                if(existe(num2)&&existe(num2-1)){
                    addArista(num2,num2-1,true);
                }
                else{
                    i--;
                }
            }
        }
    }
    for(int i =0;i<(res*0.05)/2;i++){
        int num1 = rand()%x*y;
        int num2 = rand()%x*y;
        if(num1-y>0){
            if(existe(num1)&&existe(num1-y)){
               addArista(num1,num1-y,true);
            }
            else{
                i--;
            }
        }
    }
}
bool existe(int indice){
    for(int i =0;i<listaNodos->getSize();i++){
        if(indice==listaNodos->getElement()->numero==indice){
            return true;
        }
    }
    return false;
}

void montarCuadricula(int x, int y){
    for(int i=(x-1)*y+1;i<x*y+1;i++){
        anadirVacio(i);
    }
}

void acomodarLista(){
    listaNodos->goToStart();
    for(int i=0;i<listaNodos->getSize();i++){
        listaNodos->goToPos(i);
        Nodo *temp=listaNodos->getElement();
        temp->listaAristas->goToPos(1);
        arista *aris=temp->listaAristas->remove();
        temp->listaAristas->next();
        temp->listaAristas->insert(aris);
    }
}

void setPrincipal(Nodo *pPrincipal){
    principal=pPrincipal;
}

/*                      ELIMINAR ARISTA
    funcion utilizada para eliminar una arista
---------------------------------------------------------------------*/
void eliminar_arista(int inicio, int fin){
    Nodo *aux;
    Nodo *aux2;
    for(int i =0;i<listaNodos->getSize();i++){
        listaNodos->goToPos(i);
        if(listaNodos->getElement()->numero==fin){
            aux=listaNodos->getElement();
        }
    }
    for(int i =0;i<listaNodos->getSize();i++){
        listaNodos->goToPos(i);
        if(listaNodos->getElement()->numero==inicio+1){
            aux2=listaNodos->getElement();
        }
    }
    for(int i=0;aux2->listaAristas->getSize()>i;i++){
        aux2->listaAristas->goToPos(i);
        if(aux2->listaAristas->getElement()->nodoDestino->numero==fin+1){
            arista *temp=aux2->listaAristas->remove();
        }
    }
}

void eliminarArista(int nodo1, int nodo2){
    eliminarArista(nodo1,nodo2);
    eliminarArista(nodo2,nodo1);
}
/*                      MOSTRAR GRAFO
    funcion que imprime un grafo en su forma enlazada
---------------------------------------------------------------------*/
void mostrar_grafo(){
    listaNodos->goToStart();
    for(int i=0;i<listaNodos->getSize();i++){
        cout<<"   "<<listaNodos->getElement()->numero<<"|";
        Nodo *temp=listaNodos->getElement();
        if(temp->listaAristas->getSize()!=0){
            temp->listaAristas->goToStart();
            for(int i=0;i<temp->listaAristas->getSize();i++){
                cout<<" "<<temp->listaAristas->getElement()->nodoDestino->numero;
                temp->listaAristas->next();
             }
        }
        listaNodos->next();
        cout<<endl;
    }
}

void addArista(int indiceArista1, int indiceArista2,bool ambas){
    if(ambas){
        insertar_arista(indiceArista2,indiceArista1,true);
        insertar_arista(indiceArista1,indiceArista2,true);
    }
    else{
        insertar_arista(indiceArista2,indiceArista1,false);
        insertar_arista(indiceArista1,indiceArista2,false);
    }
}

void anadirVacio(int indice){
    for(int i=0;i<listaNodos->getSize();i++){
        listaNodos->goToPos(i);
        if(listaNodos->getElement()->numero==indice){
            Nodo *temp=listaNodos->getElement();
            arista *nuevaArista=new struct arista;
            nuevaArista->nodoDestino=new Nodo(0);
            temp->listaAristas->append(nuevaArista);
        }
    }
}

void addVacio(int nodo1,int nodo2){
    anadirVacio(nodo1);
    anadirVacio(nodo2);
}
};

#endif // GRAFO_H
