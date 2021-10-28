#include "luzposicional.h"

LuzPosicional::LuzPosicional(Tupla3f posicion,GLenum id,Tupla4f colorAmbiente,Tupla4f colorDifuso, Tupla4f colorEspecular){
    Tupla4f pos(posicion(0),posicion(1),posicion(2),1.0);
    this->posicion=pos;
    this->id=id;
    this->colorAmbiente=colorAmbiente;
    this->colorDifuso=colorDifuso;
    this->colorEspecular=colorEspecular;
}