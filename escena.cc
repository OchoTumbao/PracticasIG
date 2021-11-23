

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....


//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************


bool compre_float(float a,float b){

   return fabs(a-b) < 0.01f;
}
Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

   Tupla4f negro(0.0,0.0,0.0,1.0);
   Tupla4f luz1a(0.2,0.2,0.2,1.0);
   Tupla4f luz1d(1.0,1.0,1.0,1.0);
   Tupla4f luz1s(1.0,1.0,1.0,1.0);
   Tupla4f verde(0.0,0.5,0.0,0.5);
   Tupla2f angulo(0.0,0.0);
   Tupla3f posicion(0.0,150.0,0.0);
   ld= new LuzDireccional(angulo,GL_LIGHT0,verde,verde,verde);
   lp= new LuzPosicional(posicion,GL_LIGHT1,luz1a,luz1d,luz1s);
   kk= new KlinkKlang();
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

void Escena::animarModeloJerarquico(){
   if(animacion){
   kk->modifica_anguloBanda(porcentajeBanda);
   kk->modifica_anguloEngranajes(porcentajeEngranaje);
   kk->modifica_Posicion(porcentajePosicion);
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibuja_escena(int modo_diferido,int modo_dibujo,bool tapas){
   switch (modo_dibujo){
      case 2:
         glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
         kk->draw(modo_diferido,modo_dibujo);
         break;
      case 1:
         glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
         kk->draw(modo_diferido,modo_dibujo);
         break;
      case 0:
         glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
         kk->draw(modo_diferido,modo_dibujo);
         break;
   default:
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      kk->draw(modo_diferido,modo_dibujo);
      break;
   }

}

void Escena::dibuja_escena_ajedrez(int modo_diferido,bool tapas){
   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   kk->drawAjedrez(modo_diferido);
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
                ld->activar();
                lp->activar();
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
                ld->activar();
                lp->activar();
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
         if (modoMenu==MODOANIMACION){
               if(animacion){
                  animacion=false;
                  cout << "Desactivada animación automatica" << endl;
               } else{
                  animacion=true;
                  cout << "Activada animación automatica" << endl;
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
         if (modoMenu==NADA){
            modoMenu=MODOANIMACION;
            cout << "MODO ANIMACION ACTIVADO" << endl;
            cout << "P: ACTIVAR ANIMACIÓN AUTOMATICA" << endl;
            cout << "+ AUMENTA LA VELOCIDAD DE LA ANIMACIÓN" << endl;
            cout << "- DIMINUYE LA VELOCIDAD DE LA ANIMACIÓN" << endl;
            cout << "0: SELECCIONAR GRADO 0" << endl;
            cout << "1: SELECCIONAR GRADO 1" << endl;
            cout << "2: SELECCIONAR GRADO 2" << endl;
            cout << "G: SELECCIONAR VELOCIDAD GLOBAL" << endl;
            cout << "Q: SALIR MODO ANIMACIÓN" << endl;
            cout << "F: AVANZA LA ANIMACIÓN PASO A PASO" << endl;

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
         if(modoMenu==MODOLUZ){
            cout << "Activando luz 0" << endl;
            ld->habilitar();
         }
         if (modoMenu==MODOANIMACION){
            if(grado0){
               grado0=false;
            } else{
               grado0=true;
            }
            cout << "Seleccionando grado 0" << endl;
         }
         break;
       case '1':
         if(modoMenu==MODOLUZ){
            cout << "Activando luz 1" << endl;
            lp->habilitar();
         } 
         if (modoMenu==MODOANIMACION){
            if(grado1){
               grado1=false;
            } else{
               grado1=true;
            }
            cout << "Seleccionando grado 1" << endl;
         }
         break;
      case '2':
         if(modoMenu==MODOLUZ){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }
         if (modoMenu==MODOANIMACION){
            if(grado2){
               grado2=false;
            } else{
               grado2=true;
            }
            cout << "Seleccionando grado 2" << endl;
         }
      break;
      case '3':
         if(modoMenu==MODOLUZ){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }
      break;
      case '4':
         if(modoMenu==MODOLUZ){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }

      break;
      case '5':
         if(modoMenu==MODOLUZ){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }
      break;
      case '6':
         if(modoMenu==MODOLUZ){
            cout << "Actualmente no hay mas de dos luces implementadas" << endl;
         }
      break;   
      case '7':
         if(modoMenu==MODOLUZ){
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
         if(modoMenu==MODOANIMACION){
               if(grado0){
                  kk->modifica_anguloBanda(porcentajeBanda);
               }
               if(grado1){
                  kk->modifica_anguloEngranajes(porcentajeEngranaje);
               }
               if(grado2){
                  kk->modifica_Posicion(porcentajePosicion);
               }
         }
      break;

      case 'G':
         if(modoMenu==MODOANIMACION){
            grado0=true;
            grado1=true;
            grado2=true;
         }
      break;

      case '+':
         if(modoMenu==MODOANIMACION){
            if(grado0){
               if((porcentajeBanda>0.0 || compre_float(porcentajeBanda,0.0) ) && (porcentajeBanda+0.1<2.0 || compre_float(porcentajeBanda+0.1,2.0) )){
                  porcentajeBanda+=0.1;
                  cout<< "Actual valor grado 0 " << porcentajeBanda << endl;
               }
            }
            if(grado1){
               if((porcentajeEngranaje>0.0 || compre_float(porcentajeEngranaje,0.0) ) && (porcentajeEngranaje+0.1<2.0 || compre_float(porcentajeEngranaje+0.1,2.0) )){
                  porcentajeEngranaje+=0.1;
                  cout<< "Actual valor grado 1 " << porcentajeEngranaje << endl;
               }
            }
            if(grado2){
               if((porcentajePosicion>0.0 || compre_float(porcentajePosicion,0.0) ) && (porcentajePosicion+0.1<2.0 || compre_float(porcentajePosicion+0.1,2.0) )){
                  porcentajePosicion+=0.1;
                  cout<< "Actual valor grado 2 " << porcentajePosicion << endl;
               }
            }
            
         }
      break;
      case '-':
         if(modoMenu==MODOANIMACION){
            if(grado0){
               if((porcentajeBanda-0.1>0.0 || compre_float(porcentajeBanda-0.1,0.0) ) && (porcentajeBanda<2.0 || compre_float(porcentajeBanda,2.0) )){
                  porcentajeBanda-=0.1;
                  cout<< "Actual valor grado 0 " << porcentajeBanda << endl;
               }
            }
            if(grado1){
               if((porcentajeEngranaje-0.1>0.0 || compre_float(porcentajeEngranaje-0.1,0.0) ) && (porcentajeEngranaje<2.0 || compre_float(porcentajeEngranaje,2.0) )){
                  porcentajeEngranaje-=0.1;
                  cout<< "Actual valor grado 1 " << porcentajeEngranaje << endl;
               }
            }
            if(grado2){
               if((porcentajePosicion-0.1>0.0 || compre_float(porcentajePosicion-0.1,0.0) ) && (porcentajePosicion<2.0 || compre_float(porcentajePosicion,2.0) )){
                  porcentajePosicion-=0.1;
                  cout<< "Actual valor grado 2 " << porcentajePosicion << endl;
               }
            }
            
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
