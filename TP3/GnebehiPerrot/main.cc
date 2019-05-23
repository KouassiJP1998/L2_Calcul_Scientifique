#include "mesh.h"
#include <iostream>
#include <fstream>

int main()
{
   Mesh mesh;
   mesh.readData("domain.msh");
   mesh.writeVtk("Domain.vtk");
   double area = mesh.computeArea();
   std::cerr<<"Aire du domaine: "<<area<<'\n';

   //Informations après lancement du fichier Domain.vtk sur ParaView :
   //"Le fichier généré contient comme informations :
   //"Nombre de cellules du maillage : 8540"
   //"Nombre de points du maillage : 4395" 

}
