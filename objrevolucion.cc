#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <cmath>




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

Tupla3f RotaEjeX(Tupla3f punto, float radianes){
   float resx,resy,resz;
   resx=punto(0);
   resy=punto(1)*cos(radianes)+punto(2)*-sin(radianes);
   resz=punto(1)*sin(radianes)+punto(2)*cos(radianes);
   return Tupla3f(resx,resy,resz);
}

Tupla3f RotaEjeZ(Tupla3f punto, float radianes){
   float resx,resy,resz;
   resx=punto(0)*cos(radianes)+punto(1)*-sin(radianes);
   resy=punto(0)*sin(radianes)+punto(1)*cos(radianes);
   resz=punto(2);
   return Tupla3f(resx,resy,resz);
}

bool compare_float(float a,float b){

   return fabs(a-b) < 0.01f;
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_supp, bool tapa_infp,int pivote) {
   eje=pivote;
   tapa_sup=tapa_supp;
   tapa_inf=tapa_infp;
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo,perfil_original);

   crearMalla(perfil_original,num_instancias);
    
   rellenar_colores();
   // completar ......(práctica 2)
}


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_supp, bool tapa_infp,int pivote) {
   eje=pivote;
   tapa_sup=tapa_supp;
   tapa_inf=tapa_infp;
   crearMalla(perfil_original,num_instancias);
   rellenar_colores();
   // completar ......(práctica 2)
}



 void ObjRevolucion::actualizatapa(int tapa){
   if(tapa==0){
      if(tapa_sup==true){        
         f.erase(tapa_supit,tapa_supit+caras_tapa_sup.size());
         tapa_sup=false;
      } else{
            f.insert(tapa_supit,caras_tapa_sup.cbegin(),caras_tapa_sup.cend());
            tapa_sup=true;
      }
   } else{
      if(tapa_inf=true){
         f.erase(tapa_infit,f.cend());
         tapa_inf=false;
         tapa_infit=f.cend();
      } else{
         f.insert(tapa_infit,caras_tapa_inf.cbegin(),caras_tapa_inf.cend());
         tapa_inf=true;
         tapa_infit=f.cend()-caras_tapa_inf.size();
      }
   }
}


    

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
   int M=perfil_original.size();
   int N=num_instancias;
   Tupla3f polo_norte;
   Tupla3f polo_sur;

   switch (eje) {
   case 0:
   // Homogeneizamos perfil para que sea ascendente
    if(perfil_original.at(M-1)(0)<perfil_original.at(0)(0)){
       std::vector<Tupla3f> temp;
       for(int i=M-1;i>=0;i--){
          temp.push_back(perfil_original.at(i));
       }
       perfil_original=temp;
    }

   // Apartamos tapas
      if(compare_float(perfil_original.at(M-1)(2),0.0)){
      polo_norte=perfil_original.at(M-1);
      perfil_original.erase(perfil_original.cend()-1);
      } else{
         polo_norte=Tupla3f(perfil_original.at(M-1)(0),0.0,0.0);
      }
      if(compare_float(perfil_original.at(0)(2),0.0)){
      polo_sur=perfil_original.at(0);
      perfil_original.erase(perfil_original.cbegin());
      } else{
         polo_sur=Tupla3f(perfil_original.at(0)(0),0.0,0.0);
      }
   // Añadimos vertices
   M=perfil_original.size();
      for(int i=0;i<N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEjeX(perfil_original.at(j),(2*M_PI*i)/num_instancias));
         }
      }
   break;
   case 1:
    // Homogeneizamos perfil para que sea ascendente
    if(perfil_original.at(M-1)(1)<perfil_original.at(0)(1)){
       std::vector<Tupla3f> temp;
       for(int i=M-1;i>=0;i--){
          temp.push_back(perfil_original.at(i));
       }
       perfil_original=temp;
    }


   // Apartamos tapas
      if(compare_float(perfil_original.at(M-1)(0),0.0)){
      polo_norte=perfil_original.at(M-1);
      perfil_original.erase(perfil_original.cend()-1);
      } else{
         polo_norte=Tupla3f(0.0,perfil_original.at(M-1)(1),0.0);
      }

      if(compare_float(perfil_original.at(0)(0),0.0)){
      polo_sur=perfil_original.at(0);
      perfil_original.erase(perfil_original.cbegin());
      } else{
         polo_sur=Tupla3f(0.0,perfil_original.at(0)(1),0.0);
      }
   // Añadimos vertices
   M=perfil_original.size();
      for(int i=0;i<N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEjeY(perfil_original.at(j),(2*M_PI*i)/num_instancias));
         }
      }
   break;
   case 2:
    // Homogeneizamos perfil para que sea ascendente
    if(perfil_original.at(M-1)(2)<perfil_original.at(0)(2)){
       std::vector<Tupla3f> temp;
       for(int i=M-1;i>=0;i--){
          temp.push_back(perfil_original.at(i));
       }
       perfil_original=temp;
    }

   // Apartamos tapas
      if(compare_float(perfil_original.at(M-1)(1),0.0)){
      polo_norte=perfil_original.at(M-1);
      perfil_original.erase(perfil_original.cend()-1);
      } else{
         polo_norte=Tupla3f(0.0,0.0,perfil_original.at(M-1)(2));
      }
      if(compare_float(perfil_original.at(0)(1),0.0)){
      polo_sur=perfil_original.at(0);
      perfil_original.erase(perfil_original.cbegin());
      } else{
         polo_sur=Tupla3f(0.0,0.0,perfil_original.at(0)(2));
      }
   // Añadimos vertices
   M=perfil_original.size();
      for(int i=0;i<N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEjeZ(perfil_original.at(j),(2*M_PI*i)/num_instancias));
         }
      }
   break;
   }

   for(int i=0;i<N;i++){
      for(int j=0;j<M-1;j++){
         int a=(M*i)+j;
         int b=M*((i+1)%N)+j;
         Tupla3i pt(a,b,b+1);
         Tupla3i st(a,b+1,a+1);
         f.push_back(pt);
         f.push_back(st);
         caras_notapas+=2;
      }
   }

if(tapa_sup){
       
      v.push_back(polo_norte);
      int indice=v.size()-1;

       for(int i=0;i<N-1;i++){
          int last_instance=(M*(i+1)-1);
          int next_instance=(M*(i+2)-1);
          Tupla3i tr(indice,last_instance,next_instance);
          f.push_back(tr);
          caras_tapa_sup.push_back(tr);
       }
       Tupla3i tr(indice,M*N-1,M-1);
       f.push_back(tr);
       caras_tapa_sup.push_back(tr);

    }
    if(tapa_inf){
       v.push_back(polo_sur);
       int indice=v.size()-1;
       for(int i=0;i<N-1;i++){
          int last_instance=(M*i);
          int next_instance=(M*(i+1));
          Tupla3i tr(indice,next_instance,last_instance);
          f.push_back(tr);
          caras_tapa_inf.push_back(tr);
       }
       Tupla3i tr(indice,0,M*(N-1));
       f.push_back(tr);
       caras_tapa_inf.push_back(tr);

    }

}





