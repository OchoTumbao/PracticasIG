#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

GLuint CrearVBO ( GLuint tipo_vbo , GLuint tamanio_bytes ,
GLvoid * puntero_ram )
{
GLuint id_vbo ; // resultado: identificador de VBO
glGenBuffers ( 1 , & id_vbo ); // crear nuevo VBO, obtener identificador
glBindBuffer ( tipo_vbo , id_vbo ); // activar el VBO usando su identificador
// esta instrucción hace la transferencia de datos desde RAM hacia GPU
glBufferData ( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW );
glBindBuffer ( tipo_vbo , 0 ); // desactivación del VBO (activar 0)
return id_vbo ; // devolver el identificador resultado
}

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato(int modo_dibujo)
{
  // visualizar la malla usando glDrawElements,
  // Inicializar Array Vertices
   glEnableClientState(GL_VERTEX_ARRAY);
   // Indicamos buffer de vertices
   glVertexPointer(3,GL_FLOAT,0,&v[0]);
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
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(int modo_dibujo)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)

   

   if(id_vbov==0){
      id_vbov=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&v[0]);
      printf("Entro Aqui");
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
   glEnableClientState(GL_VERTEX_ARRAY);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbof);
   glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);


}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido





void Malla3D::draw(int modo_diferido,int modo_dibujo)
{
   glShadeModel(GL_SMOOTH);
   // completar .....(práctica 1)
   if(modo_diferido==0){
      draw_ModoInmediato(modo_dibujo);
   } else{
      draw_ModoDiferido(modo_dibujo);
   }


}

void Malla3D::draw_ModoInmediatoAjedrez()
{
  // visualizar la malla usando glDrawElements,
  // Inicializar Array Vertices
   glEnableClientState(GL_VERTEX_ARRAY);
   // Indicamos buffer de vertices

   glVertexPointer(3,GL_FLOAT,0,&v[0]);
   //Visualizamos en modo inmediato, parametros: tipo de primitiva, numero de indices tipo de los indices y direccion de los indices
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3,GL_FLOAT,0,&color_chess1[0]);
   glDrawElements(GL_TRIANGLES,3*faces_fh_chess.size(),GL_UNSIGNED_INT,&faces_fh_chess[0]);
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3,GL_FLOAT,0,&color_chess2[0]);

    glDrawElements(GL_TRIANGLES,3*faces_sh_chess.size(),GL_UNSIGNED_INT,&faces_sh_chess[0]);  

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferidoAjedrez()
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)
   // .....



   if(id_vbov==0){
      id_vbov=CrearVBO(GL_ARRAY_BUFFER,3*v.size()*sizeof(float),&v[0]);
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
   glEnableClientState(GL_VERTEX_ARRAY);
   ////
   glEnableClientState(GL_COLOR_ARRAY);
   ///
   glBindBuffer(GL_ARRAY_BUFFER,id_vboac1);
   glColorPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   ///
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vboaf1);
   glDrawElements(GL_TRIANGLES,faces_fh_chess.size()*3,GL_UNSIGNED_INT,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   ///
   glBindBuffer(GL_ARRAY_BUFFER,id_vboac2);
   glColorPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   ///
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vboaf2);
   glDrawElements(GL_TRIANGLES,faces_fh_chess.size()*3,GL_UNSIGNED_INT,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   ///
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);


}




void Malla3D::drawAjedrez(int modo_diferido)
{
   // completar .....(práctica 1)
   glShadeModel(GL_FLAT);
   if(modo_diferido==0){
      draw_ModoInmediatoAjedrez();
   } else{
      draw_ModoDiferidoAjedrez();
   }


}




