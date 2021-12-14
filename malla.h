// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"
// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(int modo_dibujo=0);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(int modo_dibujo=0);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(int modo_diferido=1,int modo_dibujo=0) ;

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediatoAjedrez();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferidoAjedrez();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void drawAjedrez(int modo_diferido=1) ;

   void setMaterial(Material m);

   void setTextura(std::string archivo);
   Textura *t=nullptr;

   

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   void rellenar_colores();
   GLuint CrearVBO(GLuint tipo_vbo , GLuint tamanio_bytes ,
GLvoid * puntero_ram);
   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> faces_fh_chess;
   std::vector<Tupla3i> faces_sh_chess;
   std::vector<Tupla3f> color_fill ;
   std::vector<Tupla3f> color_wire;
   std::vector<Tupla3f> color_points;
   std::vector<Tupla3f> color_chess1;
   std::vector<Tupla3f> color_chess2;
   std::vector<Tupla3f> vn;
   std::vector<Tupla2f> ct;
   Tupla3f c_fill=Tupla3f(1.0,0.0,1.0);
   Tupla3f c_wire=Tupla3f(0.0,1.0,1.0);
   Tupla3f c_points=Tupla3f(0.0,0.0,0.0);
   Tupla3f c_chess1=Tupla3f(0.0,1.0,0.0);
   Tupla3f c_chess2=Tupla3f(1.0,0.0,0.0);
   Tupla4f defaultmaterial=Tupla4f(0.0,0.0,0.0,1.0);
   GLuint id_vbov=0;
   GLuint id_vbof=0;
   GLuint id_vbocw=0;
   GLuint id_vbocf=0;
   GLuint id_vbocp=0;
   GLuint id_vboaf1=0;
   GLuint id_vboaf2=0;
   GLuint id_vboac1=0;
   GLuint id_vboac2=0;
   GLuint id_vbovn=0;
   GLuint id_vboct=0;
   Material m=Material(defaultmaterial,defaultmaterial,defaultmaterial,1.0);


   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
