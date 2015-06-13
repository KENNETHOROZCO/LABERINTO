#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <direct.h>
#include <string.h>
#include<Personaje.h>
#include <sstream>
#include <Grafo.h>


using namespace std;

class Interfaz
{
private:
    int desplazar;// CANTIDAD DE ESPACIOS QUE SE VA A MOVER EL PERSONAJE
    int color;
    int maxx;
    int maxy;
    int posx,posy,posAntX,posAntY,RFondo,GFondo,BFondo;

public:
    bool pausa;
    bool fin;
    Personaje personaje;
    Interfaz() { //constructor
    pausa=false;
    fin = true;
    desplazar=60;
    maxx = 1000;
    maxy = 740;
    RFondo=0;//160 tods
    GFondo=0;
    BFondo=0;
    personaje.fondo(RFondo,GFondo,BFondo);
    }
    virtual ~Interfaz() {}
    // INICIALIZACION DE MODO GRAFICO
    void crearVentana(){
        initwindow(maxx, maxy);
        setbkcolor(COLOR(RFondo,GFondo,BFondo));// 255,255,102
        cleardevice();
    }
    void posInicial(int x, int y){
        posx = x;
        posy = y;
        posAntX=x;
        posAntY=y;
        personaje.setPos(posx,posy);
        personaje.setPosicion(0);
    }
    void setMaxX(int x){
        maxx=x;
    }
    void setMaxY(int y){
        maxy=y;
    }
    int getMaxX(){
        return maxx;
    }
    int getMaxY(){
        return maxy;
    }
    // DIBUJA O BORRA UNA FRUTA EN LA POSICIÓN X, Y RECIBIDAS
    void dibujarGifs(int x, int y){
            setlinestyle(6,1,3);
            setfillstyle(1,COLOR(255,0,0));
            setcolor(COLOR(255,0,0));
            fillellipse(x-1,y,6,8);
            fillellipse(x+6,y,6,8);
            setcolor(COLOR(0,255,0));
            setlinestyle(1,0,2);
            line(x+3,y-8,x+2,y-12);
            line(x+2,y-11,x-2,y-12);
            setcolor(COLOR(255,255,255));
            fillellipse(x+7,y-4,2,2);
    }

    //VERIFICA SI EL PERSONAJE TOMO O NO UNA FRUTA
    void recogerGifs(Nodo *&nodo){
        if(nodo->getFruta()==true){
            personaje.setGifsP(1);
            nodo->setFruta(false);
        }
    }

    //PINTA UN CUADRO DESDE LAS DIMENSIONES X,Y RECIBIDAS
    void pintarCuadro(int x, int y){
        setlinestyle(6,1,2);
        setcolor(COLOR(255,153,51));
        rectangle(x,y,x+21,y+15);
        rectangle(x+20,y,x+30,y+15);
        rectangle(x,y+15,x+10,y+30);
        rectangle(x+10,y+15,x+30,y+30);
        setfillstyle(SOLID_FILL,COLOR(102,51,0));//255,153,51
        bar(x+1,y+1,x+19,y+14);
        bar(x+21,y+1,x+29,y+14);
        bar(x+1,y+16,x+9,y+29);
        bar(x+11,y+16,x+29,y+29);

    }

