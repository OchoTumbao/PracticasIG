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

Tupla3f RotaEj0(Tupla3f punto, float radianes){
   float resx,resy,resz;
   resx=punto(0);
   resy=punto(1)*cos(radianes)+punto(2)*-sin(radianes);
   resz=punto(1)*sin(radianes)+punto(2)*cos(radianes);
   return Tupla3f(resx,resy,resz);
}

Tupla3f RotaEj2(Tupla3f punto, float radianes){
   float resx,resy,resz;
   resx=punto(0)*cos(radianes)+punto(1)*-sin(radianes);
   resy=punto(0)*sin(radianes)+punto(1)*cos(radianes);
   resz=punto(2);
   return Tupla3f(resx,resy,resz);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf,int pivote) {
   eje=pivote;
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo,perfil_original);

   crearMalla(perfil_original,num_instancias,tapa_sup,tapa_inf);
    
       for(int i=0;i<v.size();i++){
      color_fill.push_back(c_fill);
      color_wire.push_back(c_wire);
      color_points.push_back(c_points);
      color_chess1.push_back(c_chess1);
      color_chess2.push_back(c_chess2);
   }
   for(int i=0;i<f.size();i++){
      if(i%2==0){
         faces_fh_chess.push_back(f.at(i));
      }else{
         faces_sh_chess.push_back(f.at(i));
      }
   // completar ......(práctica 2)
}
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_sup, bool tapa_inf,int pivote) {
   eje=pivote;
   crearMalla(perfil_original,num_instancias,tapa_sup,tapa_inf);
   for(int i=0;i<v.size();i++){
      color_fill.push_back(c_fill);
      color_wire.push_back(c_wire);
      color_points.push_back(c_points);
      color_chess1.push_back(c_chess1);
      color_chess2.push_back(c_chess2);
   }
   for(int i=0;i<f.size();i++){
      if(i%2==0){
         faces_fh_chess.push_back(f.at(i));
      }else{
         faces_sh_chess.push_back(f.at(i));
      }
   // completar ......(práctica 2)
}
   printf("Ya he construido la malla, tengo: %d puntos y %d caras\n", v.size(),f.size());
   printf("Objeto bien creado\n");

}
    

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias,bool tapa_sup,bool tapa_inf) {
   int M=perfil_original.size();
   int N=num_instancias;
   printf ("M: %d, F: %d\n",M,N);
   switch (eje)
   {
   case 0:
      for(int i=0;i<N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEj0(perfil_original.at(j),(2*M_PI*i)/num_instancias));
         }
      }
   break;
   case 1:
      for(int i=0;i<N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEjeY(perfil_original.at(j),(2*M_PI*i)/num_instancias));
            printf("i: %d,j: %d [%f,%f,%f]\n",i,j,v.at(v.size()-1)(0),v.at(v.size()-1)(1),v.at(v.size()-1)(2));
         }
      }
   break;
   case 2:
      for(int i=0;i<N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEj2(perfil_original.at(j),(2*M_PI*i)/num_instancias));
         }
      }
   break;
   default:
      for(int i=0;i<N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEjeY(perfil_original.at(j),(2*M_PI*i)/num_instancias));
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
      }
   }

if(tapa_sup){
       Tupla3f polo_norte=v.at(num_instancias+1);
       int indice=num_instancias+1;
       switch (eje)
       {
       case 0:
         if(polo_norte(1)!=0 || polo_norte(2)!=0){
            polo_norte=Tupla3f(polo_norte(0),0,0);
            v.push_back(polo_norte);
            indice=v.size()-1;
         }
         break;
       case 1:
         if(polo_norte(0)!=0 || polo_norte(2)!=0){
            polo_norte=Tupla3f(0,polo_norte(1),0);
            v.push_back(polo_norte);
            indice=v.size()-1;
         }
         break;
       case 2:
         if(polo_norte(0)!=0 || polo_norte(1)!=0){
            polo_norte=Tupla3f(0,0,polo_norte(2));
            v.push_back(polo_norte);
            indice=v.size()-1;
         }
         break;
       }
       printf("x:%f,y:%f,z:%f\n",polo_norte(0),polo_norte(1),polo_norte(2));
       
       for(int i=0;i<num_instancias;i++){
          Tupla3i tr(indice,(int)(perfil_original.size()*i)-1,(int)(perfil_original.size()*(i+1))-1);
          f.push_back(tr);
       }

    }
    if(tapa_inf){
       Tupla3f polo_sur=v.at(num_instancias);
       int indice=num_instancias;
       switch (eje)
       {
       case 0:
         if(polo_sur(1)!=0 || polo_sur(2)!=0){
            polo_sur=Tupla3f(polo_sur(0),0,0);
            v.push_back(polo_sur);
            indice=v.size()-1;
         }
         break;
       case 1:
         if(polo_sur(0)!=0 || polo_sur(2)!=0){
            polo_sur=Tupla3f(0,polo_sur(1),0);
            v.push_back(polo_sur);
            indice=v.size()-1;
         }
         break;
       case 2:
         if(polo_sur(0)!=0 || polo_sur(1)!=0){
            polo_sur=Tupla3f(0,0,polo_sur(2));
            v.push_back(polo_sur);
            indice=v.size()-1;
         }
         break;
       }
       for(int i=0;i<num_instancias;i++){
          Tupla3i tr(indice,(int)(perfil_original.size()*i),(int)(perfil_original.size()*(i-1)));
          f.push_back(tr);
       }

    }

}





