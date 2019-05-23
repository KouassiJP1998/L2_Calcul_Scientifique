#include "matrix.h"
/*---------------------------------------------------------*/
int main()
{
//  test 
  Matrix A,B,L,U;
  L.reInit(3,3);
  U.reInit(3,3);
  A.reInit(3,3);
  B.reInit(3,3);

  //Instanciation de toutes les matrices à O
  L.zero();
  U.zero();
  A.zero();
  B.zero();

  A(0,0)=4;A(0,1)=1;A(0,2)=1;
  A(1,0)=2;A(1,1)=5;A(1,2)=1;
  A(2,0)=3;A(2,1)=1;A(2,2)=9;

  B(0,0)=0;B(0,1)=1;B(0,2)=1;
  B(1,0)=2;B(1,1)=5;B(1,2)=1;
  B(2,0)=3;B(2,1)=1;B(2,2)=9;

  std::cerr<<"********************************************"<<'\n';
  //Test sur la matrice A :
  std::cerr<<"Matrice A : \n"<<A<<'\n';
  A.LUv1(L,U);
  std::cerr<<"Matrice L après A.LUv1(L,U) : \n"<<L<<'\n';
  std::cerr<<"Matrice U après A.LUv1(L,U) : \n"<<U<<'\n';

  //Test sur la matrice B :
  std::cerr<<"Matrice B : \n"<<B<<'\n';
  B.LUv1(L,U);
  std::cerr<<"Matrice L après B.LUv1(L,U) : \n"<<L<<'\n';
  std::cerr<<"Matrice U après B.LUv1(L,U) : \n"<<U<<'\n';
}
