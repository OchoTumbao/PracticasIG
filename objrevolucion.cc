#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include "func_aux.hpp"




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



// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias,const std::string & texturas, bool tapa_supp, bool tapa_infp,int pivote) {
   eje=pivote;
   tapa_sup=tapa_supp;
   tapa_inf=tapa_infp;
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo,perfil_original);
   M=perfil_original.size();
   N=num_instancias;

   crearMalla(perfil_original,num_instancias);
   rellenar_colores();
   calcular_normales();
   calcularCoordTextura();
   setTextura(texturas);

   // completar ......(práctica 2)
}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_supp, bool tapa_infp,int pivote) {
   eje=pivote;
   tapa_sup=tapa_supp;
   tapa_inf=tapa_infp;
   std::vector<Tupla3f> perfil_original;
   ply::read_vertices(archivo,perfil_original);
   M=perfil_original.size();
   N=num_instancias;

   crearMalla(perfil_original,num_instancias);
   rellenar_colores();
   calcular_normales();
   // completar ......(práctica 2)
}



// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_supp, bool tapa_infp,int pivote) {
   eje=pivote;
   tapa_sup=tapa_supp;
   tapa_inf=tapa_infp;
   M=perfil_original.size();
   N=num_instancias;
   crearMalla(perfil_original,num_instancias);
   rellenar_colores();
   calcular_normales();
   
   // completar ......(práctica 2)
}

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias,const std::string & texturas, bool tapa_supp, bool tapa_infp,int pivote) {
   eje=pivote;
   tapa_sup=tapa_supp;
   tapa_inf=tapa_infp;
   M=perfil_original.size();
   N=num_instancias;
   crearMalla(perfil_original,num_instancias);
   rellenar_colores();
   calcular_normales();
   calcularCoordTextura();
   setTextura(texturas);

   
   // completar ......(práctica 2)
}


void ObjRevolucion::calcularCoordTextura(){
   float Si;
   float Ti;
      for(int i=0;i<N;i++){
         Si=i/(float)(N);
         for(int j=0;j<M;j++)
         {  
            Ti=distancias_originales[j]/distancias_originales[M-1];
            //printf("Al punto %d de la rotación %d con coordenadas %f %f %f le asigno las coordenadas de textura %f %f\n",j,i,v.at(i*M+j)(0),v.at(i*M+j)(1),v.at(i*M+j)(2),Si,Ti);
            Tupla2f coord(Si,Ti);   
            ct.push_back(coord);
         }
      }
         Si = 1;
      for (int i = 0 ; i < M ; i++){
      Ti = distancias_originales[i]/distancias_originales[M-1];
            Tupla2f coord(Si,Ti);   
            ct.push_back(coord);
   }
}



    

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias) {
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
      if(compare_float(perfil_original.at(M-1)(2),0.0) && compare_float(perfil_original.at(M-1)(1),0.0)){
      polo_norte=perfil_original.at(M-1);
      perfil_original.erase(perfil_original.cend()-1);
      } else{
         polo_norte=Tupla3f(perfil_original.at(M-1)(0),0.0,0.0);
         //perfil_original.push_back(polo_norte);
      }
      if(compare_float(perfil_original.at(0)(2),0.0) && compare_float(perfil_original.at(0)(1),0.0)){
      polo_sur=perfil_original.at(0);
      perfil_original.erase(perfil_original.begin());
      } else{
         polo_sur=Tupla3f(perfil_original.at(0)(0),0.0,0.0);
         //(perfil_original.insert(perfil_original.begin(),polo_sur);
      }
   // Añadimos vertices
   M=perfil_original.size();

      for(int i=0;i<=N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEjeX(perfil_original.at(j),((2*M_PI)/N)*i));
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
       if(compare_float(perfil_original.at(M-1)(0),0.0) && compare_float(perfil_original.at(M-1)(2),0.0)){
      polo_norte=perfil_original.at(M-1);
      perfil_original.erase(perfil_original.cend()-1);
      } else{
         polo_norte=Tupla3f(0.0,perfil_original.at(M-1)(1),0.0);
         //perfil_original.push_back(polo_norte);
      }

      if(compare_float(perfil_original.at(0)(0),0.0) && compare_float(perfil_original.at(0)(2),0.0)){
      polo_sur=perfil_original.at(0);
      perfil_original.erase(perfil_original.cbegin());
      } else{

         polo_sur=Tupla3f(0.0,perfil_original.at(0)(1),0.0);
         //perfil_original.insert(perfil_original.begin(),polo_sur);
      }
   // Añadimos vertices
   M=perfil_original.size();
      for(int i=0;i<=N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEjeY(perfil_original.at(j),((2*M_PI)/N)*i));
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
      if(compare_float(perfil_original.at(M-1)(0),0.0) && compare_float(perfil_original.at(M-1)(1),0.0)){
      polo_norte=perfil_original.at(M-1);
      perfil_original.erase(perfil_original.cend()-1);
      } else{
         polo_norte=Tupla3f(0.0,0.0,perfil_original.at(M-1)(2));
      }
      if(compare_float(perfil_original.at(0)(0),0.0) && compare_float(perfil_original.at(0)(1),0.0)){
      polo_sur=perfil_original.at(0);
      perfil_original.erase(perfil_original.cbegin());
      } else{
         polo_sur=Tupla3f(0.0,0.0,perfil_original.at(0)(2));
      }
   // Añadimos vertices
   M=perfil_original.size();
      for(int i=0;i<=N;i++){
         for(int j=0;j<M;j++){
            v.push_back(RotaEjeZ(perfil_original.at(j),((2*M_PI)/N)*i));
         }
      }
   break;
   }

   // Calculamos distancias

   distancias_originales.push_back(0.0);
   for (int i = 1 ; i < perfil_original.size() ; i++){
      Tupla3f p = perfil_original[i] - perfil_original[i-1];
      distancias_originales.push_back(distancias_originales[i-1] + p.lengthSq());
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
      v.push_back(polo_norte);
      int indice=v.size()-1;

       for(int i=0;i<N-1;i++){
          int last_instance=(M*(i+1)-1);
          int next_instance=(M*(i+2)-1);
          Tupla3i trsup(indice,last_instance,next_instance);
          f.push_back(trsup);
          ntapas++;
       }
       Tupla3i trsup(indice,M*N-1,M-1);
          f.push_back(trsup);
          ntapas++;
   }
   if(tapa_inf){
       v.push_back(polo_sur);
       int indice=v.size()-1;
       for(int i=0;i<N-1;i++){
          int last_instance=(M*i);
          int next_instance=(M*(i+1));
          Tupla3i trinf(indice,next_instance,last_instance);
          f.push_back(trinf);
          ntapas++;
       }
       Tupla3i trinf(indice,0,M*(N-1));
          f.push_back(trinf);
          ntapas++;

   }




}



