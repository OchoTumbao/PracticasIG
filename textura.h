#include "aux.h"
#include "jpg_imagen.hpp"

class Textura{
    protected:
        unsigned int w, h;
        GLuint id=0;
    private:
        std::vector<unsigned char> data;
    public:
        Textura()= default;
        Textura(const std::string filename);
        void activar();
        
};

class Cubemap : public Textura {
    private:
        std::vector<unsigned char>data[6];
        unsigned int hs[3];
        unsigned int ws[4];
    public:
        Cubemap(const std::string filename);
        Cubemap(const std::string filename[6]);
        void activar();
};