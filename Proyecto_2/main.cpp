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
Grafo *grafo = new Grafo();
int segundos;
int nivel=0;
int nivelExtra;
int ayuda=0;
int filas=4;
int tamannio;// TAMAÑO DEL LABERINTO
thread t; // HILO DE LA VENTANA
thread t2; // HILO DEL CRONOMETRO

//POSICIONA AL PERSONAJE EN LA POSICION DE INICIO DEL JUEGO SEGUN EL NIVEL
void posInicio(){
    int x=(VInterfaz.getMaxX()/2-100)-(nivel*15);
    int y=(VInterfaz.getMaxY()/2-100)-(nivel*15);
    if(x<=60){
        x=30;
    }
    if(y<=60){
        y=60;
    }
    VInterfaz.posInicial(x,y);
}

//MODIFICA EL TIEMPO DEL CRONOMETRO
void determinarTiempo(){
    segundos=(nivel/4+1)*7;
    segundos+=VInterfaz.personaje.getExtraTime()+1;
    segundos-=nivelExtra*5;
    VInterfaz.personaje.setExtraTime(0);
}

// IMPRIME EN LA VENTANA LAS ESTADISTICAS DEL JUGADOR
void estadisticas(){
    settextstyle(2,1,12);
    string estadisticas;
    stringstream p,r,g;
    p<<VInterfaz.personaje.getPuntaje();
    nivel+=nivelExtra;
    r<<nivel+1;
    g<<VInterfaz.personaje.getGifs();
    outtextxy(VInterfaz.getMaxX()/2-150,VInterfaz.getMaxY()/2-300,"¡GAME OVER!");
    estadisticas="score: "+p.str();
    const char * estadistica = ((string)estadisticas).c_str();
    outtextxy(VInterfaz.getMaxX()/2-400,VInterfaz.getMaxY()/2+20,estadistica);
    estadisticas="record: "+r.str();
    estadistica=((string)estadisticas).c_str();
    outtextxy(VInterfaz.getMaxX()/2-80,VInterfaz.getMaxY()/2+20,estadistica);
    estadisticas="apples: "+g.str();
    estadistica=((string)estadisticas).c_str();
    outtextxy(VInterfaz.getMaxX()/2+200,VInterfaz.getMaxY()/2+20,estadistica);
    cout<<"nivel"<<r.str()<<" puntaje "<<p.str()<<"gifs: "<<g.str()<<endl;
}

// REVISA SI EL JUEGO SE TERMINO O NO
void finDelJuego(){
    if(segundos<0){
        setbkcolor(COLOR(102,0,0));
        cleardevice();
        setcolor(COLOR(255,255,0));
        int x=VInterfaz.getMaxX()/2-135;
        int y=VInterfaz.getMaxY()/2-200;
        int R=0;
        int G=240;
        int B=0;
        estadisticas();
        for(int i=0;i<6;i++){
            for(int j=0;j<9;j++){
                VInterfaz.personaje.setPos(x,y);
                VInterfaz.personaje.DPersonaje1(0,4);
                x+=35;
            }
            VInterfaz.personaje.setColoresT(R,G,B);
            G-=40;
            x=VInterfaz.getMaxX()/2-135;
            y+=35;
        }
        settextstyle(11,0,1);
        setcolor(COLOR(32,32,32));
        outtextxy(10,VInterfaz.getMaxY()-50,"P.K.A.");
        getch();
        VInterfaz.fin=false;
    }
    else if(VInterfaz.personaje.getPosicion()==tamannio-1 && VInterfaz.personaje.getGifsP()==grafo->gifsPantalla){
        VInterfaz.pausa=true;
        cleardevice();
        VInterfaz.personaje.setPuntaje(30);
        VInterfaz.personaje.setExtraTime(segundos);
        VInterfaz.personaje.setGifs();
        if(nivel<=15){nivel++;}
        else{nivelExtra++;}
        posInicio();
        determinarTiempo();
        iniciarJuego();
    }
}

// RESTA EL TIEMPO DEL JUGADOR
void cambiarCronometro(){
    if(VInterfaz.personaje.getAyuda()){
        segundos-=(segundos*0.3);
        VInterfaz.personaje.setAyuda(false);
    }
}
// INICIA EL CRONOMETRO
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
    determinarTiempo();
    iniciarCuenta();
    exit(0);
    return;
}

//PONE A FUNCIONAR EL JUEGO
void iniciarJuego(){
    VInterfaz.pausa=false;
    int f=filas+(nivel/2);
    int columnas=f+(nivel%2);
    tamannio=f*columnas;
    grafo->arbol(f,columnas);
    grafo->mostrar_grafo();
    VInterfaz.pintarGrafo(grafo);
    VInterfaz.personaje.DPersonaje1(0,3);
    VInterfaz.personaje.DPersonaje1(1,3);
    stringstream p;
    p<<nivel+1;
    string n="nivel "+p.str();
    const char * ni = ((string)n).c_str();
    setcolor(COLOR(160,160,160));
    settextstyle(1,0,1);
    outtextxy(10,VInterfaz.getMaxY()-50,ni);
    do{
        VInterfaz.mover(grafo);
        finDelJuego();
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
