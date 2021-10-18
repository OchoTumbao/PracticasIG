#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil ,const int num_instancias_perf ,const float altura ,const float radio,int pivote) : ObjRevolucion(getPerfilOriginal(num_vert_perfil,num_instancias_perf,altura,radio),num_instancias_perf,true,true,pivote){
    // Construimos el perfil


    
    printf("Ya he construido el objeto, tengo: %d puntos y %d caras\n", v.size(),f.size());



}

std::vector<Tupla3f> Cilindro::getPerfilOriginal(const int num_vert_perfil,const float altura,const float radio){
        float divisiones=altura/num_vert_perfil;
    std::vector<Tupla3f> perfil_original;
    for(int i=0;i<num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f(radio,divisiones*i,0));
    }
}
