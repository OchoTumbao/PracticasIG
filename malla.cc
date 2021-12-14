#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

GLuint Malla3D::CrearVBO ( GLuint tipo_vbo , GLuint tamanio_bytes ,
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
   glEnableClientState(GL_NORMAL_ARRAY);
   if(!ct.empty()){
     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
     glTexCoordPointer(2, GL_FLOAT, 0, &ct[0]);
     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   }
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

void Malla3D::draw_ModoDiferido(int modo_dibujo)
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
   glNormalPointer(GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   if(!ct.empty()){
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glBindBuffer(GL_ARRAY_BUFFER,id_vboct);
   glTexCoordPointer(2, GL_FLOAT, 0, 0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   }
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbof);
   glDrawElements(GL_TRIANGLES,f.size()*3,GL_UNSIGNED_INT,0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);


}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido





void Malla3D::draw(int modo_diferido,int modo_dibujo)
{
   // completar .....(práctica 1)
   m.aplicar();
   if(!ct.empty()){
      t->activar();
   }
   if(modo_diferido==0){
      draw_ModoInmediato(modo_dibujo);
   } else{
      draw_ModoDiferido(modo_dibujo);
   }

   glDisable(GL_TEXTURE_2D);


}

void Malla3D::draw_ModoInmediatoAjedrez()
{
  // visualizar la malla usando glDrawElements,
  // Inicializar Array Vertices
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   // Indicamos buffer de vertices

   glVertexPointer(3,GL_FLOAT,0,&v[0]);
   glNormalPointer(GL_FLOAT,0,&vn[0]);
   
   //Visualizamos en modo inmediato, parametros: tipo de primitiva, numero de indices tipo de los indices y direccion de los indices
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3,GL_FLOAT,0,&color_chess1[0]);
   glDrawElements(GL_TRIANGLES,3*faces_fh_chess.size(),GL_UNSIGNED_INT,&faces_fh_chess[0]);
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(3,GL_FLOAT,0,&color_chess2[0]);

    glDrawElements(GL_TRIANGLES,3*faces_sh_chess.size(),GL_UNSIGNED_INT,&faces_sh_chess[0]);  

   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)


void Malla3D::setMaterial(Material m){
   this->m=m;
}

void Malla3D::setTextura(std::string archivo){
   t=new Textura(archivo);
}

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
   if(id_vbovn==0){
      id_vbovn=CrearVBO(GL_ARRAY_BUFFER,3*vn.size()*sizeof(float),&vn[0]);
   }





   ////
   glBindBuffer(GL_ARRAY_BUFFER,id_vbov);
   glVertexPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glBindBuffer(GL_ARRAY_BUFFER,id_vbovn);
   glNormalPointer(GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
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
   glDisableClientState(GL_NORMAL_ARRAY);


}

void Malla3D::calcular_normales(){
      Tupla3f v1;
      Tupla3f v2;
      for(int i=0;i<v.size();i++){
      vn.push_back(Tupla3f(0.0,0.0,0.0));
      }
   for(int i=0;i<f.size();i++){
      Tupla3f v1=v.at(f.at(i)(1))-v.at(f.at(i)(0));
      Tupla3f v2=v.at(f.at(i)(2))-v.at(f.at(i)(0));
      Tupla3f res=v1.cross(v2);
      if(res.lengthSq()>0){
      res=res.normalized();
      vn.at(f.at(i)(0))=vn.at(f.at(i)(0))+res;
      vn.at(f.at(i)(1))=vn.at(f.at(i)(1))+res;
      vn.at(f.at(i)(2))=vn.at(f.at(i)(2))+res;
      }
 
   }
   for(int i=0;i<vn.size();i++){
      if(vn.at(i).lengthSq()>0){
      vn.at(i)=vn.at(i).normalized();
      }
   }
}




void Malla3D::drawAjedrez(int modo_diferido)
{
   // completar .....(práctica 1)
   m.aplicar();
   if(modo_diferido==0){
      draw_ModoInmediatoAjedrez();
   } else{
      draw_ModoDiferidoAjedrez();
   }


}

void Malla3D::rellenar_colores(){
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



