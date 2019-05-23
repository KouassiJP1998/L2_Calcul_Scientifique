#include "Triangle.h"
#include <math.h>


Triangle::Triangle():Polygone(3){
	//Appel du constructeur de Polygone avec n=3
}

Triangle::Triangle(const Vecteur<node2d> &v):Polygone(v){
  //init();
}

Triangle::~Triangle(){
	//Destructeur
}

void Triangle::_computeArea(){
			node2d n1 = _nodes[0];
	    	node2d n2 = _nodes[1];		
	    	node2d n3 = _nodes[2];

	    	_area = (1.0/2.0)*fabs(( (n2(0) - n1(0)) * (n3(1) - n1(1)) ) - ( (n2(1) - n1(1)) * (n3(0) - n1(0)) ));
}