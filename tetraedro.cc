#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro(float lado)
{

   // inicializar la tabla de vértices

    
   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)
   // 4 vertices en el origen
   Tupla3f va(0,0,-lado/2); // centro izquierda detras
   Tupla3f vb(-lado/2,0,lado/2); // centro derecha detras
   Tupla3f vc(lado/2,0,lado/2); // centro izquierda delante
   Tupla3f vd(0,lado,0); // arriba

   // Metemos los vertices en la tabla de vertices
   v.push_back(va); //0
   v.push_back(vb); //1
   v.push_back(vc); //2
   v.push_back(vd); //3


   Tupla3i tbac(1,0,2);
   Tupla3i tdab(3,0,1);
   Tupla3i tdbc(3,1,2);
   Tupla3i tdca(3,2,0);

   f.push_back(tbac);
   f.push_back(tdab);
   f.push_back(tdbc);
   f.push_back(tdca);


rellenar_colores();
calcular_normales();

}

