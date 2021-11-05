#include <material.h>

Material::Material(Tupla4f difuso,Tupla4f especular,Tupla4f ambiente,float brillo){
    this->difuso=difuso;
    this->especular=especular;
    this->ambiente=ambiente;
    this->brillo=brillo;
}

void Material::aplicar(){
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,difuso);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,especular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambiente);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);
}