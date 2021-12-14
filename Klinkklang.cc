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
    cubo= new Cubo(grosor-0.2,false,false);
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
                
                glRotatef(i*(360/num_dientes),0,1,0);
                break;
            case 1:
                glRotatef(i*(360/num_dientes),0,1,0);
                break;
            case 2:
                glRotatef(i*(360/num_dientes),0,0,1);
                break;
        }
        switch(eje){
            case 0:
                
                glTranslatef(grosor/2,0,radio);
                break;
            case 1:
                glTranslatef(radio,0,0);
                break;
            case 2:
                glTranslatef(radio,0,grosor/2);
                break;
        }

        cubo->draw(modo_diferido,modo_dibujo);
        glPopMatrix();
    }
    if(semiesfera){
        glPushMatrix();
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
                
                glRotatef(i*(360/num_dientes),0,1,0);
                break;
            case 1:
                glRotatef(i*(360/num_dientes),0,1,0);
                break;
            case 2:
                glRotatef(i*(360/num_dientes),0,0,1);
                break;
        }
        switch(eje){
            case 0:
                
                glTranslatef(grosor/2,0,radio);
                break;
            case 1:
                glTranslatef(radio,0,0);
                break;
            case 2:
                glTranslatef(radio,0,grosor/2);
                break;
        }
        cubo->drawAjedrez(modo_diferido);
        glPopMatrix();
    if(semiesfera){
        glPushMatrix();
        switch(eje){
            case 0:
                glTranslatef(-grosor/2,0,0);
                break;
            case 1:
                glTranslatef(0,-grosor/2,0);
                glRotatef(180,0,0,1);
                break;
            case 2:
                glTranslatef(0,0,-grosor/2);
                break;}

        esfera->drawAjedrez(modo_diferido);
        glPopMatrix();
    }
    }
}
Banda::Banda(){
    cilindro = new Toroide(50,50,5,70,false,false);
    cono = new Cono(20,50,10,3,0,true,true);
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
    glRotatef(i*(360/10),0,1,0);
    glTranslatef(74,0,0);
    
    cono->draw(modo_diferido,modo_dibujo);
    glPopMatrix();
    }
}

