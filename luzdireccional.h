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