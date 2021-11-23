#include "KlinkKlang.h"
#include <math.h>

Engranaje::Engranaje(int num_dientes,float radio,int eje,float grosor,bool semiesfera){
    this->num_dientes=num_dientes;
    this->radio=radio;
    this->eje=eje;
    this->grosor=grosor;
    this->semiesfera=semiesfera;
    cilindro= new Cilindro(50,50,grosor,radio,eje,true,true);
    float lado=((2*M_PI*radio)/num_dientes)/2;
    cubo= new Cubo(grosor-0.2);
    esfera= new Semiesfera(50,50,radio*0.30,eje,true,true);
    Tupla4f Cromoa(0.25,0.25,0.25,1.0);
    Tupla4f CromoD(0.4,0.4,0.4,1.0);
    Tupla4f CromoE(0.774597,0.774597,0.774597,1.0);
    float Cromob=76.8;

    m1=new Material(CromoD,CromoE,Cromoa,Cromob);

    cilindro->setMaterial(*m1);
    cubo->setMaterial(*m1);

    Tupla4f CyanA(0.0,0.1,0.06,1.0);
    Tupla4f CyanD(0.0,0.50980392,0.50980392,1.0);
    Tupla4f CyanE(0.50196078,0.50196078,0.50196078,1.0);
    float Cyanb=32.0;

    m2=new Material(CyanD,CyanE,CyanA,Cyanb);
    esfera->setMaterial(*m2);

    
}

void Engranaje::draw(int modo_diferido,int modo_dibujo){
    cilindro->draw(modo_diferido,modo_dibujo);

    for(int i=0;i<num_dientes;i++){
        glPushMatrix();
        switch(eje){
            case 0:
                glTranslatef(grosor/2,cos(((2*M_PI)/num_dientes)*i)*radio,sin(((2*M_PI)/num_dientes)*i)*radio);
                glRotatef(i*360/num_dientes,1,0,0);
                break;
            case 1:
                glTranslatef(cos(((2*M_PI)/num_dientes)*i)*radio,0,-sin(((2*M_PI)/num_dientes)*i)*radio);
                glRotatef(i*(360/num_dientes),0,1,0);
                break;
            case 2:
                glTranslatef(cos(((2*M_PI)/num_dientes)*i)*radio,sin(((2*M_PI)/num_dientes)*i)*radio,grosor/2);
                glRotatef(i*(360/num_dientes),0,0,1);
                break;
        }
        cubo->draw(modo_diferido,modo_dibujo);
        glPopMatrix();
    }
    if(semiesfera){
        glPushMatrix();
        switch(eje){
            case 0:
                glTranslatef(-grosor/2,0,0);
                break;
            case 1:
                glTranslatef(0,-grosor/2,0);
                break;
            case 2:
                glTranslatef(0,0,-grosor/2);
                break;}

        esfera->draw(modo_diferido,modo_dibujo);
        glPopMatrix();
    }
        
}

void Engranaje::drawAjedrez(int modo_diferido){
    cilindro->drawAjedrez(modo_diferido);

    esfera->drawAjedrez(modo_diferido);

    for(int i=0;i<num_dientes;i++){
        glPushMatrix();
        switch(eje){
            case 0:
                glTranslatef(grosor/2,cos(((2*M_PI)/num_dientes)*i)*radio,sin(((2*M_PI)/num_dientes)*i)*radio);
                glRotatef(i*360/num_dientes,1,0,0);
                break;
            case 1:
                glTranslatef(cos(((2*M_PI)/num_dientes)*i)*radio,0,-sin(((2*M_PI)/num_dientes)*i)*radio);
                glRotatef(i*(360/num_dientes),0,1,0);
                break;
            case 2:
                glTranslatef(cos(((2*M_PI)/num_dientes)*i)*radio,sin(((2*M_PI)/num_dientes)*i)*radio,grosor/2);
                glRotatef(i*(360/num_dientes),0,0,1);
                break;
        }
        cubo->drawAjedrez(modo_diferido);
        glPopMatrix();
    }
}
Banda::Banda(){
    cilindro = new Cilindro(20,20,10,70,1,false,false);
    cono = new Cono(20,50,10,5,0,true,true);
    Tupla4f Cromoa(0.105882, 0.058824, 0.113725, 1.0);
    Tupla4f CromoD(0.427451, 0.470588, 0.541176, 1.0);
    Tupla4f CromoE(0.333333, 0.333333, 0.521569, 1.0);
    float Cromob=9.84615;

    m1=new Material(CromoD,CromoE,Cromoa,Cromob);
    cilindro->setMaterial(*m1);
    cono->setMaterial(*m1);
}

