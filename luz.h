#include "aux.h"

class Luz
{
public:
void activar();
void desactivar();
void habilitar();
protected:
Tupla4f posicion;
GLenum id;
Tupla4f colorAmbiente;
Tupla4f colorDifuso;
Tupla4f colorEspecular;

};