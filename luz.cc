#include "luz.h"

void Luz::activar(){
    glLightfv ( id , GL_DIFFUSE , colorDifuso );
    glLightfv(id,GL_AMBIENT,colorAmbiente);
    glLightfv(id,GL_SPECULAR,colorEspecular);
    glLightfv(id,GL_POSITION,posicion);
}

void Luz::habilitar(){
        if(glIsEnabled(id)){
            glDisable(id);
        }else{
            glEnable(id);
    }
}
