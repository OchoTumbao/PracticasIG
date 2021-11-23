#include "aux.h"
#include "cilindro.h"
#include "semiesfera.h"
#include "cubo.h"
#include "cono.h"

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
    Cilindro *cilindro;
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
    private:
    Banda *banda;
    Engranaje *engranaje1;
    Engranaje *engranaje2;
    Engranaje *engranaje3;
    Engranaje *engranaje4;
    float iy=0;
    float anguloEngranajes=0;
    float anguloBanda=0;
    bool arriba=true;
};
