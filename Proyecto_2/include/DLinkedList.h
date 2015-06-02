#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include <stdexcept>
#include "DNode.h"

using namespace std;
template<typename E>

class DLinkedList{
    private:
        DNode<E>*head;
        DNode<E>*tail;

        int size;
        E *sumando;
        int size2;
    public:
         DNode<E>*current;
        DLinkedList() {
            current=head=new DNode<E>();
            tail=new DNode<E>(NULL,head,NULL);
            head->next=tail;
            size=0;
            size2=0;

            sumando=new E[100];
        }
        ~DLinkedList() {
            clear();
            delete head;
            delete tail;
        }
        void insert(E *pElement){
            current->next=current->next->previous=new DNode<E>(pElement,current->next,current);
            size++;
        }
        void append(E *pElement){
            if(head->next==tail){
                insert(pElement);
            }else
            tail->previous=tail->previous->next=new DNode<E>(pElement,tail,tail->previous);
            size++;
        }
        E *getHeadElement(){

            return &head->element;
        }
        E *remove()throw(runtime_error){
            if(current->next==tail){
                throw runtime_error("No hay elemento actual");
            }
            DNode<E>*temp = current->next;
            E *res = current->next->element;
            current->next = current->next->next;
            current->next->previous = current;

            delete temp;
            size--;
            return res;
        }
        void clear(){
            current=head->next;
            while(current!=tail){
                head->next=head->next->next;
                delete current;
                current=head->next;
            }
            head->next->previous=head;
            current=head;
            size=0;
        }
        E *getElement()throw(runtime_error){
            if(current->next==NULL){
                throw runtime_error("No hay elemento actual");
            }
           // cout << "Se ha obtenido el: " << current->next->element;
            return current->next->element;
        }
        void goToStart(){
            current=head;
        }
        void goToEnd(){
            current=tail->previous;
        }
        void goToPos(int pPos)throw(runtime_error){
            if((size<pPos)||(pPos<0)){
                throw runtime_error("No existe la posicion");
            }
            current=head;
            for(int i=0; i<pPos;i++){
                current=current->next;
            }
        }
        void next(){
            if(current->next!=tail){
                current= current->next;
            }
        }
        void previous(){
            if(current!=head){
                current=current->previous;
            }
        }
        int getPos(){
            int contador=0;
            DNode<E> *temp=current;
            for(current=head;current!=temp;current=current->next){

            contador++;
            }
            return contador;
        }
        void getPPos(bool vara){
            int contador=0;
            DNode<E> *temp=current;
            for(current=head;current!=temp;current=current->next){

            contador++;
            }
            cout <<contador;
        }
        int getSize(){
           // cout <<"El tamaño es de: "<< size-1;
            return size-1;
        }
        void printAll(){
                        cout << "\n";

            if(size==0){
                cout<<"Lista vacia";
            }
            else{
                DNode<E>*temp=current;
                int i=0;
                for(temp=head;temp->next!=tail;temp=temp->next){
                    cout << temp->next->element << " ";
                    if(i==getPos()-1){
                        cout << "|" ;
                    }
                    i++;
                }
            }
            cout<<endl;
        }
        void remo(){
        cout<< remove();
        }
        void intercambiar(int pos1, int pos2){
            DNode<E> *puntero1;
            printAll();
            DNode<E> *puntero2;
            current=head;
            goToPos(pos1);
            E temp1=getElement();
            remove();
            printAll();
            puntero1=current;
            current=head;

            for(int i=0;i<size;i++){
                if(pos1==i){
                    puntero1=current->next;
                }
                next();
            }
            current=head;
            for(int i=0;i<size;i++){
                if(pos2==i){
                    puntero2=current->next;
                }
                next();
            }
                DNode<E> *puntero1Siguiente=puntero1->next;
                DNode<E> *puntero1Previo=puntero1->previous;
                DNode<E> *puntero2Siguiente=puntero2->next;
                DNode<E> *puntero2Previo=puntero2->previous;
                puntero1Previo=puntero2;
                puntero1Siguiente=puntero2;
                puntero2Previo=puntero1;
                puntero2Siguiente=puntero1;
                puntero1=puntero2Siguiente;
                puntero1=puntero2Previo;
                puntero2=puntero1Siguiente;
                puntero2=puntero1Previo;
                current=head;
                goToPos(pos2-1);
            E temp2=getElement();
            remove();
            printAll();
            //Node<E> puntero1=current;
            insert(temp1);
            printAll();
            current=puntero1;
            insert(temp2);
            printAll();
        }
        void invertir(){
            for(int i =0;i<(size-1)/2;i++){
                goToPos(size-1-i-1);
                E temp1=getElement();
                goToPos(i);
                E temp2=getElement();
                goToPos(size-i-1-1);
                remove();
                insert(temp2);
                printAll();
                goToPos(i);
                remove();
                insert(temp1);
                printAll();

            }
        }
        void agregandoSuma(E elemento){
            sumando[size2++]=elemento;
        }
        void concatenar(){
            for(int i=0;i<size2;i++){
                append(sumando[i]);
            }
        }
};

#endif // DLINKEDLIST_H
