#include "objrevolucion.h"

class Cilindro : public ObjRevolucion
{
public :
Cilindro ( const int num_vert_perfil ,const int num_instancias_perf ,const float altura ,const float radio, int pivote ) ;
protected :
std::vector<Tupla3f> getPerfilOriginal(const int num_vert_perfil,const float altura,const float radio,int pivote);
} ;