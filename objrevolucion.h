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
   ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_supp=true, bool tapa_infp=true,int pivote=1) ;
   ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias, bool tapa_supp=true, bool tapa_infp=true,int pivote=1) ;
   void actualizatapa(int tapa);


private:
    int caras_notapas=0;
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias);
    std::vector<Tupla3i> caras_tapa_sup;
    std::vector<Tupla3i> caras_tapa_inf;
    std::vector<Tupla3i>::const_iterator tapa_infit=f.cend()-(caras_tapa_inf.size()+caras_tapa_sup.size());
    std::vector<Tupla3i>::const_iterator tapa_supit=f.cend()-caras_tapa_inf.size();

} ;




#endif
