#include "aux.h"

typedef enum state {PRIMERA_PERSONA,EXAMINAR};
class Camara{
    private:
        Tupla3f eye=Tupla3f(0,0,0);
        Tupla3f at=Tupla3f(0,0,-1);
        Tupla3f up=Tupla3f(0,1,0);
        Tupla3f at_original=Tupla3f(0,0,-1);
        Tupla3f eye_original=Tupla3f(0,0,0);
        state estado=PRIMERA_PERSONA;

        int tipo=1;
        float left,right,bottom,top,near,far;
    public:
        Camara(Tupla3f eye,Tupla3f at,Tupla3f up,int tipo,float left,float right,float top,float bottom,float near,float far);
        Camara()=default;
        void rotarXexaminar(float angulo);
        void rotarYexaminar(float angulo);
        void rotarX(float angulo);
        void rotarY(float angulo);
        void rotarXFirstPerson(float angulo);
        void rotarYFirstPerson(float angulo);
        void seleccionar(Tupla3f punto);
        void deseleccionar();
        void mover(int x,int y,bool primera_persona);
        void zoom(float factor);
        void updateScreen(float ratio);
        void setObserver();
        void setProjection();

};