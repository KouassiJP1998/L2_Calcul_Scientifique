#include "polygone.h"

class Triangle : public Polygone {
	public :
		Triangle();
		Triangle(const Vecteur<node2d> & v);
		~Triangle();

	protected:
		virtual void _computeArea();
 };
