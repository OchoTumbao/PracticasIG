#include "objrevolucion.h"

class Toroide : public ObjRevolucion
{
public :
Toroide( const int num_vert_perfil ,const int num_instancias_perf ,const float radioint,const float radioext,bool tapa_sup,bool tapa_inf ) ;
protected :
std::vector<Tupla3f> getPerfilOriginal(const int num_vert_perfil,const float radioint,const float radioext);
} ;