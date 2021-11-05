#include <aux.h>

class Material{
    private:
        Tupla4f difuso;
        Tupla4f especular;
        Tupla4f ambiente;
        float brillo;
    public:
    Material(Tupla4f difuso,Tupla4f especular,Tupla4f ambiente,float brillo);
    void aplicar();
};