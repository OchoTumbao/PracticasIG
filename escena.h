#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luces.h"

typedef enum {NADA, SELTAPAS,SELVISUALIZACION,SELDIBUJADO} menu;
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
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro= nullptr ; // es importante inicializarlo a 'nullptr'
   ObjRevolucion * peon= nullptr;
   ObjPLY * ant=nullptr;
   ObjPLY * coche=nullptr;
   ObjPLY * busto=nullptr;
   Cilindro * cilindro=nullptr;
   Cilindro * cilindrox=nullptr;
   Cilindro * cilindroz=nullptr;
   Cono * cono=nullptr;
   Esfera * esfera=nullptr;
   Material * m1=nullptr;
   Material * m2=nullptr;
   Material * m3=nullptr;
   LuzDireccional * ld=nullptr;
   LuzPosicional * lp=nullptr;

   modo_dibujado modo_d=DIFERIDO;
   objeto_a_mostrar dibujo=NO;
   int flag_points=0;
   int flag_lines=0;
   int flag_fill=1;
   int flag_chess=0;
   int flag_luz=0;
   bool tapas=true;

   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
    void dibuja_escena(int modo_diferido=1,int modo_dibujado=0,bool tapas=true);
    void dibuja_escena_ajedrez(int modo_diferido=1,bool tapas=true);

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
