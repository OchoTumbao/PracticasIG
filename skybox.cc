#include "skybox.h"

Skybox::Skybox(std::string archivo,float lado){
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

   posicionsol=new Tupla3f(0,0,0);
   posicionluna=new Tupla3f(0,0,0);
   colAmbSol=new Tupla4f(1.0,Gsol,Bsol,1);
   colDifSol=new Tupla4f(1.0,Gsol,Gsol,1);
   colEspSol=new Tupla4f(1.0,Gsol,Bsol,1);
   colAmbLuna=new Tupla4f(0,0,0,1);
   colDifLuna=new Tupla4f(0,0,0,1);
   colEspLuna=new Tupla4f(0,0,0,1);
   this->lado=lado;

   sol=new LuzPosicional(*posicionsol,GL_LIGHT2,*colAmbSol,*colDifSol,*colEspSol);
   luna=new LuzPosicional(*posicionluna,GL_LIGHT3,*colAmbLuna,*colDifLuna,*colEspLuna);

   sol->habilitar();
   luna->habilitar();


   this->setTextura(archivo);

   v.push_back(va); //0
   v.push_back(vb); //1
   v.push_back(vc); //2
   v.push_back(vd); //3
   v.push_back(ve); //4
   v.push_back(vf); //5
   v.push_back(vg); //6
   v.push_back(vh); //7

   f.push_back({0,2,1});
   f.push_back({1,2,3});
   f.push_back({2,6,7});
   f.push_back({2,7,3});
   f.push_back({3,7,5});
   f.push_back({3,5,1});
   f.push_back({5,0,1});
   f.push_back({5,4,0});
   f.push_back({6,2,0});
   f.push_back({6,0,4});
   f.push_back({7,6,4});
   f.push_back({7,4,5});

   calcular_normales();
   rellenar_colores();

   tc.push_back({-lado/2,-lado/8,-lado/2});
   tc.push_back({lado/2,-lado/8,-lado/2});
   tc.push_back({-lado/2,-lado/8,lado/2});
   tc.push_back({lado/2,-lado/8,lado/2});
   tc.push_back({-lado/2,lado,-lado/2});
   tc.push_back({lado/2,lado,-lado/2});
   tc.push_back({-lado/2,lado,lado/2});
   tc.push_back({lado/2,lado,lado/2});
   
}


Skybox::Skybox(std::string archivo[6],float lado){
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

    this->setTextura(archivo);

   v.push_back(va); //0
   v.push_back(vb); //1
   v.push_back(vc); //2
   v.push_back(vd); //3
   v.push_back(ve); //4
   v.push_back(vf); //5
   v.push_back(vg); //6
   v.push_back(vh); //7

   f.push_back({0,2,1});
   f.push_back({1,2,3});
   f.push_back({2,6,7});
   f.push_back({2,7,3});
   f.push_back({3,7,5});
   f.push_back({3,5,1});
   f.push_back({5,0,1});
   f.push_back({5,4,0});
   f.push_back({6,2,0});
   f.push_back({6,0,4});
   f.push_back({7,6,4});
   f.push_back({7,4,5});

   calcular_normales();
   rellenar_colores();

   tc.push_back({-lado/2,-lado/2,-lado/2});
   tc.push_back({lado/2,-lado/2,-lado/2});
   tc.push_back({-lado/2,-lado/2,lado/2});
   tc.push_back({lado/2,-lado/2,lado/2});
   tc.push_back({-lado/2,lado/2,-lado/2});
   tc.push_back({lado/2,lado/2,-lado/2});
   tc.push_back({-lado/2,lado/2,lado/2});
   tc.push_back({lado/2,lado/2,lado/2});
   
}


void Skybox::setTextura(std::string archivo){
    t=new Cubemap(archivo);
}

void Skybox::setTextura(std::string archivo[6]){
    t=new Cubemap(archivo);
}

