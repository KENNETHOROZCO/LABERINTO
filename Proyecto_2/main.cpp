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
        segundos-=(segundos*0.3);
        VInterfaz.personaje.setAyuda(false);
    }
}
void iniciarCuenta(){
    while(segundos!=-1 && VInterfaz.fin){
        settextstyle(2,0,12);
        if(!VInterfaz.pausa){
            VInterfaz.tiempoA(segundos);
            cambiarCronometro();
        }

    }
}
void setTiempo(){
    segundos=((nivel/4)+1)*10;
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
    Grafo *grafo = new Grafo();
    grafo->arbol(filas+(nivel/2),columnas+nivel);
    grafo->mostrar_grafo();
    VInterfaz.pintarGrafo(grafo,nivel);
    VInterfaz.personaje.DPersonaje1(0);
    VInterfaz.personaje.DPersonaje1(1);
    do{
       VInterfaz.mover(grafo);
    }while(VInterfaz.fin);
}

void posInicio(){
    int x=320-(nivel*30);
    int y=250-(nivel*30);
    if(x<=60){
        x=60;
    }
    if(y<=60){
        y=60;
    }
    VInterfaz.posInicial(x,y);
}
void crearVentana(void * aArg){
    VInterfaz.crearVentana();
    posInicio();
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
