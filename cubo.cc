#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado,bool skybox,bool textured)
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
   v.push_back(va); //0
   v.push_back(vb); //1
   v.push_back(vc); //2
   v.push_back(vd); //3
   v.push_back(ve); //4
   v.push_back(vf); //5
   v.push_back(vg); //6
   v.push_back(vh); //7
   if(!skybox){
   f.push_back({0,1,2});
   f.push_back({1,3,2});
   f.push_back({2,7,6});
   f.push_back({2,3,7});
   f.push_back({3,5,7});
   f.push_back({3,1,5});
   f.push_back({5,1,0});
   f.push_back({5,0,4});
   f.push_back({6,0,2});
   f.push_back({6,4,0});
   f.push_back({7,4,6});
   f.push_back({7,5,4});
   } else {

   }

   rellenar_colores();
   calcular_normales();


if(textured){

	ct.push_back({0.0f, 1.0f});
	ct.push_back({1.0f, 1.0f});
	ct.push_back({0.0f, 0.0f});
	ct.push_back({1.0f, 0.0f});
	ct.push_back({0.0f, 0.0f});
	ct.push_back({1.0f, 0.0f});
	ct.push_back({0.0f, 1.0f});
	ct.push_back({1.0f, 1.0f});

	ct.push_back({0.0f, 1.0f});
	ct.push_back({1.0f, 1.0f});
	ct.push_back({0.0f, 0.0f});
	ct.push_back({1.0f, 0.0f});
	ct.push_back({0.0f, 0.0f});
	ct.push_back({1.0f, 0.0f});
	ct.push_back({0.0f, 1.0f});
	ct.push_back({1.0f, 1.0f});

   
}

}

