#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );
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


