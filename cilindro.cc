#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil ,const int num_instancias_perf ,const float altura ,const float radio,int pivote,bool tapa_sup,bool tapa_inf) : ObjRevolucion(getPerfilOriginal(num_vert_perfil,altura,radio,pivote),num_instancias_perf,tapa_sup,tapa_inf,pivote){
    // Construimos el perfil

}

Cilindro::Cilindro(const int num_vert_perfil ,const int num_instancias_perf ,std::string texturas,const float altura ,const float radio,int pivote,bool tapa_sup,bool tapa_inf) : ObjRevolucion(getPerfilOriginal(num_vert_perfil,altura,radio,pivote),num_instancias_perf,texturas,tapa_sup,tapa_inf,pivote){
    // Construimos el perfil

}

std::vector<Tupla3f> Cilindro::getPerfilOriginal(const int num_vert_perfil,const float altura,const float radio,int pivote){
    std::vector<Tupla3f> perfil_original;
    printf("aqui llego\n");
    if(pivote==1){
        float divisiones=altura/num_vert_perfil;

    for(int i=0;i<num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f(radio,divisiones*i,0));
    }
    } else if(pivote<1){
        float divisiones=altura/num_vert_perfil;
    for(int i=0;i<num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f(divisiones*i,0,radio));        
    }} else{
        float divisiones=altura/num_vert_perfil;
    for(int i=0;i<num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f(0,radio,divisiones*i));        
    }
    }
    
    return perfil_original;
}
