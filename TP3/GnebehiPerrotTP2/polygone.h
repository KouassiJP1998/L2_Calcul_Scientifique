# ifndef _Polygone_
# define _Polygone_
#include <stdlib.h>
#include "fixvecteur.h"
#include "vecteur.h"
class Polygone
{
protected:
  int _nnodes;
  Vecteur<node2d> _nodes;
  std::string _type;
  double _perimeter;
  double _area;
  void _computeperimeter();
  double _getDistance(const node2d &n1, const node2d &n2) const;
  virtual void _computeArea() =0;
public:
  virtual ~Polygone();
  Polygone(int n);
  Polygone(const Vecteur<node2d> & v);
  void init();
  const std::string& getType() const;
  int getNNodes() const;
  const node2d& getNode(int i) const;
  node2d& getNode(int i);
  double getArea() const;
  double getPerimeter() const;
  friend std::ostream & operator << (std::ostream&, const Polygone &) ;
};
#endif


