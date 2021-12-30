#include "camara.h"
Tupla3f RotyEjeY(Tupla3f punto, float radianes){
   float resx,resy,resz;
   resx=punto(0)*cos(radianes)+punto(2)*sin(radianes);
   resy=punto(1);
   resz=punto(0)*-sin(radianes)+punto(2)*cos(radianes);
   return Tupla3f(resx,resy,resz);
}

Tupla3f RotyEjeX(Tupla3f punto, float radianes){
   float resx,resy,resz;
   resx=punto(0);
   resy=punto(1)*cos(radianes)+punto(2)*-sin(radianes);
   resz=punto(1)*sin(radianes)+punto(2)*cos(radianes);
   return Tupla3f(resx,resy,resz);
}

Tupla3f RotyEjeZ(Tupla3f punto, float radianes){
   float resx,resy,resz;
   resx=punto(0)*cos(radianes)+punto(1)*-sin(radianes);
   resy=punto(0)*sin(radianes)+punto(1)*cos(radianes);
   resz=punto(2);
   return Tupla3f(resx,resy,resz);
}





Camara::Camara(Tupla3f eye,Tupla3f at,Tupla3f up,int tipo,float left,float right,float top,float bottom,float near,float far){
    this->eye=eye;
    this->eye_original=eye;
    this->at=at;
    this->at_original;
    this->up=up;
    this->tipo=tipo;
    this->left=left;
    this->right=right;
    this->bottom=bottom;
    this->top=top;
    this->near=near;
    this->far=far;
}

void Camara::rotarXexaminar(float angulo){
   float x = eye(X) - at(X);
   float y = cos(angulo) * (eye(Y) - at(Y)) - sin(angulo) * (eye(Z) - at(Z));
   float z = sin(angulo) * (eye(Y) - at(Y)) + cos(angulo) * (eye(Z) - at(Z));

   eye(X) = x + at(X);
   eye(Y) = y + at(Y);
   eye(Z) = z + at(Z);
}

void Camara::rotarYexaminar(float angulo){
   float x = cos(angulo) * (eye(X) - at(X)) + sin(angulo) * (eye(Z) - at(Z));
   float y = eye(Y) - at(Y);
   float z = -sin(angulo) * (eye(X) - at(X)) + cos(angulo) * (eye(Z) - at(Z));

   eye(X) = x + at(X);
   eye(Y) = y + at(Y);
   eye(Z) = z + at(Z);
}

void Camara::seleccionar(Tupla3f punto){
    this->at=punto;
    this->estado=EXAMINAR;
}

void Camara::deseleccionar(){
    if(estado==EXAMINAR){
    this->at=at_original;
    this->eye=eye_original;
    this->estado=PRIMERA_PERSONA;
    }
}

void Camara::rotarX(float angulo){
    if(estado==PRIMERA_PERSONA){
        rotarXFirstPerson(angulo);
    }
    else{
        rotarXexaminar(angulo);
    }
}

void Camara::rotarY(float angulo){
    if(estado==PRIMERA_PERSONA){
        rotarYFirstPerson(angulo);
    }
    else{
        rotarYexaminar(angulo);
    }
}

void Camara::rotarXFirstPerson(float angulo){
   float x = at(X) - eye(X);
   float y = cos(angulo) * (at(Y) - eye(Y)) - sin(angulo) * (at(Z) - eye(Z));
   float z = sin(angulo) * (at(Y) - eye(Y)) + cos(angulo) * (at(Z) - eye(Z));

   at(X) = x + eye(X);
   at(Y) = y + eye(Y);
   at(Z) = z + eye(Z);
}

void Camara::rotarYFirstPerson(float angulo){
   float x = cos(angulo) * (at(X) - eye(X)) + sin(angulo) * (at(Z) - eye(Z));
   float y = at(Y) - eye(Y);
   float z = -sin(angulo) * (at(X) - eye(X)) + cos(angulo) * (at(Z) - eye(Z));

   at(X) = x + eye(X);
   at(Y) = y + eye(Y);
   at(Z) = z + eye(Z);
}




void Camara::zoom(float factor){
    left*=factor;
    right*=factor;
    bottom*=factor;
    top*=factor;
}

void Camara::updateScreen(float ratio){
    right=top*ratio;
    left=bottom*ratio;
}

void Camara::setObserver(){
    gluLookAt(eye(0),eye(1),eye(2),at(0),at(1),at(2),up(0),up(1),up(2));
}

void Camara::setProjection(){
    if(tipo==0){
        glOrtho(left,right,bottom,top,near,far);
    }
    else{
        glFrustum(left,right,bottom,top,near,far);
    }
}

void Camara::mover(int x,int y,bool primera_persona){
        rotarX(x*(M_PI/180));
        rotarY(y*(M_PI/180));
    

}