#include "mesh.h"
#include <iostream>
#include <fstream>
int main()
{
   Mesh mesh;
   mesh.readData("domain.msh");
   mesh.writeVtk("Domain.vtk");
   double area=mesh.computeArea();
   std::cerr<<"Aire du domaine: "<<area<<'\n';

}
