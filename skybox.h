#include "aux.h"
#include "malla.h"
#include "luces.h"

class Skybox : public Malla3D
{   
   private:
        std::string archivo;
        std::vector <Tupla3f> tc;
        Cubemap * t=nullptr;
        LuzPosicional * sol=nullptr;
        LuzPosicional * luna=nullptr;
        Tupla3f * posicionsol=nullptr;
        Tupla4f * colAmbSol=nullptr;
        Tupla4f * colDifSol=nullptr;
        Tupla4f * colEspSol=nullptr;
        Tupla3f * posicionluna=nullptr;
        Tupla4f * colAmbLuna=nullptr;
        Tupla4f * colDifLuna=nullptr;
        Tupla4f * colEspLuna=nullptr;
        float rotacionluces=0;
        float lado;
        float Gsol=0.24;
        float Bsol=0.24;
        float Rsol=1.0;
        float Gluna=0.23;
        float Bluna=0.7;
        float Rluna=0.08;
   public:
   Skybox(std::string archivo,float l=1);
   Skybox(std::string archivo[6],float l=1);
   void draw_ModoInmediato(int modo_dibujo=0);
   void draw_ModoDiferido(int modo_dibujo=0);
   void draw(int modo_diferido=1, int modo_dibujo=0);
   void setTextura(std::string archivo);
   void setTextura(std::string archivo[6]);
   void animarLuces(float porcentaje);
   void habilitarLuzSol();
   void habilitarLuzLuna();

} ;