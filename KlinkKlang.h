#include "aux.h"
#include "cilindro.h"
#include "semiesfera.h"
#include "cubo.h"
#include "cono.h"
#include "toroide.h"
#include "esfera.h"
#include "objply.h"

class Engranaje{
    public:
    Engranaje(int num_dientes,float radio,int eje,float grosor,bool semiesfera);
    void draw(int modo_diferido,int modo_dibujo);
    void drawAjedrez(int modo_diferido);
    private:
    Cilindro* cilindro;
    Cubo* cubo;
    Semiesfera* esfera;
    int num_dientes;
    float radio;
    bool semiesfera;
    int eje;
    float grosor;
    Material * m1=nullptr;
    Material * m2=nullptr;


};


class Banda{
    public:
    Banda();
    void draw(int modo_diferido,int modo_dibujo);
    void drawAjedrez(int modo_diferido);
    private:
    Toroide *cilindro;
    Cono *cono;
    Material * m1=nullptr;
};

class KlinkKlang{
    public:
    KlinkKlang();
    void draw(int modo_diferido,int modo_dibujo);
    void drawAjedrez(int modo_diferido);
    void modifica_anguloEngranajes(float porcentaje);
    void modifica_anguloBanda(float porcentaje);
    void modifica_Posicion(float porcentaje);
    void modifica_PosicionPokeball(float porcentaje);
    void modifica_Escala(float porcentaje);
    private:
    Banda *banda;
    Engranaje *engranaje1;
    Engranaje *engranaje2;
    Engranaje *engranaje3;
    Engranaje *engranaje4;
    ObjRevolucion * pokeball;
    float iy=0;
    float anguloEngranajes=0;
    float anguloBanda=0;
    float posx_pokeball=0;
    float posy_pokeball=0;
    float velocidad_tiroy=100*cos(M_PI/4);
    float velocidad_tirox=100*sin(M_PI/4);
    float angulo_pokeball=0;
    float scale=0.01;
    float tiempo=0.5;
    bool arriba=true;
};


class Magnemite{
    public:
    Magnemite();
    void draw(int modo_diferido,int modo_dibujo);
    void drawAjedrez(int modo_diferido);
    void modifica_posicionPokeball(float porcentaje);
    void modifica_posicion(float porcentaje);
    void modifica_anguloIman(float porcentaje);
    private:
    ObjRevolucion * esfera=nullptr;
    ObjPLY * Iman1=nullptr;
    ObjPLY * Tornillo1=nullptr;
    Cubo * polo_norte1=nullptr;
    Cubo * polo_sur1=nullptr;
    ObjRevolucion * pokeball=nullptr;
    Material *m1=nullptr;
    Material *m2=nullptr;
    Material *m3=nullptr;
    Material *m4=nullptr;
    Material *m5=nullptr;
    float iy=0;
    float ix=0;
    float angulo_imanes=0;
    float posx_pokeball=0;
    float posy_pokeball=0;
    float velocidad_tiroy=100*cos(M_PI/4);
    float velocidad_tirox=100*sin(M_PI/4);
    float angulo_pokeball=0;
    float scale=0.01;
    float tiempo=0.5;
    float alphaelipse=0;
    bool vuelta=false;
};
