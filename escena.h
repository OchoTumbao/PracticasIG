#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "KlinkKlang.h"
#include "skybox.h"

typedef enum {NADA, SELTAPAS,SELVISUALIZACION,SELDIBUJADO,MODOLUZ,MODOANIMACION} menu;
typedef enum{INMEDIATO,DIFERIDO} modo_dibujado;
typedef enum{CUBO,TETRAEDRO,BUSTO,P2,NO} objeto_a_mostrar;
typedef enum{SMOOTH,FLAT} sombreado;
class Escena
{

   private:

   

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    


   void clear_window();

   menu modoMenu=NADA;
   sombreado modo_sombreado=SMOOTH;
   // Objetos de la escena
   Ejes ejes;
   LuzDireccional * ld=nullptr;
   LuzPosicional * lp=nullptr;
   KlinkKlang* kk=nullptr;
   Magnemite *mm=nullptr;
   ObjPLY * Dalinar=nullptr;
    ObjRevolucion * pokeball=nullptr;
    Cubo * suelo=nullptr;
    Tetraedro * piramide=nullptr;
    Skybox * skybox=nullptr;

   modo_dibujado modo_d=DIFERIDO;
   objeto_a_mostrar dibujo=NO;
   int flag_points=0;
   int flag_lines=0;
   int flag_fill=1;
   int flag_chess=0;
   int flag_luz=1;
   bool tapas=true;
   int variar_angulo=0;
   int luz1=1;
   int luz2=1;
   float porcentajeBanda=1.0;
   float porcentajeEngranaje=1.0;
   float porcentajePosicion=1.0;
   float porcentajePokeball=1.0;
   bool animacion=true;
   bool grado0=false;
   bool grado1=false;
   bool grado2=false;
   bool lanzar_pokeballs=false;
   bool setup_inicial=true;

   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
    void animarModeloJerarquico();

	// Dibujar
	void dibujar() ;
    void dibuja_escena(int modo_diferido=1,int modo_dibujado=0,bool tapas=true);
    void dibuja_escena_ajedrez(int modo_diferido=1,bool tapas=true);

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );


};
#endif