void ObjRevolucion::draw(int modo_diferido,int modo_dibujo,bool tapas){
      if (t != nullptr && !ct.empty()){
      t->activar();
      }
         m.aplicar();
      if(modo_diferido==0){
      draw_ModoInmediato(modo_dibujo,tapas);
   } else{
      draw_ModoDiferido(modo_dibujo,tapas);
   }
   glDisable(GL_TEXTURE_2D);



}

void ObjRevolucion::draw_ModoInmediato(int modo_dibujo,bool tapas){
  // visualizar la malla usando glDrawElements,
  // Inicializar Array Vertices
   glEnableClientState(GL_VERTEX_ARRAY);
   // Indicamos buffer de vertices
   glVertexPointer(3,GL_FLOAT,0,&v[0]);
   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT,0,&vn[0]);
   //Visualizamos en modo inmediato, parametros: tipo de primitiva, numero de indices tipo de los indices y direccion de los indices
     
      glEnableClientState(GL_COLOR_ARRAY);
      switch(modo_dibujo){
         case 0:
               glColorPointer(3,GL_FLOAT,0,&color_fill[0]);
         break;
         case 1:
               glColorPointer(3,GL_FLOAT,0,&color_wire[0]);
         break;
         case 2:
     
               glColorPointer(3,GL_FLOAT,0,&color_points[0]);
         break;
         default:
               glColorPointer(3,GL_FLOAT,0,&color_fill[0]);
         break;
      }
      if(!ct.empty()){

     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     glTexCoordPointer(2, GL_FLOAT, 0, &ct[0]);
   }
   if(tapas){
     glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,&f[0]);
   } else{
      
      glDrawElements(GL_TRIANGLES,(f.size()-ntapas)*3,GL_UNSIGNED_INT,&f[0]);
   }
      if(!ct.empty()){
     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     glTexCoordPointer(2, GL_FLOAT, 0, &ct[0]);
   }

   // deshabilitamos el array de vertices
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
}

   void ObjRevolucion::draw_ModoDiferido(int modo_dibujo,bool tapas){
   if(id_vbov==0){
      id_vbov=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&v[0]);
   }
   if(id_vbof==0){
      id_vbof=CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*f.size()*sizeof(int),&f[0]);
   }
      switch(modo_dibujo){
         case 0:
            if(id_vbocf==0){
               id_vbocf=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&color_fill[0]);
            }
         break;
         case 1:
            if(id_vbocw==0){
               id_vbocw=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&color_wire[0]);
            }
         break;
         case 2:
             if(id_vbocp==0){
               id_vbocp=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&color_points[0]);
            }
         break;
         default:
            if(id_vbocf==0){
               id_vbocf=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&color_fill[0]);
            }
         break;
      }
   if(id_vbovn==0){
      id_vbovn=CrearVBO(GL_ARRAY_BUFFER,3*vn.size()*sizeof(float),&vn[0]);
   }
   if (!ct.empty()){
      if(id_vboct==0){
         id_vboct=CrearVBO(GL_ARRAY_BUFFER,2*ct.size()*sizeof(float),&ct[0]);
      }
   }
      switch(modo_dibujo){
         case 0:
            glBindBuffer(GL_ARRAY_BUFFER,id_vbocf);
         break;
         case 1:
            glBindBuffer(GL_ARRAY_BUFFER,id_vbocw);
         break;
         case 2:
            glBindBuffer(GL_ARRAY_BUFFER,id_vbocp);
         break;
         default:
            glBindBuffer(GL_ARRAY_BUFFER,id_vbocf);
         break;
      }   
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3,GL_FLOAT,0,0);
      glBindBuffer(GL_ARRAY_BUFFER,0);

   glBindBuffer(GL_ARRAY_BUFFER,id_vbov);
   glVertexPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glBindBuffer(GL_ARRAY_BUFFER,id_vbovn);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbof);
   if(!ct.empty()){
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER,id_vboct);
   glTexCoordPointer(2, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   }
   if(tapas){
   glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,0);
   } else{
   glDrawElements(GL_TRIANGLES,(f.size()-ntapas)*3,GL_UNSIGNED_INT,0);  
   }
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   }

