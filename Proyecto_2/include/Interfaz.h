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


using namespace std;

class Interfaz
{
private:
    int desplazar=10;// CANTIDAD DE ESPACIOS QUE SE VA A MOVER EL PERSONAJE
    int color;
    int maxx = 900;
    int maxy = 700;
    int posx, posy;

public:
    bool fin = true;
    Personaje personaje;
    Interfaz() {}
    virtual ~Interfaz() {}

    void crearVentana(){
        // INICIALIZACION DE MODO GRAFICO
        initwindow(maxx, maxy);
        setbkcolor(COLOR(200,165,20));
        cleardevice();
        posx = maxx/2;
        posy = maxy/2;
    }

    void dibujarGifs(bool pintar,int x, int y){
        if(pintar==true){
            setfillstyle(1,COLOR(255,0,0));
            setcolor(COLOR(255,0,0));
            fillellipse(x-6,y,7,9);
            fillellipse(x+2,y,7,9);
            setcolor(COLOR(0,255,0));
            setlinestyle(1,0,2);
            line(x-3,y-8,x-4,y-12);
            line(x-4,y-12,x-8,y-12);
            setcolor(COLOR(255,255,255));
            fillellipse(x+3,y-4,2,2);
        }
        else{
            setfillstyle(2,COLOR(0,0,0));}
    }
    void recogerGifs(){
        if(personaje.getX()==100 && personaje.getY()==100){personaje.setGifs(1);}
        if(personaje.getX()==250 && personaje.getY()==250){personaje.setGifs(1);}
        if(personaje.getX()==600 && personaje.getY()==600){personaje.setGifs(1);}
        if(personaje.getX()==400 && personaje.getY()==400){personaje.setGifs(1);}
    }

    void teclaSeleccionada(int &tecla){
        int flecha;
        //personaje.setAyuda(false);
        switch(tecla){
            case 0:
                flecha=getch();
                switch(flecha){
                    case KEY_UP: // HACIA ARRIBA
                        posy = (posy + (maxy - desplazar)) % maxy;personaje.setHeading(90);
                        break;
                    case KEY_LEFT: // HACIA LA IZQUIERDA
                        posx = (posx + (maxx - desplazar)) % maxx;personaje.setHeading(180);
                        break;
                    case KEY_RIGHT: // HACIA LA DERECHA
                        posx = (posx + desplazar) % maxx;personaje.setHeading(0);
                        break;
                    case KEY_DOWN: // HACIA ABAJO
                        posy = (posy + desplazar) % maxy;personaje.setHeading(270);
                        break;
                    case KEY_END:
                        personaje.setAyuda(true);
                        break;
                }break;
            case 27: // TECLA ESC
                    fin = false;
                    break;
        }
    }
    void mover(){
        int tecla;
        /*dibujarGifs(true,200,200);
        dibujarGifs(true,100,100);
        dibujarGifs(true,250,250);
        dibujarGifs(true,600,600);
        dibujarGifs(true,400,400);*/
        personaje.setPos(posx,posy);
        personaje.DPersonaje(0); //PINTA EL PERSONAJE
        tecla = getch();// GUARDA LA TECLA SELECCIONADA
        personaje.DPersonaje(1);//BORRA EL PERSONAJE
        recogerGifs();// REVISA SI PASO POR UN GIF
        cout<<"GIFS: "<<personaje.getGifs()<<endl;
        teclaSeleccionada(tecla);//REVISA QUE FLECHA FUE SELECCIONADA
    }

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
                    outtextxy(maxx-x, maxy-y, "        ");
                    Sleep(900);
                }
                else{
                    setcolor(COLOR(102,51,0));
                    outtextxy(maxx-x, maxy-y, cronometro);
                    Sleep(1);
                    outtextxy(maxx-x, maxy-y, "        ");
                    Sleep(999);

                }
            }
        }
        tiempo--;
    }
};

#endif // INTERFAZ_H