void Banda::drawAjedrez(int modo_diferido){
    cilindro->drawAjedrez(modo_diferido);
    for(int i=0;i<10;i++){
    glPushMatrix();
    glRotatef(i*(360/10),0,1,0);
    glTranslatef(74,0,0);
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
    pokeball= new Esfera(200,200,"text-pokeball.jpg",15,1,true,true);
Tupla4f mat_ambient( 0.0f,0.0f,0.0f,1.0f );
Tupla4f mat_diffuse ( 0.55f,0.55f,0.55f,1.0f);
Tupla4f mat_specular(0.70f,0.70f,0.70f,1.0f);
float shine = 32.0f ;
Material * m1= new Material(mat_diffuse,mat_specular,mat_ambient,shine);
    pokeball->setMaterial(*m1);
}

void KlinkKlang::draw(int modo_diferido,int modo_dibujo){
    //Gestion  banda y engranaje interior
    glPushMatrix();
    glTranslatef(0,posy_pokeball,posx_pokeball);
    glPushMatrix();
    glRotatef(angulo_pokeball,1,1,0);
    //printf("%f %f %f\n",posx_pokeball,posy_pokeball,0);
    pokeball->draw(modo_diferido,modo_dibujo);
    glPopMatrix();
    glPushMatrix();
    glScalef(scale,scale,scale);
    glTranslatef(0,100,0);
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
    glPopMatrix();
    glPopMatrix();

}

void KlinkKlang::drawAjedrez(int modo_diferido){
    //Gestion  banda y engranaje interior
    glPushMatrix();
    glTranslatef(0,posy_pokeball,posx_pokeball);
    glPushMatrix();
    glRotatef(angulo_pokeball,1,1,0);
    //printf("%f %f %f\n",posx_pokeball,posy_pokeball,0);
    pokeball->drawAjedrez(modo_diferido);
    glPopMatrix();
    glPushMatrix();
    glScalef(scale,scale,scale);
    glTranslatef(0,100,0);
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

void KlinkKlang::modifica_PosicionPokeball(float porcentaje){
    if(posy_pokeball>=0){
        this->posy_pokeball+=((porcentaje*velocidad_tiroy)*tiempo);
        this->velocidad_tiroy=velocidad_tiroy-(9.8*tiempo);
        //printf("nuevo valor de velocidad=%f\n",velocidad_tiroy);
        //printf("nuevo valor de y=%f\n",this->posy_pokeball);
        this->posx_pokeball+=((porcentaje*velocidad_tirox)*tiempo);
        //printf("nuevo valor de x=%f\n",this->posx_pokeball);
        this->angulo_pokeball=fmod(this->angulo_pokeball+(10*porcentaje),360);
    } else if (scale<=2.0){
        this->scale+=0.05;
    }
}


Magnemite::Magnemite(){
    Tornillo1=new ObjPLY("plys/screw.ply");
    esfera=new Esfera(200,200,"text-magnemite.jpg",30,1,true,true);
    Iman1=new ObjPLY("plys/iman.ply");
    polo_norte1=new Cubo(0.95,false,false);
    polo_sur1=new Cubo(0.95,false,false);
    pokeball= new Esfera(200,200,"text-pokeball.jpg",15,1,true,true);


    Tupla4f Cromoa(0.105882, 0.058824, 0.113725, 1.0);
    Tupla4f CromoD(0.427451, 0.470588, 0.541176, 1.0);
    Tupla4f CromoE(0.333333, 0.333333, 0.521569, 1.0);
    float Cromob=76.8f;

    Tupla4f BPa(0.05375f, 0.05f, 0.06625f, 0.82f);
    Tupla4f BPD(0.18275f, 0.17f, 0.22525f, 0.82f);
    Tupla4f BPE(0.332741f, 0.328634f, 0.346435f, 0.82f);
    float BPb=38.4f;

    Tupla4f RPa(0.1745f, 0.01175f, 0.01175f, 0.55f);
    Tupla4f RPD(0.61424f, 0.04136f, 0.04136f, 0.55f);
    Tupla4f RPE(0.727811f, 0.626959f, 0.626959f, 0.55f);
    float RPb=76.8f ;

    Tupla4f CPa(0.0f,0.1f,0.06f ,1.0f);
    Tupla4f CPD(0.0f,0.50980392f,0.50980392f,1.0f);
    Tupla4f CPE(0.50196078f,0.50196078f,0.50196078f,1.0f);
    float CPb=32.0f;


    Tupla4f mat_ambient( 0.0f,0.0f,0.0f,1.0f );
    Tupla4f mat_diffuse ( 0.55f,0.55f,0.55f,1.0f);
    Tupla4f mat_specular(0.70f,0.70f,0.70f,1.0f);
    float shine = 32.0f ;

    m1=new Material(CromoD,CromoE,Cromoa,Cromob);
    m2=new Material(BPD,BPE,BPa,BPb);
    m3=new Material(RPD,RPE,RPa,RPb);
    m4=new Material(CPD,CPE,CPa,CPb);
    m5= new Material(mat_diffuse,mat_specular,mat_ambient,shine);
    Tornillo1->setMaterial(*m1);
    esfera->setMaterial(*m1);
    Iman1->setMaterial(*m2);
    polo_norte1->setMaterial(*m3);
    polo_sur1->setMaterial(*m4);
    pokeball->setMaterial(*m5);
}

void Magnemite::draw(int modo_diferido,int modo_dibujo){
    glPushMatrix(); //1
    glTranslatef(0,posy_pokeball,posx_pokeball);
    glPushMatrix(); // 2
    glRotatef(angulo_pokeball,1,1,0);
    //printf("%f %f %f\n",posx_pokeball,posy_pokeball,0);
    pokeball->draw(modo_diferido,modo_dibujo);
    glPopMatrix(); //1
    glPushMatrix(); // 3
    glScalef(scale,scale,scale);
    glTranslatef(ix,iy,0);
    glPushMatrix();// 4
    glTranslatef(0,115,0);
    glPushMatrix();// 5
    glRotatef(-75,0,1,0);
    esfera->draw(modo_diferido,modo_dibujo);
    glPopMatrix(); // 2
    glPushMatrix(); // 6
    glTranslatef(-43.5,0,0);
    glScalef(10,10,10);
    glRotatef(-90,0,1,0);
    glRotatef(angulo_imanes,0,0,1);
    Iman1->draw(modo_diferido,modo_dibujo);
    glPushMatrix(); // 7
    glTranslatef(0.15,0,1.5);
    glPushMatrix(); // 8
    glTranslatef(0,0.8,0);
    polo_norte1->draw(modo_diferido,modo_dibujo);
    glPopMatrix(); // 3
    glPushMatrix(); // 9
    glTranslatef(0,-1.3,0);
    polo_sur1->draw(modo_diferido,modo_dibujo);
    glPopMatrix();// 4
    glPopMatrix(); // 5
    glPopMatrix(); // 6
    glPushMatrix(); // 10
    glTranslatef(43.5,0,0);
    glScalef(10,10,10);
    glRotatef(90,0,1,0);
    glRotatef(-angulo_imanes,0,0,1);
    Iman1->draw(modo_diferido,modo_dibujo);
    glPushMatrix(); // 11
    glTranslatef(0.15,0,1.5);
    glPushMatrix(); // 12
    glTranslatef(0,0.8,0);
    polo_norte1->draw(modo_diferido,modo_dibujo);
    glPopMatrix(); // 7
    glPushMatrix(); // 13
    glTranslatef(0,-1.3,0);
    polo_sur1->draw(modo_diferido,modo_dibujo);
    glPopMatrix(); // 8
    glPopMatrix(); // 9
    glPopMatrix(); // 10
    glPushMatrix(); //14
    glTranslatef(0,40,0);
    glScalef(0.5,0.5,0.5);
    Tornillo1->draw(modo_diferido,modo_dibujo);
    glPopMatrix(); // 11
    glPopMatrix(); // 12
    glPopMatrix(); // 13
    glPopMatrix(); // 14


}

void Magnemite::drawAjedrez(int modo_diferido){
    glPushMatrix(); //1
    glTranslatef(0,posy_pokeball,posx_pokeball);
    glPushMatrix(); // 2
    glRotatef(angulo_pokeball,1,1,0);
    //printf("%f %f %f\n",posx_pokeball,posy_pokeball,0);
    pokeball->drawAjedrez(modo_diferido);
    glPopMatrix(); //1
    glPushMatrix(); // 3
    glTranslatef(ix,iy,0);
    glScalef(scale,scale,scale);
    glPushMatrix();// 4
    glTranslatef(0,115,0);
    glPushMatrix();// 5
    glRotatef(-75,0,1,0);
    esfera->drawAjedrez(modo_diferido);
    glPopMatrix(); // 2
    glPushMatrix(); // 6
    glTranslatef(-43.5,0,0);
    glScalef(10,10,10);
    glRotatef(-90,0,1,0);
    glRotatef(angulo_imanes,0,0,1);
    Iman1->drawAjedrez(modo_diferido);
    glPushMatrix(); // 7
    glTranslatef(0.15,0,1.5);
    glPushMatrix(); // 8
    glTranslatef(0,0.8,0);
    polo_norte1->drawAjedrez(modo_diferido);
    glPopMatrix(); // 3
    glPushMatrix(); // 9
    glTranslatef(0,-1.3,0);
    polo_sur1->drawAjedrez(modo_diferido);
    glPopMatrix();// 4
    glPopMatrix(); // 5
    glPopMatrix(); // 6
    glPushMatrix(); // 10
    glTranslatef(43.5,0,0);
    glScalef(10,10,10);
    glRotatef(90,0,1,0);
    glRotatef(-angulo_imanes,0,0,1);
    Iman1->drawAjedrez(modo_diferido);
    glPushMatrix(); // 11
    glTranslatef(0.15,0,1.5);
    glPushMatrix(); // 12
    glTranslatef(0,0.8,0);
    polo_norte1->drawAjedrez(modo_diferido);
    glPopMatrix(); // 7
    glPushMatrix(); // 13
    glTranslatef(0,-1.3,0);
    polo_sur1->drawAjedrez(modo_diferido);
    glPopMatrix(); // 8
    glPopMatrix(); // 9
    glPopMatrix(); // 10
    glPushMatrix(); //14
    glTranslatef(0,40,0);
    glScalef(0.5,0.5,0.5);
    Tornillo1->drawAjedrez(modo_diferido);
    glPopMatrix(); // 11
    glPopMatrix(); // 12
    glPopMatrix(); // 13
    glPopMatrix(); // 14


}

void Magnemite::modifica_posicionPokeball(float porcentaje){
    if(posy_pokeball>=0){
        this->posy_pokeball+=((porcentaje*velocidad_tiroy)*tiempo);
        this->velocidad_tiroy=velocidad_tiroy-(9.8*tiempo);
        //printf("nuevo valor de velocidad=%f\n",velocidad_tiroy);
        //printf("nuevo valor de y=%f\n",this->posy_pokeball);
        this->posx_pokeball+=((porcentaje*velocidad_tirox)*tiempo);
        //printf("nuevo valor de x=%f\n",this->posx_pokeball);
        this->angulo_pokeball=fmod(this->angulo_pokeball+(10*porcentaje),360);
    } else {
        if (scale<=1.0){
        this->scale+=0.05;
        } 
    }
}

void Magnemite::modifica_posicion(float porcentaje){
    ix=70*cos(alphaelipse);
    iy=40*sin(alphaelipse);
    alphaelipse=fmod(alphaelipse+(0.065*porcentaje),2*M_PI);

}

void Magnemite::modifica_anguloIman(float porcentaje){
    if(!vuelta){
    angulo_imanes=(angulo_imanes+(5*porcentaje));
    if(angulo_imanes>=180){
        vuelta=true;
    }
    } else{
    angulo_imanes=(angulo_imanes-(5*porcentaje));
    if(angulo_imanes<=0){
        vuelta=false;
    }
    }

}
