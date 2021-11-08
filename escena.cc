

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

   Tupla4f negro(0.0,0.0,0.0,1.0);
   Tupla4f blanco(1.0,1.0,1.0,1.0);
   Tupla4f rojo(1.0,0.0,0.0,1.0);    
   Tupla4f verde(0.0,1.0,0.0,1.0);
   Tupla2f angulo(0.0,0.0);
   Tupla3f posicion(0.0,6.0,0.0);
   cubo=new Cubo(100);
   tetraedro=new Tetraedro(100);
   peon= new ObjRevolucion("plys/peon.ply",50,true,true,1);
   ant=new ObjPLY("plys/ant.ply");
   //coche=new ObjPLY("plys/big_dodge.ply");
   //busto=new ObjPLY("plys/beethoven.ply");
   cilindro=new Cilindro(50,50,10,5,0,true,false);
   cono=new Cono(10,50,10,5,2,false,true);
   esfera= new Esfera(10,50,5,1,false,false);
   m1= new Material(blanco,negro,blanco,90.0);
   m2= new Material(negro,blanco,negro,90.0);
   m3= new Material(rojo,blanco,verde,90.0);
   ld= new LuzDireccional(angulo,GL_LIGHT0,verde,verde,verde);
   lp= new LuzPosicional(posicion,GL_LIGHT1,rojo,rojo,rojo);
   peon->setMaterial(*m1);
   esfera->setMaterial(*m2);
   ant->setMaterial(*m3);
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

void Escena::dibuja_escena(int modo_diferido,int modo_dibujo,bool tapas){
             glPushMatrix();
             if(modo_dibujo==0){
             glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
             } else if( modo_dibujo==1){
               glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); 
             } else{
                glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
             }
             glScalef(50.0,50.0,50.0);
             peon->draw(modo_diferido,modo_dibujo,tapas);
             glPopMatrix();
             glPushMatrix();
             glTranslatef(200.0,0.0,0.0);
             glScalef(2.0,2.0,2.0);
             ant->draw(modo_diferido,modo_dibujo);
             glPopMatrix();
             glPushMatrix();
             glTranslatef(-200.0,0.0,0.0);
             glScalef(10.0,10.0,10.0);
             esfera->draw(modo_diferido,modo_dibujo,tapas);
             glPopMatrix();
             glPushMatrix();
             glTranslatef(0.0,0.0,200.0);
             glScalef(10.0,10.0,10.0);
             cilindro->draw(modo_diferido,modo_dibujo,tapas);
             glPopMatrix();
             glPushMatrix();
             glTranslatef(0.0,0.0,-200.0);
             glScalef(10.0,10.0,10.0);
             cono->draw(modo_diferido,modo_dibujo,tapas);
             glPopMatrix();
}

void Escena::dibuja_escena_ajedrez(int modo_diferido,bool tapas){
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
             glPushMatrix();
             glScalef(50.0,50.0,50.0);
             peon->drawAjedrez(modo_diferido,tapas);
             glPopMatrix();
             glPushMatrix();
             glScalef(2.0,2.0,2.0);
             glTranslatef(30.0,0.0,0.0);
             ant->drawAjedrez(modo_diferido);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(-10.0,0.0,0.0);
             esfera->drawAjedrez(modo_diferido,tapas);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,25.0);
             cilindro->drawAjedrez(modo_diferido,tapas);
             glPopMatrix();
             glPushMatrix();
             glScalef(10.0,10.0,10.0);
             glTranslatef(0.0,0.0,-15.0);
             cono->drawAjedrez(modo_diferido,tapas);
             glPopMatrix();
}