void Skybox::draw_ModoInmediato(int modo_dibujo)
{
  // visualizar la malla usando glDrawElements,
  // Inicializar Array Vertices
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     glTexCoordPointer(3, GL_FLOAT, 0, &tc[0]);
     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   // Indicamos buffer de vertices
   glVertexPointer(3,GL_FLOAT,0,&v[0]);
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
   glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,&f[0]);
   // deshabilitamos el array de vertices
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Skybox::draw_ModoDiferido(int modo_dibujo)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)

   

   if(id_vbov==0){
      id_vbov=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&v[0]);
   }
   if(id_vbof==0){
      id_vbof=CrearVBO(GL_ELEMENT_ARRAY_BUFFER,3*f.size()*sizeof(int),&f[0]);
   }
   if(id_vbovn==0){
      id_vbovn=CrearVBO(GL_ARRAY_BUFFER,3*vn.size()*sizeof(float),&vn[0]);
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
      if(id_vboct==0){
         id_vboct=CrearVBO(GL_ARRAY_BUFFER,3*tc.size()*sizeof(float),&tc[0]);
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
   glNormalPointer(GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER,id_vboct);
   glTexCoordPointer(3, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbof);
   glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);



}

void Skybox::draw(int modo_diferido,int modo_dibujo)
{
   // completar .....(práctica 1)
   m.aplicar();
    this->t->activar();
   if(modo_diferido==0){
      draw_ModoInmediato(modo_dibujo);
   } else{
      draw_ModoDiferido(modo_dibujo);
   }

   if(glIsEnabled(GL_LIGHTING)){
      glPushMatrix();
      glRotatef(rotacionluces,0,0,1);
      glPushMatrix();
      glTranslatef(-(this->lado/2-this->lado/20),0,0);
      sol->activar();
      glPopMatrix();
      glPushMatrix();
      glTranslatef(this->lado/2-this->lado/20,0,0);
      luna->activar();
      glPopMatrix();
      glPopMatrix();


   }

   glDisable(GL_TEXTURE_CUBE_MAP);


}


void Skybox::animarLuces(float porcentaje){
   rotacionluces=fmod(rotacionluces+0.5*porcentaje,360);
   if(rotacionluces<=90){
      if(Gsol<1){
         Gsol+=0.008*porcentaje;
      } if (Bsol<0.8){
         Bsol+=0.003*porcentaje;
      }
   }
   else if(rotacionluces<=180){
      if(Gsol>0.24){
         Gsol-=0.008*porcentaje;
      } if (Bsol>0.24){
         Bsol-=0.003*porcentaje;
      }
   } else if(rotacionluces<=270){
      if(Gluna<0.23){
         Gluna+=0.008*porcentaje;
      } if (Bluna<0.7){
         Bluna+=0.003*porcentaje;
      }
      if(Rluna<0.08){
         Rluna+=0.001*porcentaje;
      }
      if(Gsol>0){
         Gsol-=0.008*porcentaje;
      }
      if(Bsol>0){
         Bsol-=0.003*porcentaje;
      } 
      if(Rsol>0){
         Rsol-=0.008*porcentaje;
      }
   } else if(rotacionluces<=360){
      if(Gluna>0){
         Gluna-=0.008*porcentaje;
      } if (Bluna>0){
         Bluna-=0.003*porcentaje;
      }
      if(Rluna>0){
         Rluna-=0.001*porcentaje;
      }
      if(Rsol<1){
         Rsol+=0.008*porcentaje;
      } if (Gsol<0.24){
         Gsol+=0.0008*porcentaje;
      } if (Bsol<0.24){
         Bsol+=0.008*porcentaje;
      }
   }
/*         printf("%f %f %f\n",Rsol,Gsol,Bsol);
         printf("%f %f %f\n",Rluna,Gluna,Bluna);
         printf("%f\n",rotacionluces);*/
         colAmbSol=new Tupla4f(Rsol,Gsol,Bsol,1);
         colDifSol=new Tupla4f(Rsol,Gsol,Bsol,1);
         colEspSol=new Tupla4f(Rsol,Gsol,Bsol,1);
         colDifLuna=new Tupla4f(Rluna,Gluna,Bluna,1);
         colEspLuna=new Tupla4f(Rluna,Gluna,Bluna,1);
         colAmbLuna=new Tupla4f(Rluna,Gluna,Bluna,1);
         sol->setcolorAmbiente(*colAmbSol);
         sol->setcolorDifuso(*colDifSol);
         sol->setcolorEspecular(*colEspSol);
         luna->setcolorAmbiente(*colAmbLuna);
         luna->setcolorDifuso(*colDifLuna);
         luna->setcolorEspecular(*colEspLuna);
}

void Skybox::habilitarLuzLuna(){
   luna->habilitar();
}

void Skybox::habilitarLuzSol(){
   sol->habilitar();
}