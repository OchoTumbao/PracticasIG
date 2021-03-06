#include "luz.h"

class LuzDireccional : public Luz
{
protected:
    float alpha;
    float beta;
public:
LuzDireccional(Tupla2f direccion,GLenum id,Tupla4f colorAmbiente,Tupla4f colorDifuso, Tupla4f colorEspecular);
void variarAnguloAlpha(float incremento);
void variarAnguloBeta(float incremento);
};

class LuzPosicional : public Luz
{
public:
LuzPosicional(Tupla3f posicion,GLenum id,Tupla4f colorAmbiente,Tupla4f colorDifuso, Tupla4f colorEspecular);
void setPosicion(Tupla3f posicion);
void setcolorAmbiente(Tupla4f colorAmbiente);
void setcolorDifuso(Tupla4f colorDifuso);
void setcolorEspecular(Tupla4f colorEspecular);

};
