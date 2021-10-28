// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
class ObjRevolucion : public Malla3D
{
   public:
       ObjRevolucion();
       int eje=1;
       bool tapa_sup=true;
       bool tapa_inf=true;
       int ntapas=0;
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_supp=true, bool tapa_infp=true,int pivote=1) ;
   ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_supp=true, bool tapa_infp=true,int pivote=1) ;
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(int modo_dibujo=0,bool tapas=true);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(int modo_dibujo=0,bool tapas=true);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(int modo_diferido=1,int modo_dibujo=0,bool tapas=true) ;

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediatoAjedrez(bool tapas=true);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferidoAjedrez(bool tapas=true);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void drawAjedrez(int modo_diferido=1,bool tapas=true) ;


private:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias);

} ;




#endif