void ObjRevolucion::draw_ModoInmediatoAjedrez(bool tapas)
{
  // visualizar la malla usando glDrawElements,
  // Inicializar Array Vertices
   glEnableClientState(GL_VERTEX_ARRAY);
   // Indicamos buffer de vertices

   glVertexPointer(3,GL_FLOAT,0,&v[0]);
   glEnableClientState(GL_NORMAL_ARRAY);
   glNormalPointer(GL_FLOAT,0,&vn[0]);
   //Visualizamos en modo inmediato, parametros: tipo de primitiva, numero de indices tipo de los indices y direccion de los indices
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3,GL_FLOAT,0,&color_chess1[0]);

   if(tapas){
   glDrawElements(GL_TRIANGLES,faces_fh_chess.size()*3,GL_UNSIGNED_INT,&faces_fh_chess[0]);
   }else{
   glDrawElements(GL_TRIANGLES,(faces_fh_chess.size()-(ntapas/2))*3,GL_UNSIGNED_INT,&faces_fh_chess[0]);
   }
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3,GL_FLOAT,0,&color_chess2[0]);

   if(tapas){
   glDrawElements(GL_TRIANGLES,faces_fh_chess.size()*3,GL_UNSIGNED_INT,&faces_sh_chess[0]);
   }else{
   glDrawElements(GL_TRIANGLES,(faces_fh_chess.size()-(ntapas/2))*3,GL_UNSIGNED_INT,&faces_sh_chess[0]);
   }

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjRevolucion::draw_ModoDiferidoAjedrez(bool tapas)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....



   if(id_vbov==0){
      id_vbov=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&v[0]);
   }
   if(id_vbovn==0){
      id_vbovn=CrearVBO(GL_ARRAY_BUFFER,3*vn.size()*sizeof(float),&vn[0]);
   }
   if(id_vboaf1==0){
      id_vboaf1=CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*faces_fh_chess.size()*sizeof(int),&faces_fh_chess[0]);
   }
   if(id_vboaf2==0){
      id_vboaf2=CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*faces_sh_chess.size()*sizeof(int),&faces_sh_chess[0]);
   }
   if(id_vboac1==0){
      id_vboac1=CrearVBO(GL_ARRAY_BUFFER,3*color_chess1.size()*sizeof(float),&color_chess1[0]);
   }
   if(id_vboac2==0){
      id_vboac2=CrearVBO(GL_ARRAY_BUFFER,3*color_chess2.size()*sizeof(float),&color_chess2[0]);
   }





   ////
   glBindBuffer(GL_ARRAY_BUFFER,id_vbov);
   glVertexPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glBindBuffer(GL_ARRAY_BUFFER,id_vbovn);
   glNormalPointer(GL_FLOAT,0,0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   ////
   glEnableClientState(GL_COLOR_ARRAY);
   ///
   glBindBuffer(GL_ARRAY_BUFFER,id_vboac1);
   glColorPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   ///
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vboaf1);
   if(tapas){
   glDrawElements(GL_TRIANGLES,faces_fh_chess.size()*3,GL_UNSIGNED_INT,0);
   }else{
   glDrawElements(GL_TRIANGLES,(faces_fh_chess.size()-ntapas/2)*3,GL_UNSIGNED_INT,0);
   }
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   ///
   glBindBuffer(GL_ARRAY_BUFFER,id_vboac2);
   glColorPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   ///
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vboaf2);
   if(tapas){
   glDrawElements(GL_TRIANGLES,faces_fh_chess.size()*3,GL_UNSIGNED_INT,0);
   }else{
   glDrawElements(GL_TRIANGLES,(faces_fh_chess.size()-ntapas/2)*3,GL_UNSIGNED_INT,0);
   }
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   ///
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);


}

void ObjRevolucion::drawAjedrez(int modo_diferido,bool tapas){
      if(modo_diferido==0){
      draw_ModoInmediatoAjedrez(tapas);
   } else{
      draw_ModoDiferidoAjedrez(tapas);
   }
}


