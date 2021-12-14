#include "textura.h"

Textura::Textura(const std::string filename){
    jpg::Imagen * pimg=nullptr;
    pimg=new jpg::Imagen(filename);
    this->w=pimg->tamX();
    this->h=pimg->tamY();
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            unsigned char* texels=pimg->leerPixel(j,h-i-1);
            data.push_back(texels[0]);
            data.push_back(texels[1]);
            data.push_back(texels[2]);
    }   
    }
}



void Textura::activar(){


    glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (this->id == 0){
	glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    printf("La textura con id %d tiene %lu bytes en un archivo de %dx%d\n", id, data.size(), w, h);
    gluBuild2DMipmaps ( GL_TEXTURE_2D ,GL_RGB , w ,h ,GL_RGB ,GL_UNSIGNED_BYTE ,data.data() );

	} else{
        glBindTexture(GL_TEXTURE_2D, this->id);
    }

}

Cubemap::Cubemap(const std::string filename) {
    jpg::Imagen * pimg =new jpg::Imagen(filename);
    this->w=pimg->tamX();
    this->h=pimg->tamY();
    for(int i=3;i>0;i--){
        this->hs[i-1]=(h/3)*i;
    }
    for(int i=0;i<4;i++){
        this->ws[i]=(w/4)*i;
    }
    //leemos las 6 caras en el orden X Positivo(hs[1]ws[2]), X Negativo(hs[1]ws[0]), Y Positivo(hs[2]ws[1]), Y Negativo(hs[0]ws[1])
    //, Z Positivo(hs[1]ws[1]), Z Negativo(hs[1]ws[3])
    
    //X positivo
    for(int i=(h/3)-1;i>=0;i--){
        for(int j=0;j<w/4;j++){
            unsigned char* texels=pimg->leerPixel(ws[2]+j,hs[1]-i);
            data[0].push_back(texels[0]);
            data[0].push_back(texels[1]);
            data[0].push_back(texels[2]);
    }   
    }
    //X negativo
    for(int i=(h/3)-1;i>=0;i--){
        for(int j=0;j<w/4;j++){
            unsigned char* texels=pimg->leerPixel(ws[0]+j,hs[1]-i);
            data[1].push_back(texels[0]);
            data[1].push_back(texels[1]);
            data[1].push_back(texels[2]);
    }   
    }
    //Y positivo
    for(int i=(h/3)-1;i>=0;i--){
        for(int j=0;j<w/4;j++){
            unsigned char* texels=pimg->leerPixel(ws[1]+j,hs[0]-i);
            data[2].push_back(texels[0]);
            data[2].push_back(texels[1]);
            data[2].push_back(texels[2]);
    }   
    }
    //Y negativo
    for(int i=(h/3)-1;i>=0;i--){
        for(int j=0;j<w/4;j++){
            unsigned char* texels=pimg->leerPixel(ws[1]+j,hs[2]-i);
            data[3].push_back(texels[0]);
            data[3].push_back(texels[1]);
            data[3].push_back(texels[2]);
    }   
    }
    //Z positivo
    for(int i=(h/3)-1;i>=0;i--){
        for(int j=0;j<w/4;j++){
            unsigned char* texels=pimg->leerPixel(ws[1]+j,hs[1]-i);
            data[4].push_back(texels[0]);
            data[4].push_back(texels[1]);
            data[4].push_back(texels[2]);
    }   
    }
    //Z negativo
    for(int i=(h/3)-1;i>=0;i--){
        for(int j=0;j<w/4;j++){
            unsigned char* texels=pimg->leerPixel(ws[3]+j,hs[1]-i);
            data[5].push_back(texels[0]);
            data[5].push_back(texels[1]);
            data[5].push_back(texels[2]);
    }   
    }
}

Cubemap::Cubemap(const std::string filename[6]){
    for(int i=0;i<6;i++){
        jpg::Imagen * pimg=new jpg::Imagen(filename[i]);
        this->w=pimg->tamX();
        this->h=pimg->tamY();
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            unsigned char* texels=pimg->leerPixel(j,h-i-1);
            data[i].push_back(texels[0]);
            data[i].push_back(texels[1]);
            data[i].push_back(texels[2]);
    }   
    }
    }

}


void Cubemap::activar(){
    glEnable(GL_TEXTURE_CUBE_MAP);

glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	if (this->id == 0){
	glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
    for(int i=0;i<6;i++){
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, ws[1]-ws[0], hs[1]-hs[0], 0, GL_RGB, GL_UNSIGNED_BYTE, &data[i][0]);
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP); 

    //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	} else{
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
    }


glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

}





