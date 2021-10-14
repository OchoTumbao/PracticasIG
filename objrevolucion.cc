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
   // completar ......(práctica 2)
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   crearMalla(archivo,num_instancias);
    
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   for(int i=0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size();j++){
         v.push_back(RotaEjeY(perfil_original.at(j),(2*M_PI*i)/num_instancias));
      }
   }
   for(int i=0;i<num_instancias;i++){
      for(int j=0;j<perfil_original.size()-1;j++){
         int a=(num_instancias*i)+j;
         int b=num_instancias*((i+1)%perfil_original.size())+j;
         Tupla3i pt(a,b,b+1);
         Tupla3i st(a,b+1,a+1);
         f.push_back(pt);
         f.push_back(st);
      }
   }

}



