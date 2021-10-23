#include "cono.h"

Cono::Cono(const int num_vert_perfil ,const int num_instancias_perf ,const float altura ,const float radio,int pivote,bool tapa_sup,bool tapa_inf) : ObjRevolucion(getPerfilOriginal(num_vert_perfil,altura,radio,pivote),num_instancias_perf,tapa_sup,tapa_inf,pivote){
    // Construimos el perfil

}

std::vector<Tupla3f> Cono::getPerfilOriginal(const int num_vert_perfil,const float altura,const float radio,int pivote){
    std::vector<Tupla3f> perfil_original;
    float divisionesa=altura/num_vert_perfil;
    float divisionesr=radio/num_vert_perfil;
    int j=num_vert_perfil;
    if(pivote==1){

    for(int i=0;i<num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f(divisionesr*j,divisionesa*i,0));
        j--;
    }
    } else if(pivote<1){
    for(int i=0;i<num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f(divisionesa*i,0,divisionesr*j));
        j--;        
    }} else{
    for(int i=0;i<num_vert_perfil;i++){
        perfil_original.push_back(Tupla3f(0,divisionesr*j,divisionesa*i)); 
        j--;       
    }
    }
    
    return perfil_original;
}