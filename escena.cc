

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    
   cubo=new Cubo(100);
   tetraedro=new Tetraedro(100);
   peon= new ObjRevolucion("plys/peon.ply",50,tapas_sup,tapas_inf,1);
   ant=new ObjPLY("plys/ant.ply");
   coche=new ObjPLY("plys/big_dodge.ply");
   //busto=new ObjPLY("plys/beethoven.ply");
   cilindro=new Cilindro(10,50,10,5,0,tapas_sup,tapas_inf);
   cono=new Cono(10,50,10,5,2,tapas_sup,tapas_inf);
   esfera= new Esfera(10,50,5,2,tapas_sup,tapas_inf);
    // crear los objetos de la escena....
    // .......completar: ...
    // .....

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
   glEnable(GL_CULL_FACE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   glPointSize(10);
    ejes.draw();
   switch(modo_d){
      case DIFERIDO:
          if(flag_fill==1){
             glPushMatrix();
             glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
             glScalef(50.0,50.0,50.0);
             peon->draw(1,0);
             glPopMatrix();
             glPushMatrix();
             glScalef(2.0,2.0,2.0);
             glTranslatef(30.0,0.0,0.0);
             ant->draw(1,0);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(-10.0,0.0,0.0);
             esfera->draw(1,0);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,25.0);
             cilindro->draw(1,0);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,-15.0);
             cono->draw(1,0);
             glPopMatrix();

          }
          if(flag_lines==1){
             glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
             glPushMatrix();
             glScalef(50.0,50.0,50.0);
             peon->draw(1,1);
             glPopMatrix();
             glPushMatrix();
             glScalef(2.0,2.0,2.0);
             glTranslatef(30.0,0.0,0.0);
             ant->draw(1,1);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(-10.0,0.0,0.0);
             esfera->draw(1,1);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,25.0);
             cilindro->draw(1,1);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,-15.0);
             cono->draw(1,1);
             glPopMatrix();

             change_observer();
          }
          if(flag_points==1){
             glPushMatrix();
             glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
             glScalef(50.0,50.0,50.0);
             peon->draw(1,2);
             glPopMatrix();
             glPushMatrix();
             glScalef(2.0,2.0,2.0);
             glTranslatef(30.0,0.0,0.0);
             ant->draw(1,2);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(-10.0,0.0,0.0);
             esfera->draw(1,2);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,25.0);
             cilindro->draw(1,2);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,-15.0);
             cono->draw(1,2);
             glPopMatrix();
             
          }
          if(flag_chess==1){
             glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
             glPushMatrix();
             glScalef(50.0,50.0,50.0);
             peon->drawAjedrez(1);
             glPopMatrix();
             glPushMatrix();
             glScalef(2.0,2.0,2.0);
             glTranslatef(30.0,0.0,0.0);
             ant->drawAjedrez(1);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(-10.0,0.0,0.0);
             esfera->drawAjedrez(1);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,25.0);
             cilindro->drawAjedrez(1);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,-15.0);
             cono->drawAjedrez(1);
             glPopMatrix();
             
          }
      break;
      case INMEDIATO:
          if(flag_fill==1){
             glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
             glPushMatrix();
             glScalef(50.0,50.0,50.0);
             peon->draw(0,0);
             glPopMatrix();
             glPushMatrix();
             glScalef(2.0,2.0,2.0);
             glTranslatef(30.0,0.0,0.0);
             ant->draw(0,0);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(-10.0,0.0,0.0);
             esfera->draw(0,0);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,25.0);
             cilindro->draw(0,0);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,-15.0);
             cono->draw(1,0);
             glPopMatrix();

          }
          if(flag_lines==1){
             glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
             glPushMatrix();
             glScalef(50.0,50.0,50.0);
             peon->draw(0,1);
             glPopMatrix();
             glPushMatrix();
             glScalef(2.0,2.0,2.0);
             glTranslatef(30.0,0.0,0.0);
             ant->draw(0,1);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(-10.0,0.0,0.0);
             esfera->draw(0,1);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,25.0);
             cilindro->draw(0,1);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,-15.0);
             cono->draw(0,1);
             glPopMatrix();

             
          }
          if(flag_points==1){
             glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
             glScalef(50.0,50.0,50.0);
             peon->draw(0,2);
             glPopMatrix();
             glPushMatrix();
             glScalef(2.0,2.0,2.0);
             glTranslatef(30.0,0.0,0.0);
             ant->draw(0,2);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(-10.0,0.0,0.0);
             esfera->draw(0,2);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,25.0);
             cilindro->draw(0,2);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,-15.0);
             cono->draw(0,2);
             glPopMatrix();
          }
          if(flag_chess==1){
             glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
             glPushMatrix();
             glScalef(50.0,50.0,50.0);
             peon->drawAjedrez(0);
             glPopMatrix();
             glPushMatrix();
             glScalef(2.0,2.0,2.0);
             glTranslatef(30.0,0.0,0.0);
             ant->drawAjedrez(0);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(-10.0,0.0,0.0);
             esfera->drawAjedrez(0);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,25.0);
             cilindro->drawAjedrez(0);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,-15.0);
             cono->drawAjedrez(0);
             glPopMatrix();
             
          }
      break;
   }

    glutSwapBuffers();
    // COMPLETAR
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer 
    // cubo->draw()
    // o
    // tetraedro->draw()
    
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
        case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         if(modoMenu==NADA){
         modoMenu=SELVISUALIZACION;
         printf("Opciones disponibles: \n 'L' : Linea; \n 'P' : Puntos \n 'S': Solido  \n 'A': Ajedrez");}
         break ;
       case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         if(modoMenu==NADA){
            modoMenu=SELDIBUJADO;
            printf("Opciones disponibles: \n 'I' : Inmediato; \n 'D' : Diferido");
         } else if(modoMenu==SELDIBUJADO){
            modo_d=DIFERIDO;
            cout << "Modo diferido Activado " << endl;
         }
         break ;
         // COMPLETAR con los diferentes opciones de teclado
         break;
       case 'T':
         if(modoMenu==NADA){
            modoMenu=SELTAPAS;
            cout << "Modo seleccion de tapas "<< endl << "S: Actualiza tapas superiores" << endl << "I: Actualiza tapas inferiores" << endl;
         }
         break;
       case 'P':
         if(modoMenu==SELVISUALIZACION){
            //ACTIVAR VISUALIZACION PUNTOS
            if(flag_points==0){
            flag_points=1;
            cout << "Visualizacion por puntos activada" << endl;
            } else{
               flag_points=0;
               cout << "Visualizacion por puntos desactivada " << endl;
            }
         }
         break;
       case 'L':
         if(modoMenu==SELVISUALIZACION){
            //ACTIVAR VISUALIZACION LINEAS
            if(flag_lines==0){
            flag_lines=1;
            cout << "Visualizacion por lineas activada" << endl;
            } else{
               flag_lines=0;
               cout << "Visualizacion por lineas desactivada " << endl;
            }
         }
         break;
       case 'S':
         if(modoMenu==SELVISUALIZACION){
            //ACTIVAR VISUALIZACION SOLIDO
            if(flag_fill==0){
            flag_fill=1;
            cout << "Visualizacion modo solido activada" << endl;
            } else{
               flag_fill=0;
               cout << "Visualizacion modo solido desactivada" << endl;
            }
         } else if(modoMenu==SELTAPAS){
            if(tapas_sup){
               tapas_sup=false;
            } else{
               tapas_sup=true;
            }
               cilindro=new Cilindro(10,50,10,5,0,tapas_sup,tapas_inf);
               cono=new Cono(10,50,10,5,2,tapas_sup,tapas_inf);
               esfera= new Esfera(10,50,5,2,tapas_sup,tapas_inf);
               peon= new ObjRevolucion("plys/peon.ply",50,tapas_sup,tapas_inf,1);
               cout << "Actualizadas tapas superiores" << endl;
         }
         break;
       case 'A':
         if(modoMenu==SELVISUALIZACION){
            //ACTIVAR VISUALIZACION AJEDREZ
            if(flag_chess==0){
            flag_chess=1;
            cout << "Visualizacion modo ajedrez activado" << endl;
            } else{
               flag_chess=0;
               cout << "Visualizacion modo ajedrez desactivado" << endl;
            }
         }
         break;
       case 'I':
         if(modoMenu==SELDIBUJADO){
            //ACTIVAR MODO INMEDIATO
            modo_d=INMEDIATO;
            cout << "Activado modo dibujado inmediato" << endl;
         } else if(modoMenu==SELTAPAS){
            if(tapas_inf){
               tapas_inf=false;
            } else{
               tapas_inf=true;
            }
               cilindro=new Cilindro(10,50,10,5,0,tapas_sup,tapas_inf);
               cono=new Cono(10,50,10,5,2,tapas_sup,tapas_inf);
               esfera= new Esfera(10,50,5,2,tapas_sup,tapas_inf);
               peon= new ObjRevolucion("plys/peon.ply",50,tapas_sup,tapas_inf,1);
               cout << "Actualizadas tapas inferiores" << endl;

         }
         break;

            
   }

   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
