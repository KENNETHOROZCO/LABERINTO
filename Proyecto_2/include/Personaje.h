#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <iostream>
#include <math.h>
class Personaje
{
private:
    int ejeX;
    int ejeY;
    int rumbo;
    int RT,RFondo;
    int GT,GFondo;
    int BT,BFondo;
    int extraTime;
    int gifs;
    int gifsP;
    int puntaje;
    int posicion;
    bool ayuda;

public:
    Personaje() {
    home();}
    virtual ~Personaje() {}
    void home(){
        rumbo=0;
        ejeX=480;
        ejeY=380;
        RT=0;
        GT=255;
        BT=0;
        RFondo=0;
        GFondo=0;
        BFondo=0;
        extraTime=0;
        gifs=0;
        gifsP=0;
        puntaje=0;
        posicion=0;
        ayuda=false;
    }
    void fondo(int r, int g, int b){
        RFondo=r;
        GFondo=g;
        BFondo=b;
    }
    //setter modifican los atributos
    void setAyuda(bool a){
        ayuda=a;
    }
    void setColoresT(int pRT,int pGT, int pBT){
        RT=pRT;
        GT=pGT;
        BT=pBT;
    }
    void setPos(int x,int y){
        ejeX=x;
        ejeY=y;
    }
    void setX(int x){
        ejeX=x;
    }
    void setY(int y){
        ejeY=y;
    }
    void setHeading(int grados){
        rumbo=fmod((360-grados),360);
    }
    void setGifs(){
        gifs+=gifsP;
        gifsP=0;
    }
    void setGifsP(int gif){
        gifsP+=gif;
    }
    void setExtraTime(int pTime){
        extraTime=pTime;
    }
    void setPuntaje(int pPuntaje){
        puntaje+=pPuntaje;
    }
    void setPosicion(int pos){
        posicion=pos;
    }
    //getters solo muestran los datos no modifican
    int getGifs(){
        return gifs;
    }
    int getGifsP(){
        return gifsP;
    }
    int getExtraTime(){
        return extraTime;
    }
    int getPosicion(){
        return posicion;
    }
    bool getAyuda(){
        return ayuda;
    }
    int getRT(){
        return RT;
    }
    int getGT(){
        return GT;
    }
    int getBT(){
        return BT;
    }
    int getX(){
        return ejeX;
    }
    int getY(){
        return ejeY;
    }
    int getHeading(){
        return rumbo;
    }
    int getHead(){
        return fmod((360-rumbo),360);
    }
    int getPuntaje(){
        return puntaje;
    }

void DPersonaje1(int pintar,int pTam){
    int tam=pTam;
    int x=ejeX-2;
    int y=ejeY-12;
    if(pintar==0){
        setfillstyle(SOLID_FILL,COLOR(RT,GT,BT));
        int a=x,b=y;
        for (int i=0;i<3;i++){
            bar(a,b,a+tam,b+tam);
            a+=tam;
        }
        a=x-tam;
        b+=tam;
        for(int i=0;i<5;i++){
            bar(a,b,a+tam,b+tam);
            a+=tam;
        }
        a=x-(2*tam);
        b+=tam;
        bar(a,b,a+(7*tam),b+(5*tam));
        setfillstyle(SOLID_FILL,COLOR(255,255,255));
        bar(a+tam,b,a+(3*tam),b+4);
        bar(a+tam,b+4,a+(2*tam),b+8);
        bar(a+(4*tam),b,a+(6*tam),b+4);
        bar(a+(4*tam),b+4,a+(5*tam),b+8);
        setfillstyle(SOLID_FILL,COLOR(0,0,0));
        bar(a+(2*tam),b+4,a+(3*tam),b+8);
        bar(a+(5*tam),b+4,a+(6*tam),b+8);
        setfillstyle(SOLID_FILL,COLOR(0,255,0));
        b+=(5*tam);
        for(int i=0;i<4;i++){
            bar(a,b,a+tam,b+tam);
            a+=(2*tam);
        }
    }
    else{
       setfillstyle(SOLID_FILL,COLOR(RFondo,GFondo,BFondo));
       bar(x-(2*tam),y,x+15,y+25);
    }
}

};

#endif // PERSONAJE_H
