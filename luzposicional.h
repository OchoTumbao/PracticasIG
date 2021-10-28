#include "luz.h"

class LuzPosicional : protected Luz
{
public:
LuzPosicional(Tupla3f posicion,GLenum id,Tupla4f colorAmbiente,Tupla4f colorDifuso, Tupla4f colorEspecular);
};