void Escena::dibujar()
{
   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   glPointSize(10);
   glDisable(GL_LIGHTING);
    ejes.draw();
   switch(modo_d){
      case DIFERIDO:
          if(flag_luz==1){
             glEnable(GL_LIGHTING);
             switch (modo_sombreado)
             {
             case SMOOTH:
                glShadeModel(GL_SMOOTH);
                break;
             case FLAT:
                glShadeModel(GL_FLAT);
               break;
             
             default:
                glShadeModel(GL_SMOOTH);
                break;
             }
             dibuja_escena(1,0,tapas);
          } else{
             glDisable(GL_LIGHTING);
          if(flag_fill==1){
             dibuja_escena(1,0,tapas);
          }
          if(flag_lines==1){
            dibuja_escena(1,1,tapas);  
          }
          if(flag_points==1){
            dibuja_escena(1,2,tapas);  
          }
          if(flag_chess==1){
             dibuja_escena_ajedrez(1,tapas);
          }
          }
      break;
      case INMEDIATO:
          if (flag_luz==1){
             glEnable(GL_LIGHTING);
             switch (modo_sombreado)
             {
             case SMOOTH:
                glShadeModel(GL_SMOOTH);
                break;
             case FLAT:
                glShadeModel(GL_FLAT);
               break;
             
             default:
                glShadeModel(GL_SMOOTH);
                break;
             }
             dibuja_escena(0,0,tapas);
          }
          else{
             glDisable(GL_LIGHTING);
          if(flag_fill==1){
             dibuja_escena(0,0,tapas);
          }
          if(flag_lines==1){
             dibuja_escena(0,1,tapas);

             
          }
          if(flag_points==1){
             dibuja_escena(0,2,tapas);
          }
          if(flag_chess==1){
             dibuja_escena_ajedrez(0,tapas);
          }
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
         printf("Opciones disponibles: \n 'L' : Linea; \n 'P' : Puntos \n 'S': Solido  \n 'A': Ajedrez \n 'T' : Visualizacion de tapas \n 'U' : Visualizacion con iluminacion" );}
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
         if(modoMenu==SELVISUALIZACION){
            if(tapas){
               tapas=false;
            } else{
               tapas=true;
            }
            cout << "Actualiza tapas" << endl;
         }
         break;
      case 'U':
         if(modoMenu==SELVISUALIZACION){
            if(flag_luz==0){
               flag_luz=1;
               cout << "Activado modo iluminacion" << endl;
            } else{
               flag_luz=0;
               cout << "Desactivado Modo iluminacion" << endl;
            }
         }
      break;
       case 'P':
         if(modoMenu==SELVISUALIZACION){
           if(flag_luz==1){
               flag_luz=0;
            }
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
           if(flag_luz==1){
               flag_luz=0;
            }
            //ACTIVAR VISUALIZACION LINEAS
            if(flag_lines==0){
            flag_lines=1;
            cout << "Visualizacion por lineas activada" << endl;
            } else{
               flag_lines=0;
               cout << "Visualizacion por lineas desactivada " << endl;
            }
         } 
            if(modoMenu==NADA){
            modoMenu=MODOLUZ;
            cout << "MODO LUZ ACTIVADO" << endl;
            }
         break;
       case 'S':
         if(modoMenu==SELVISUALIZACION){
            //ACTIVAR VISUALIZACION SOLIDO
            if(flag_luz==1){
               flag_luz=0;
            }
            if(flag_fill==0){
            flag_fill=1;
            cout << "Visualizacion modo solido activada" << endl;
            } else{
               flag_fill=0;
               cout << "Visualizacion modo solido desactivada" << endl;
            }
         }

         if(modoMenu==MODOLUZ){
            modo_sombreado=SMOOTH;
         }
         break;
       case 'A':
         if(modoMenu==SELVISUALIZACION){
           if(flag_luz==1){
               flag_luz=0;
            }
            //ACTIVAR VISUALIZACION AJEDREZ
            if(flag_chess==0){
            flag_chess=1;
            cout << "Visualizacion modo ajedrez activado" << endl;
            } else{
               flag_chess=0;
               cout << "Visualizacion modo ajedrez desactivado" << endl;
            }
         } 
         if (modoMenu==MODOLUZ){
            if(flag_luz==1){
               variar_angulo=1;
               cout << "ANGULO A VARIAR ALFA" << endl;
            }
         }
         break;
       case 'I':
         if(modoMenu==SELDIBUJADO){
            //ACTIVAR MODO INMEDIATO
            modo_d=INMEDIATO;
            cout << "Activado modo dibujado inmediato" << endl;
         }
         break;

       case '0':
         if(flag_luz){
            cout << "Activando luz 0" << endl;
            ld->activar();
         }
         break;
       case '1':
         if(flag_luz){
            cout << "Activando luz 1" << endl;
            lp->activar();
         } 
         break;
      case '2':
         if(flag_luz){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }
      break;
      case '3':
         if(flag_luz){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }
      break;
      case '4':
         if(flag_luz){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }

      break;
      case '5':
         if(flag_luz){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }
      break;
      case '6':
         if(flag_luz){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }
      break;   
      case '7':
         if(flag_luz){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }
      break;

      case 'B':
         if(modoMenu==MODOLUZ){
            if(flag_luz){
               variar_angulo=0;
               cout << "ANGULO A VARIAR IGUAL A BETA" << endl;
            }
         }
      break;

      case '<':
         if(modoMenu==MODOLUZ){
            if(flag_luz){
               if(variar_angulo==1){
                  ld->variarAnguloAlpha(-0.174533);
               } else{
                  ld->variarAnguloBeta(-0.174533);
               }
            } 
         }
      break;

      case '>':
         if(modoMenu==MODOLUZ){
            if(flag_luz){
               if(variar_angulo==1){
                  ld->variarAnguloAlpha(0.174533);
               } else{
                  ld->variarAnguloBeta(0.174533);
               }
            }
         }
      break;
      
      case 'F':
         if(modoMenu==MODOLUZ){
            if(flag_luz){
               modo_sombreado=FLAT;
            }
         }

            
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