    //RECIBE UN NODO Y PINTA UNA PARED EN LAS DIRECCIONES
    //DONDE NO HAY CAMINO PARA MOVERSE
    void pared(Nodo *nodo,int x,int y,int dimY ){
        pintarCuadro(x-42,y-45);
        pintarCuadro(x+18,y-45);
        pintarCuadro(x+18,y+15);
        pintarCuadro(x-42,y+15);
        //cuadro izquierdo
        nodo->listaAristas->goToPos(0);
        if(nodo->listaAristas->getElement()->nodoDestino->numero!=nodo->getNumero()-1){
            pintarCuadro(x-42,y-15);
        }
        //cuadro derecho
        nodo->listaAristas->goToPos(1);
        if(nodo->listaAristas->getElement()->nodoDestino->numero!=nodo->getNumero()+1){
            if(!nodo->getSalida()){
                pintarCuadro(x+18,y-15);
            }
        }
        //cuadro arriba
        nodo->listaAristas->goToPos(2);
        if(nodo->listaAristas->getElement()->nodoDestino->numero!=nodo->getNumero()-dimY){
            pintarCuadro(x-12,y-45);
        }
        //cuadro abajo
        nodo->listaAristas->goToPos(3);
        if(nodo->listaAristas->getElement()->nodoDestino->numero!=nodo->getNumero()+dimY){
            pintarCuadro(x-12,y+15);
        }
    }
    //RECIBE EL GRAFO Y LA REPRESENTA EN MODO GRAFICO
    void pintarGrafo(Grafo *&grafo){
        int x=personaje.getX();
        int y=personaje.getY();
        grafo->listaNodos->goToStart();
        for(int i=0;i<grafo->listaNodos->getSize();i++){
            Nodo *nodo=grafo->listaNodos->getElement();
            pared(nodo,x,y,grafo->dimensionY);
            if(nodo->getFruta()){
                dibujarGifs(x,y);
            }
            x+=desplazar;
            if((i+1)%grafo->dimensionY==0 && i!=0){
                x=personaje.getX();
                y+=desplazar;
            }
            grafo->listaNodos->next();
        }
    }

    // CAMBIA LA POSICION DEL NODO DONDE SE ENCUENTRA EL PERSONAJE
    void cambiarPosPersonaje(int &dimensionY){
        int des=desplazar;
        if(posx==posAntX+des){
            personaje.setPosicion(personaje.getPosicion()+1);
            posAntX=posx;
        }
        else if(posx==posAntX-des){
            personaje.setPosicion(personaje.getPosicion()-1);
            posAntX=posx;
        }
        else if(posy==posAntY-des){
            personaje.setPosicion(personaje.getPosicion()-dimensionY);
            posAntY=posy;
        }
        else if(posy==posAntY+des){
            personaje.setPosicion(personaje.getPosicion()+dimensionY);
            posAntY=posy;
        }
        cout<<"pos"<<personaje.getPosicion()<<endl;
    }
    //CAMBIA EL RUMBO Y LA POSICIÓN DEL PERSONAJE EN LA VENTANA
    void desplazarPersonaje(string direccion, int angulo,Grafo *&grafo){
            personaje.setHeading(angulo);
            Nodo *nodo=grafo->listaNodos->getElement();
            nodo->listaAristas->goToPos(0);
            if(direccion=="L" && nodo->listaAristas->getElement()->nodoDestino->numero==nodo->getNumero()-1){
                posx = (posx + (maxx - desplazar)) % maxx;
                personaje.setX(posx);
            }
            nodo->listaAristas->goToPos(1);
            if(direccion=="R" && nodo->listaAristas->getElement()->nodoDestino->numero==nodo->getNumero()+1
            ){
                posx = (posx + desplazar) % maxx;
                personaje.setX(posx);
            }
            nodo->listaAristas->goToPos(2);
            if(direccion=="U" && nodo->listaAristas->getElement()->nodoDestino->numero==nodo->getNumero()-grafo->dimensionY ){
                posy = (posy + (maxy - desplazar)) % maxy;
                personaje.setY(posy);
            }
            nodo->listaAristas->goToPos(3);
            if(direccion=="D" && nodo->listaAristas->getElement()->nodoDestino->numero==nodo->getNumero()+grafo->dimensionY){
                posy = (posy + desplazar) % maxy;
                personaje.setY(posy);
            }
        cambiarPosPersonaje(grafo->dimensionY);
    }

