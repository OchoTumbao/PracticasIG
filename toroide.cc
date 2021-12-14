#include "toroide.h"
Toroide::Toroide(const int num_vert_perfil ,const int num_instancias_perf,const float radioint,const float radioext,bool tapa_sup,bool tapa_inf) : ObjRevolucion(getPerfilOriginal(num_vert_perfil,radioint,radioext),num_instancias_perf,tapa_sup,tapa_inf,1){
    // Construimos el perfil

}

std::vector<Tupla3f> Toroide::getPerfilOriginal(const int num_vert_perfil,const float radioint,const float radioext){
    std::vector<Tupla3f> perfil_original;
    float radiandivision=(2*M_PI)/(num_vert_perfil);
    for(int i=0;i<=num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f((cos(radiandivision*i)*radioint)+radioext,(sin(radiandivision*i)*radioint),0));
    }
    return perfil_original;
}
