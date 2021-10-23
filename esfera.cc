#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil ,const int num_instancias_perf,const float radio,int pivote,bool tapa_sup,bool tapa_inf) : ObjRevolucion(getPerfilOriginal(num_vert_perfil,radio,pivote),num_instancias_perf,tapa_sup,tapa_inf,pivote){
    // Construimos el perfil

}

std::vector<Tupla3f> Esfera::getPerfilOriginal(const int num_vert_perfil,const float radio,int pivote){
    std::vector<Tupla3f> perfil_original;
    float radiandivision=M_PI/(num_vert_perfil);
    float startpoint=-(M_PI/2);
    if(pivote==1){

    for(int i=0;i<num_vert_perfil;i++){
        
        perfil_original.push_back(Tupla3f(cos(startpoint+radiandivision*i)*radio,sin(startpoint+radiandivision*i)*radio,0));
        
    }
    } else if(pivote<1){
    for(int i=0;i<num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f(sin(startpoint+radiandivision*i)*radio,0.,cos(startpoint+radiandivision*i)*radio));
    }
    } else{
    for(int i=0;i<num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f(0,cos(startpoint+radiandivision*i)*radio,sin(startpoint+radiandivision*i)*radio));
    }
    }
    
    return perfil_original;
}