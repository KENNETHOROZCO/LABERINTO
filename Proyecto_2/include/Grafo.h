#ifndef GRAFO_H
#define GRAFO_H
#include<iostream>
#include<conio.h>
#include<Nodo.h>
#include<DLinkedList.h>
#include<stdlib.h>
#include<time.h>
#include<MinHeap.h>

using namespace std;
struct nodo{
            int numero;//nombre del vertice o nodo
            struct Nodo *siguiente;
            struct arista *listaAdyacencia;//puntero hacia la primera arista del nodo
            };

class Grafo
{

public:
    MinHeap *Q;
    DLinkedList<Nodo> *listaNodos;
    Nodo *principal;
    int dimensionX;
    int dimensionY;
    int gifsPantalla;
Grafo(){
    Q=new MinHeap();
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
    return temp;
}

void arbol(int x,int y){
    listaNodos->clear();
    principal=NULL;
    dimensionX=x;
    dimensionY=y;
    generarLaberinto(dimensionX,dimensionY);
    srand(time(NULL));
    DLinkedList<Nodo> *pila=new DLinkedList<Nodo>();
    DLinkedList<Nodo> *nuevoArbol=new DLinkedList<Nodo>();
    listaNodos->goToStart();
    nuevoArbol=listaNodos;
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

    if(listaNodos->getSize()!=x*y){
            listaNodos->clear();
            arbol(x,y);
            return;

    }
    agregarAristasExtras(x,y);
    reordenar(x,y);
    listaNodos->goToPos(listaNodos->getSize()-1);
    listaNodos->getElement()->setSalida(true);
}

bool existe(int indice, DLinkedList<arista> *lista){
    for(int i=0;i<lista->getSize();i++){
        if(indice==lista->getElement()->nodoDestino->numero)
            return true;
        }
        return false;
    }

void anadirVacio(int indice, int posicion){
    for(int i=0;i<listaNodos->getSize();i++){
        listaNodos->goToPos(i);
        if(listaNodos->getElement()->numero==indice){
            Nodo *temp=listaNodos->getElement();
            arista *nuevaArista=new struct arista;
            nuevaArista->nodoDestino=new Nodo(-100);
            temp->listaAristas->goToPos(posicion);
            temp->listaAristas->insert(nuevaArista);
        }
    }
}

void reordenar(int x,int y){
    listaNodos->goToStart();
    for(int i =0; i<listaNodos->getSize()+1; i++){
        Nodo *temp=listaNodos->getElement();
        DLinkedList<arista> *lista=temp->listaAristas;
        for(int e=0; 4>lista->getSize(); e++){
            anadirVacio(temp->numero,0);
        }
        listaNodos->goToPos(i);
    }
    listaNodos->goToStart();
    for(int i=0; i<listaNodos->getSize()+1; i++){
        Nodo *temp=listaNodos->getElement();
        DLinkedList<arista> *lista=temp->listaAristas;
        lista->goToStart();
        for(int e=0; e<lista->getSize(); e++){
            lista->goToPos(e);
            if((lista->getElement()->nodoDestino->numero==temp->numero-1)){
                arista *aristemp=lista->remove();
                lista->goToPos(0);
                lista->insert(aristemp);
            }
        }
        for(int e=0; e<lista->getSize(); e++){
            lista->goToPos(e);
            if((lista->getElement()->nodoDestino->numero==temp->numero+1)){
                arista *aristemp=lista->remove();
                lista->goToPos(1);
                lista->insert(aristemp);
            }

        }for(int e=0; e<lista->getSize(); e++){
            lista->goToPos(e);
            if((lista->getElement()->nodoDestino->numero==temp->numero-y)){
                arista *aristemp=lista->remove();
                lista->goToPos(2);
                lista->insert(aristemp);
            }
        }
        for(int e=0; e<lista->getSize(); e++){
            lista->goToPos(e);
            if((lista->getElement()->nodoDestino->numero==temp->numero+y)){
                arista *aristemp=lista->remove();
                lista->goToPos(3);
                lista->insert(aristemp);
            }

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
    srand(time(NULL));
    gifsPantalla=(y*x/5);
    for(int i =0;i<gifsPantalla;i++){
        int f=rand()%(x*y);
        listaNodos->goToPos(f);
        if(!listaNodos->getElement()->getFruta() ){
           listaNodos->getElement()->setFruta(true);
        }
        else{i--;}
    }
}
void agregarAristasExtras(int x, int y){
    srand(time(NULL));
    int res=x*y;
    bool bandera;
    for(int i =0;i<(res*0.10);i++){
        bandera=false;
        int num1 = (rand()%res)/(((res*0.05)/2)-i);
        while(!bandera){
            if(num1<0){
                ++num1;
                bandera=false;
                continue;
            }
            else if(num1>res){
                --num1;
                bandera=false;
                continue;
            }
            else if(num1-y>0&&!existe(num1,num1-1)&&num1%y!=1){
            addArista(num1,num1-1,true);
            bandera=true;
            break;
            }else{
                ++num1;
            }
        }
    }

}bool existe(int indice,int nodoActual){
    listaNodos->goToPos(nodoActual);

    for(int i =0;i<listaNodos->getElement()->listaAristas->getSize();i++){
        listaNodos->getElement()->listaAristas->goToPos(i);
        if(indice==listaNodos->getElement()->listaAristas->getElement()->nodoDestino->numero){
            return true;
        }
    }
    return false;
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
    Nodo *aux2;
    for(int i =0;i<listaNodos->getSize();i++){
        listaNodos->goToPos(i);
        if(listaNodos->getElement()->numero==fin){
            aux2=listaNodos->getElement();
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
            aux2->listaAristas->remove();
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


//Devuelve la ruta de dijkstra
DLinkedList<Nodo> *getPath( int destino ){
    DLinkedList<Nodo> *listaTemporal=new DLinkedList<Nodo>();
    listaNodos->goToPos(destino);
    Nodo *temp=listaNodos->getElement();
    while(temp!=NULL){
            cout<<temp->numero<<endl;
        listaTemporal->append(temp);
        temp=temp->previo;

    }

    return listaTemporal;
}

//Prueba si se cumple que el peso actual del menor  mas el peso es mejor que el del adyacente
void relajacion( Nodo *actual , Nodo *adyacente , int peso ){
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if( actual->distancia + peso < adyacente->distancia ){
        adyacente->distancia = actual->distancia + peso;
        adyacente->previo = actual;
        Q->insert(adyacente);
    }
}


DLinkedList<Nodo> *dijkstra( int destino){
    normalizarNodos();
    cout<<"Salimos de: "<<destino<<endl;
    listaNodos->goToPos(destino);
    listaNodos->getElement()->distancia=0;
    Q->insert( listaNodos->getElement() ); //Insertamos el vértice inicial en la Cola de Prioridad

    int peso;
    Nodo *act;
    Nodo *ad;
    while( Q->getSize()!=0 ){//Mientras cola no este vacia

        act = Q->removeFirst() ;

        if( act->visitado ){
          continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola

        }
        act->visitado =true; //se marca el actual como visitado

        for( int i = 0 ; i < act->listaAristas->getSize() ; i++ ){ //reviso sus adyacentes del vertice actual


            act->listaAristas->goToPos(i);

            ad = act->listaAristas->getElement()->nodoDestino;   //id del vertice adyacente
            peso = 1;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if( !ad->visitado ){        //si el vertice adyacente no fue visitado
                relajacion( act , ad , peso ); //realizamos el paso de relajacion

            }
        }
    }
    cout<<"tamano lista"<<listaNodos->getSize()<<endl;
    return getPath(listaNodos->getSize()-1); //Numero al cual qiero llegat
}
void normalizarNodos(){
    for(int i =0;i<listaNodos->getSize();i++){
        listaNodos->goToPos(i);
        listaNodos->getElement()->visitado=false;
        listaNodos->getElement()->distancia=9999999;
        listaNodos->getElement()->previo=NULL;


    }
    while(Q->getSize()!=0){
        Q->removeFirst();
    }

}

};

#endif // GRAFO_H
