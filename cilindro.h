#include "objrevolucion.h"

class Cilindro : public ObjRevolucion
{
public :
Cilindro ( const int num_vert_perfil ,const int num_instancias_perf ,const float altura ,const float radio, int pivote, bool tapa_sup,bool tapa_inf) ;
Cilindro ( const int num_vert_perfil ,const int num_instancias_perf ,std::string texturas,const float altura ,const float radio, int pivote, bool tapa_sup,bool tapa_inf) ;
protected :
std::vector<Tupla3f> getPerfilOriginal(const int num_vert_perfil,const float altura,const float radio,int pivote);
} ;