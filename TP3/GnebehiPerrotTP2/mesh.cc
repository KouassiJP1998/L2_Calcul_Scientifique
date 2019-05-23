#include  "mesh.h"
#include  <fstream>
#include <cstring>
#include "Triangle.h"

using namespace  std;
/*---------------------------------------------------------*/
void Mesh::readData(const string& filename)
{
  ifstream meshfile(filename.c_str());
  if( !meshfile.is_open() )
  {
    std::cerr<<"*** ERROR Mesh::readData() cannot open meshfile "<<filename<<"\n";
    assert(0);
    exit(1);
  }
   getNodes().read(meshfile);
   getCells().read(meshfile);
   meshfile.close();
}
/*---------------------------------------------------------*/
void Mesh::writeData(const string& filename) const
{
  ofstream meshfile(filename.c_str());
  if( !meshfile.is_open() )
  {
    std::cerr<<"*** ERROR Mesh::readData() cannot open meshfile "<<filename<<"\n";
    assert(0);
    exit(1);
  }
  getNodes().write(meshfile,"ascii");
  getCells().write(meshfile,"ascii");
  meshfile.close();
}

/*---------------------------------------------------------*/
void Mesh::writeVtk(const std::string& filename) const
{

  ofstream file(filename.c_str());
  file<<"# vtk DataFile Version 4.2"<<"\n";
  file<<"Vtk data"<<"\n";
  file<<"ASCII"<<"\n";
  file<<"DATASET UNSTRUCTURED_GRID"<<"\n";
  file<<"POINTS "<<getNNodes()<<" double"<<"\n";

  for(Vecteur<node2d>::const_iterator it=getNodes().begin(); it!=getNodes().end();it++)
  {
    file<<*it<<0.<<'\n';
  }
  file<<"CELLS "<<getNCells()<<"  "<<4*getNCells()<<"\n";
  for(Vecteur<trinode>::const_iterator it=getCells().begin(); it!=getCells().end();it++)
  {
    file<<"3 "<<*it<<'\n';
  }
  file<<"CELL_TYPES "<<getNCells()<<'\n';
  for(int i=0;i<getNCells();i++)
  {
    file<<"5"<<'\n';
  }

  file.close();
}
/*---------------------------------------------------------*/
double Mesh::computeArea() const
{
   double area=0.0;
   for (int i=0;i<getNCells();i++){

     trinode t = getCell(i);

     node2d n1 = getNode(t(0));
     node2d n2 = getNode(t(1));
     node2d n3 = getNode(t(2));

     Vecteur<node2d> v;
     v.push_back(n1);
     v.push_back(n2);
     v.push_back(n3);

     //cerr<<v<<endl;

     Triangle r(v);
     //std::cerr << r << '\n';
     area += r.getArea();
   }
   return area;
}

/*---------------------------------------------------------*/
