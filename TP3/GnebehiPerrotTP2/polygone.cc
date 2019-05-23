#include <math.h>
#include "polygone.h"
/*-------------------------------------------------------------*/
Polygone::~Polygone()
{}
/*-------------------------------------------------------------*/

Polygone::Polygone(int n)
{
  _nnodes=n;
  _nodes.reInit(n);
}

/*-------------------------------------------------------------*/
Polygone::Polygone(const Vecteur<node2d> &v)
{
  _nnodes=v.size();
  _nodes.reInit(_nnodes);
  _nodes=v;
  init();
}
/*-------------------------------------------------------------*/
void Polygone::init()
{
  _computeperimeter ();
  _computeArea();
}

/*-------------------------------------------------------------*/
double Polygone::_getDistance(const node2d & n1,const node2d & n2) const
{
   return sqrt((n1(0)-n2(0))*(n1(0)-n2(0))+(n1(1)-n2(1))*(n1(1)-n2(1)));
}

/*-------------------------------------------------------------*/
void Polygone::_computeperimeter ()
{
   double p=0.; 
    for (unsigned int i=0;i<_nnodes-1;i++){
        p+=_getDistance(_nodes[i],_nodes[i+1]);
    }
    p+=_getDistance(_nodes[_nnodes-1],_nodes[0]);
  _perimeter=p;
}

/*-------------------------------------------------------------*/

const std::string& Polygone::getType() const
{
  return _type;
}

/*-------------------------------------------------------------*/

int Polygone::getNNodes() const
{
  return _nnodes;
}

/*-------------------------------------------------------------*/

const node2d& Polygone::getNode(int i) const
{
  return _nodes[i];
}

/*-------------------------------------------------------------*/

node2d& Polygone::getNode(int i)
{
  return _nodes[i];
}
/*-------------------------------------------------------------*/

double Polygone::getArea() const
{
  return _area;
}

/*-------------------------------------------------------------*/

double Polygone::getPerimeter() const
{
  return _perimeter;
}

/*-------------------------------------------------------------*/
std::ostream & operator << (std::ostream& os, const Polygone & p)
{
    os<<"Le polygone est un "<<p._type<<'\n';
    os<<" Nombre de sommets: "<<p._nnodes<<'\n';
    for (unsigned int i=0; i<p._nnodes;i++)
       os<<"\t\t Sommet "<<i<<": "<<p._nodes[i];
    os<<" Aire: "<<p.getArea()<<'\n';
    os<<" Périmètre: "<<p.getPerimeter()<<'\n';
    

    return os;
}
  
