#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"




// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************
Tupla3f RotaEjeY(Tupla3f punto, float radianes){
   float resx,resy,resz;
   resx=punto(0)*cos(radianes)+punto(2)*sin(radianes);
   resy=punto(1);
   resz=punto(0)*-sin(radianes)+punto(2)*cos(radianes);
   return Tupla3f(resx,resy,resz);
   


}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo,perfil_original);
   crearMalla(perfil_original,num_instancias);
    if(tapa_sup){
       Tupla3f polo_norte=v.at(num_instancias+1);
       int indice=num_instancias+1;
       printf("x:%f,y:%f,z:%f\n",polo_norte(0),polo_norte(1),polo_norte(2));
       if(polo_norte(0)!=0 || polo_norte(2)!=0){
          printf("Ojo\n");
          polo_norte=Tupla3f(0,polo_norte(1),0);
          printf("x:%f,y:%f,z:%f\n",polo_norte(0),polo_norte(1),polo_norte(2));
          v.push_back(polo_norte);
          indice=v.size()-1;
       }
       for(int i=0;i<num_instancias;i++){
          Tupla3i tr(indice,(int)(perfil_original.size()*i)-1,(int)(perfil_original.size()*(i+1))-1);
          f.push_back(tr);
       }

    }
    if(tapa_inf){
       Tupla3f polo_sur=v.at(num_instancias);
       int indice=num_instancias;
       printf("x:%f,y:%f,z:%f\n",polo_sur(0),polo_sur(1),polo_sur(2));
       if(polo_sur(0)!=0 || polo_sur(2)!=0){
          printf("Ojo\n");
          polo_sur=Tupla3f(0,polo_sur(1),0);
          printf("x:%f,y:%f,z:%f\n",polo_sur(0),polo_sur(1),polo_sur(2));
          v.push_back(polo_sur);
          indice=v.size()-1;
       }
       for(int i=0;i<num_instancias;i++){
          Tupla3i tr(indice,(int)(perfil_original.size()*i),(int)(perfil_original.size()*(i-1)));
          f.push_back(tr);
       }

    }
   // completar ......(práctica 2)
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   crearMalla(archivo,num_instancias);
    if(tapa_sup){
       Tupla3f polo_norte=v.at(num_instancias+1);
       int indice=num_instancias+1;
       printf("x:%f,y:%f,z:%f\n",polo_norte(0),polo_norte(1),polo_norte(2));
       if(polo_norte(0)!=0 || polo_norte(2)!=0){
          printf("Ojo\n");
          polo_norte=Tupla3f(0,polo_norte(1),polo_norte(0));
          v.push_back(polo_norte);
          indice=v.size()-1;
       }
       for(int i=0;i<num_instancias;i++){
          Tupla3i tr(indice,(int)(archivo.size()*i)-1,(int)(archivo.size()*(i+1))-1);
          f.push_back(tr);
       }

    }
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   int M=perfil_original.size();
   int N=num_instancias;
   for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
         v.push_back(RotaEjeY(perfil_original.at(j),(2*M_PI*i)/num_instancias));
      }
   }
   for(int i=0;i<N;i++){
      for(int j=0;j<M-1;j++){
         int a=(M*i)+j;
         int b=M*((i+1)%N)+j;
         Tupla3i pt(a,b,b+1);
         Tupla3i st(a,b+1,a+1);
         f.push_back(pt);
         f.push_back(st);
      }
   }

}



