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
    int RT;
    int GT;
    int BT;
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
        GT=0;
        BT=0;
        extraTime=0;
        gifs=0;
        gifsP=0;
        puntaje=0;
        posicion=0;
        ayuda=false;
    }
    void home1(){
        rumbo=0;
        ejeX=350;
        ejeY=350;
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
    //dibuja la tortuga
void DPersonaje(int b){
    setlinestyle(6,1,3);
    if(b==1){RT=0;GT=102;BT=102;}//200,165,20
    else{RT=0;GT=255;BT=0;}
    setcolor(COLOR(RT,GT,BT));
    //cuerpo
    setfillstyle(1,COLOR(RT,GT,BT));
    //cabeza
    int x2=cos((rumbo*M_PI)/180)*11;//18
    int y2=sin((rumbo*M_PI)/180)*11;//18
    fillellipse(ejeX+x2,ejeY+y2,4,4);//8-7
    //pie Superior Izquierdo
    int rumbo2=fmod(rumbo-60,360);
    int x3=cos((rumbo2*M_PI)/180)*11;//17
    int y3=sin((rumbo2*M_PI)/180)*11;//17
    fillellipse(ejeX+x3,ejeY+y3,2,2);//5-5
    //pie Inferior Izquierdo
    int rumbo3=fmod(rumbo-130,360);
    int x4=cos((rumbo3*M_PI)/180)*12;//17
    int y4=sin((rumbo3*M_PI)/180)*12;//17
    fillellipse(ejeX+x4,ejeY+y4,2,2);//5-5
    //pie Superior Derecho
    int rumbo4=fmod(rumbo-300,360);
    int x5=cos((rumbo4*M_PI)/180)*11;//17
    int y5=sin((rumbo4*M_PI)/180)*11;//17
    fillellipse(ejeX+x5,ejeY+y5,2,2);//5-5
    //pie Inferior Derecho
    int rumbo5=fmod(rumbo-230,360);
    int x6=cos((rumbo5*M_PI)/180)*12;//18
    int y6=sin((rumbo5*M_PI)/180)*12;//18
    fillellipse(ejeX+x6,ejeY+y6,2,2);
    if(b==0){
       setfillstyle(INTERLEAVE_FILL,COLOR(0,102,102));
    }
    else{
        setfillstyle(HATCH_FILL,COLOR(RT,GT,BT));//100 51 25
    }
    fillellipse(ejeX,ejeY,7,7);

}

void DPersonaje1(int pintar){
    int tam=3;
    int x=ejeX-2;
    int y=ejeY-12;
    if(pintar==0){
        setfillstyle(SOLID_FILL,COLOR(0,255,0));
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
       setfillstyle(SOLID_FILL,COLOR(0,0,0));
       bar(x-(2*tam),y,x+15,y+25);
    }
}

};

#endif // PERSONAJE_H