    //muestra la ruta más corta desde el personaje hasta la salida
    void pintarRutaCorta(Grafo *grafo,int pintar){
        DLinkedList<Nodo> *ruta=grafo->dijkstra(personaje.getPosicion());
        int xActual=personaje.getX();
        int yActual=personaje.getY();
        ruta->goToPos(ruta->getSize()-1);
        int posActual=ruta->getElement()->numero;
        cout<<"actual"<<posActual<<endl;
        int r=0;
        int g=25;
        int b=351;
        for(ruta->goToPos(ruta->getSize()-2);ruta->getPos()>=0;ruta->previous()){
            if(pintar){
                    setfillstyle(SOLID_FILL,COLOR(r,g,b));
                    g+=20;
                    b+=30;
            }
            else{setfillstyle(SOLID_FILL,COLOR(RFondo,GFondo,BFondo));}
            Nodo *nodo=ruta->getElement();
            if(nodo->getNumero()==posActual+1){
                xActual+=60;
                bar(xActual+17,yActual+15,xActual-43,yActual-15);
                if(nodo->getFruta())dibujarGifs(xActual,yActual);
            }
            if(nodo->getNumero()==posActual-1){
                xActual-=60;
                bar(xActual-11,yActual-15,xActual+49,yActual+15);
                if(nodo->getFruta())dibujarGifs(xActual,yActual);
            }
            if(nodo->getNumero()==posActual+grafo->dimensionY){
                yActual+=60;
                bar(xActual-11,yActual+15,xActual+17,yActual-45);
                if(nodo->getFruta())dibujarGifs(xActual,yActual);

            }
            if(nodo->getNumero()==posActual-grafo->dimensionY){
                yActual-=60;
                bar(xActual-11,yActual-15,xActual+17,yActual+45);
                if(nodo->getFruta())dibujarGifs(xActual,yActual);

            }
                posActual=nodo->getNumero();
            cout<<"pos actual"<<posActual<<endl;
            if(ruta->getPos()==0){
                break;
            }
        }
        personaje.DPersonaje1(0,3);
    }
    //DETECTA SI UNA TECLA FUE SELECCIONADA Y VERIFICA CUAL FUE
    void teclaSeleccionada(int &tecla, Grafo *&grafo){
        int flecha;
        grafo->listaNodos->goToPos(personaje.getPosicion());
        switch(tecla){
            case 0:
                pausa=false;
                flecha=getch();
                switch(flecha){
                    case KEY_UP: // HACIA ARRIBA
                        desplazarPersonaje("U",90,grafo);
                        break;
                    case KEY_LEFT: // HACIA LA IZQUIERDA
                        desplazarPersonaje("L",180,grafo);
                        break;
                    case KEY_RIGHT: // HACIA LA DERECHA
                        desplazarPersonaje("R",0,grafo);
                        break;
                    case KEY_DOWN: // HACIA ABAJO
                        desplazarPersonaje("D",270,grafo);
                        break;
                    case KEY_END:
                        pintarRutaCorta(grafo,1);
                        personaje.setAyuda(true);
                        pausa=true;
                        getch();
                        pausa=false;
                        pintarRutaCorta(grafo,0);
                        break;
                }break;
            case 27: // TECLA ESC
                    pausa=true;
                    break;
        }
    }
    //MUEVE AL PERSONAJE CONFORME ES PRESIONADA UNA TECLA
    void mover(Grafo *&grafo){
        int tecla;
        personaje.DPersonaje1(0,3); //PINTA EL PERSONAJE
        tecla = getch();// GUARDA LA TECLA SELECCIONADA
        personaje.DPersonaje1(1,3);//BORRA EL PERSONAJE
        grafo->listaNodos->goToPos(personaje.getPosicion());
        Nodo *nodo=grafo->listaNodos->getElement();
        recogerGifs(nodo);// REVISA SI PASO POR UN GIF
        //cout<<"GIFS: "<<personaje.getGifs()<<endl;
        teclaSeleccionada(tecla,grafo);//REVISA QUE FLECHA FUE SELECCIONADA
    }

    //REPRESENTA EN MODO GRAFICO EL TIEMPO RECIBIDO
    void tiempoA(int &tiempo){
        int x=100;
        int y=55;
        int seg = (tiempo)%60;
        int min = tiempo/60;
        if(min!=-1){
            if(seg!=-1){
                string time;
                stringstream ss,mm;
                mm<<min;
                ss<<seg;
                if(min>0){time=mm.str()+":"+ss.str();}
                else{time=ss.str();}
                const char * cronometro = ((string)time).c_str();
                if(seg<=5 && min<=0){
                    setcolor(COLOR(255,0,0));
                    outtextxy(maxx-x, maxy-y, cronometro);
                    Sleep(300);
                    outtextxy(maxx-x, maxy-y, "          ");
                    Sleep(900);
                }
                else{
                    setcolor(COLOR(255,255,51));
                    outtextxy(maxx-x, maxy-y, cronometro);
                    Sleep(1);
                    outtextxy(maxx-x, maxy-y, "          ");
                    Sleep(999);
                }
            }
        }
        tiempo--;
    }
};

#endif // INTERFAZ_H
