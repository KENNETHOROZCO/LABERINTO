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

using namespace std;
using namespace tthread;
void iniciarJuego();
Interfaz VInterfaz;
int segundos;
int nivel=0;//5,10,14
int ayuda=0;
int filas=4;
int tamannio;
thread t;
thread t2;


void posInicio(){
    int x=320-(nivel*15);
    int y=300-(nivel*15);
    if(x<=60){
        x=60;
    }
    if(y<=60){
        y=60;
    }
    VInterfaz.posInicial(x,y);
}
void setTiempo(){
    segundos=((nivel/4)+1)*5;
    //cout<<"segundos "<<segundos<<endl;
    segundos+=VInterfaz.personaje.getExtraTime()+1;
    segundos-=ayuda;
}
void finDelJuego(){
    if(segundos<=1){
        cleardevice();
        setcolor(COLOR(255,255,0));
        settextstyle(2,1,12);
        outtextxy(VInterfaz.getMaxX()/2-100,VInterfaz.getMaxY()/2-100,"Perdiste!!!");
        cout<<"Tu puntaje: "<<VInterfaz.personaje.getPuntaje()<<endl;
        cout<<"Record: nivel "<<nivel+1<<endl;
        cout<<"Gifs: "<<VInterfaz.personaje.getGifs()<<endl;
        getch();
        VInterfaz.fin=false;
    }
    else if(VInterfaz.personaje.getPosicion()==tamannio-1){
        VInterfaz.pausa=true;
        cleardevice();
        VInterfaz.personaje.setPuntaje(30);
        VInterfaz.personaje.setExtraTime(segundos);
        nivel++;
        posInicio();
        setTiempo();
        iniciarJuego();

    }
}
void cambiarCronometro(){
    if(VInterfaz.personaje.getAyuda()){
        segundos-=(segundos*0.3);
        VInterfaz.personaje.setAyuda(false);
    }
}
void iniciarCuenta(){
    while(VInterfaz.fin){
        settextstyle(2,0,12);
        if(!VInterfaz.pausa && segundos>-1){
            VInterfaz.tiempoA(segundos);
            cambiarCronometro();
        }
    }
}
void cronometro(void * aArg){
    setTiempo();
    iniciarCuenta();
    exit(0);
    return;
}

void iniciarJuego(){
    VInterfaz.pausa=false;
    Grafo *grafo = new Grafo();
    int f=filas+(nivel/2);
    int columnas=f+(nivel%2);
    tamannio=f*columnas;
    grafo->arbol(f,columnas);
    VInterfaz.pintarGrafo(grafo,nivel);
    VInterfaz.personaje.DPersonaje1(0);
    VInterfaz.personaje.DPersonaje1(1);
    do{
        finDelJuego();
        VInterfaz.mover(grafo);
    }while(VInterfaz.fin);
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
    inicioHilos();
    return 0;
}
