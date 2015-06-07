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
int nivel=4;
int ayuda=0;
int filas=4;
int columnas=5;
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
    segundos=((nivel/3)+3)*40;
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


void iniciarJuego(){
    grafo->arbol(filas+nivel,columnas+nivel);
    grafo->mostrar_grafo();
    VInterfaz.pintarGrafo(grafo,nivel);
    VInterfaz.personaje.DPersonaje1(0);
    VInterfaz.personaje.DPersonaje1(1);
    do{
       VInterfaz.mover(grafo);
    }while(VInterfaz.fin);
}
void crearVentana(void * aArg){
    int x=320-(nivel*30);
    int y=250-(nivel*30);
    if(x<=60){
        x=60;
    }
    if(y<=60){
        y=60;
    }
    VInterfaz.crearVentana(x,y);
    iniciarJuego();
}



void inicioHilos(){
    thread t(cronometro, 0);
    thread t2(crearVentana,0);
    t.join();
    t2.join();
}
int main() {
    //grafo->arbol(filas,columnas);
    inicioHilos();
    return 0;
}