void Banda::draw(int modo_diferido,int modo_dibujo){
    cilindro->draw(modo_diferido,modo_dibujo);
    for(int i=0;i<10;i++){
    glPushMatrix();
    glTranslatef(cos(((2*M_PI)/10)*i)*70,5,-sin(((2*M_PI)/10)*i)*70);
    glRotatef(i*(360/10),0,1,0);
    cono->draw(modo_diferido,modo_dibujo);
    glPopMatrix();
    }
}

void Banda::drawAjedrez(int modo_diferido){
    cilindro->drawAjedrez(modo_diferido);
    for(int i=0;i<10;i++){
    glPushMatrix();
    glTranslatef(cos(((2*M_PI)/10)*i)*70,5,-sin(((2*M_PI)/10)*i)*70);
    glRotatef(i*(360/10),0,1,0);
    cono->drawAjedrez(modo_diferido);
    glPopMatrix();
    }
}

KlinkKlang::KlinkKlang(){
    banda = new Banda();
    engranaje1= new Engranaje(30,45,2,7.5,false);
    engranaje2= new Engranaje(15,25,2,7.5,true);
    engranaje3= new Engranaje(15,25,2,7.5,true);
    engranaje4= new Engranaje(15,25,1,7.5,true);
}

void KlinkKlang::draw(int modo_diferido,int modo_dibujo){
    //Gestion  banda y engranaje interior
    glPushMatrix();
    glTranslatef(0,-35,0);
    glPushMatrix();
    glRotatef(-anguloBanda,0,1,0);
    banda->draw(modo_diferido,modo_dibujo);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-22.5);
    glRotatef(-anguloEngranajes,0,1,0);
    engranaje4->draw(modo_diferido,modo_dibujo);
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,iy,0);
    glPushMatrix();
    glTranslatef(0,0,7.5);
    glRotatef(-anguloEngranajes,0,0,1);
    engranaje1->draw(modo_diferido,modo_dibujo);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-anguloEngranajes,0,0,1);
    engranaje2->draw(modo_diferido,modo_dibujo);
    glPopMatrix();   
    glPushMatrix();
    glTranslatef(40,40,0);
    glRotatef(anguloEngranajes,0,0,1);
    engranaje3->draw(modo_diferido,modo_dibujo);
    glPopMatrix();
    glPopMatrix();

}

void KlinkKlang::drawAjedrez(int modo_diferido){
    //Gestion  banda y engranaje interior
    glPushMatrix();
    glTranslatef(0,-35,0);
    glPushMatrix();
    glRotatef(-anguloBanda,0,1,0);
    banda->drawAjedrez(modo_diferido);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-22.5);
    glRotatef(-anguloEngranajes,0,1,0);
    engranaje4->drawAjedrez(modo_diferido);
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,iy,0);
    glPushMatrix();
    glTranslatef(0,0,7.5);
    glRotatef(-anguloEngranajes,0,0,1);
    engranaje1->drawAjedrez(modo_diferido);
    glPopMatrix();
    glPushMatrix();
    glRotatef(-anguloEngranajes,0,0,1);
    engranaje2->drawAjedrez(modo_diferido);
    glPopMatrix();   
    glPushMatrix();
    glTranslatef(40,40,0);
    glRotatef(anguloEngranajes,0,0,1);
    engranaje3->drawAjedrez(modo_diferido);
    glPopMatrix();
    glPopMatrix();

}

void KlinkKlang::modifica_anguloBanda(float porcentaje){

    if(porcentaje>=0 && porcentaje<=2.5){
        this->anguloBanda=fmod(this->anguloBanda+(2*porcentaje),360);
    }
}

void KlinkKlang::modifica_anguloEngranajes(float porcentaje){
    if(porcentaje>=0 && porcentaje<=2.5){
        this->anguloEngranajes=fmod(this->anguloEngranajes+(2*porcentaje),360);
    }
        
}

void KlinkKlang::modifica_Posicion(float porcentaje){
    if(arriba){
        this->iy+=(1*porcentaje);
        if(this->iy>=35){
            this->iy=35;
            arriba=false;
        }
    } else {
        this->iy-=(1*porcentaje);
        if(this->iy<=0){
            this->iy=0;
            arriba=true;
        }
    }
}