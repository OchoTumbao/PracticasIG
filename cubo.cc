#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{

   // inicializar la tabla de vértices

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   //Base centrada en el origen
   Tupla3f va(-lado/2,0,-lado/2); // abajo izquierda detras
   Tupla3f vb(lado/2,0,-lado/2); // abajo derecha detras
   Tupla3f vc(-lado/2,0,lado/2); // abajo izquierda delante
   Tupla3f vd(lado/2,0,lado/2); // abajo derecha delante
   Tupla3f ve(-lado/2,lado,-lado/2); // arriba izquierda detras
   Tupla3f vf(lado/2,lado,-lado/2); // arriba derecha detras
   Tupla3f vg(-lado/2,lado,lado/2);// arriba izquierda delante
   Tupla3f vh(lado/2,lado,lado/2); // arriba derecha delante
   v.push_back(va); //0
   v.push_back(vb); //1
   v.push_back(vc); //2
   v.push_back(vd); //3
   v.push_back(ve); //4
   v.push_back(vf); //5
   v.push_back(vg); //6
   v.push_back(vh); //7
   Tupla3i tabc(0,1,2);
   Tupla3i tbdc(1,3,2);
   Tupla3i tchg(2,7,6);
   Tupla3i tcdh(2,3,7);
   Tupla3i tdfh(3,5,7);
   Tupla3i tdbf(3,1,5);
   Tupla3i tfba(5,1,0);
   Tupla3i tfae(5,0,4);
   Tupla3i tgac(6,0,2);
   Tupla3i tgea(6,4,0);
   Tupla3i theg(7,4,6);
   Tupla3i thfe(7,5,4);
   f.push_back(tabc);
   f.push_back(tbdc);
   f.push_back(tchg);
   f.push_back(tcdh);
   f.push_back(tdfh);
   f.push_back(tdbf);
   f.push_back(tfba);
   f.push_back(tfae);
   f.push_back(tgac);
   f.push_back(tgea);
   f.push_back(theg);
   f.push_back(thfe);

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
   }


   


}

