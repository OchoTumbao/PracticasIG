#include "luces.h"
Tupla4f RotaEjeY(Tupla4f punto, float radianes){
   float resx,resy,resz,resw;
   resx=punto(0)*cos(radianes)+punto(2)*sin(radianes);
   resy=punto(1);
   resz=punto(0)*-sin(radianes)+punto(2)*cos(radianes);
   resw=punto(3);
   return Tupla4f(resx,resy,resz,resw);
}

Tupla4f RotaEjeX(Tupla4f punto, float radianes){
   float resx,resy,resz,resw;
   resx=punto(0);
   resy=punto(1)*cos(radianes)+punto(2)*-sin(radianes);
   resz=punto(1)*sin(radianes)+punto(2)*cos(radianes);
   resw=punto(3);
   return Tupla4f(resx,resy,resz,resw);
}

LuzDireccional::LuzDireccional(Tupla2f direccion,GLenum id,Tupla4f colorAmbiente,Tupla4f colorDifuso, Tupla4f colorEspecular){
    Tupla4f pos(0.0,0.0,1.0,0.0);
    this->alpha=direccion(0);
    this->beta=direccion(1);
    pos=RotaEjeX(pos,direccion(0));
    pos=RotaEjeY(pos,direccion(1));
    this->posicion=pos;
    this->id=id;
    this->colorAmbiente=colorAmbiente;
    this->colorDifuso=colorDifuso;
    this->colorEspecular=colorEspecular;

}

void LuzDireccional::variarAnguloAlpha(float incremento){
    alpha+=incremento;
    this->posicion=RotaEjeX(posicion,incremento);
}

void LuzDireccional::variarAnguloBeta(float incremento){
    beta+=incremento;
    this->posicion=RotaEjeY(posicion,incremento);
}

LuzPosicional::LuzPosicional(Tupla3f posicion,GLenum id,Tupla4f colorAmbiente,Tupla4f colorDifuso, Tupla4f colorEspecular){
    Tupla4f pos(posicion(0),posicion(1),posicion(2),1.0);
    this->posicion=pos;
    this->id=id;
    this->colorAmbiente=colorAmbiente;
    this->colorDifuso=colorDifuso;
    this->colorEspecular=colorEspecular;
}