#include "objrevolucion.h"

class Semiesfera : public ObjRevolucion
{
public :
Semiesfera( const int num_vert_perfil ,const int num_instancias_perf ,const float radio, int pivote,bool tapa_sup,bool tapa_inf ) ;
protected :
std::vector<Tupla3f> getPerfilOriginal(const int num_vert_perfil,const float radio,int pivote);
} ;