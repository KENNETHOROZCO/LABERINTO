#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>
#include <string.h>
#include<winbgim.h>
#include <windows.h>
#include<Personaje.h>
#include<Interfaz.h>
#include<tinythread.h>
#include <sstream>
#include <Grafo.h>

/*
grafo->listaNodos->goToStart();
Nodo* nodo=grafo->listaNodos->getElement();
nodo->listaArista.goToStart();
if(nodo->listaArista.getElement()){
}
*/
using namespace std;
using namespace tthread;
Interfaz VInterfaz;
Grafo *grafo = new Grafo();
int segundos;
int nivel=1;
int ayuda=0;
thread t;
thread t2;
void cronometro(void * aArg);
void crearVentana(void * aArg);

void cambiarCronometro(){
    if(VInterfaz.personaje.getAyuda()){
        segundos-=10;
    }
}
void iniciarCuenta(){
    while(segundos!=-1 && VInterfaz.fin){
        settextstyle(2,0,12);
        VInterfaz.tiempoA(segundos);
        cambiarCronometro();
    }
}

void setTiempo(){
    segundos=((nivel/3)+3)*10;
    segundos+=VInterfaz.personaje.getExtraTime()+1;
    segundos-=ayuda;
}
void cronometro(void * aArg){
    setTiempo();
    iniciarCuenta();
    cout<<"entro"<<endl;
    exit(0);
    return;
}


void crearVentana(void * aArg){
    VInterfaz.crearVentana();
    grafo->listaNodos->goToPos(10);
    VInterfaz.pared(grafo->listaNodos->getElement(),nivel);
    //VInterfaz.pintarGrafo(grafo,nivel);
    /*VInterfaz.pintarCuadro(350,420);
    VInterfaz.pintarCuadro(370,420);
    VInterfaz.pintarCuadro(390,420);
    cout<<"Creando ventanas"<<endl;
    VInterfaz.dibujarGifs(true,200,200);
    VInterfaz.dibujarGifs(true,100,100);
    VInterfaz.dibujarGifs(true,250,250);
    VInterfaz.dibujarGifs(true,600,600);
    VInterfaz.dibujarGifs(true,400,400);*/
    VInterfaz.personaje.DPersonaje(0);
    VInterfaz.personaje.DPersonaje(1);
    do{
       VInterfaz.mover();
    }while(VInterfaz.fin);
}



void inicioHilos(){
    thread t(cronometro, 0);
    thread t2(crearVentana,0);
    t.join();
    t2.join();
}
int main() {
    grafo->arbol(4,5);
    inicioHilos();

  //  t.~thread();
 //   t2.~thread();
    return 0;
}
