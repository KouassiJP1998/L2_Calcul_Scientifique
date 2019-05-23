#ifndef  __FixVecteur_h
#define  __FixVecteur_h

#include  <stdlib.h> 
#include  <iostream>
#include  <vector>

/*-------------------------------------------------*/
template <int N,typename T >
class FixVecteur: public std::vector <T>
{

 public:
  
  FixVecteur<N,T>():std::vector<T>(N){}
  FixVecteur<N,T>(const std::vector<T> v):std::vector<T>(v){}

  const T & operator()(int i) const
  {
    return (*this)[i];
  }

  T & operator()(int i)
  {
    return (*this)[i];
  }
};
 
template <int N,typename T >
 std::ostream & operator << (std::ostream & os, const FixVecteur<N,T>& v)
{
   for (int i=0;i<N;i++)
   {
     os<<v[i]<<" ";
   }
   return os;
}
template <int N,typename T >
 std::istream & operator >> (std::istream & is, FixVecteur<N,T>& v)
{
   for (int i=0;i<N;i++)
   {
     is>>v(i);
   }
   return is;
}

typedef FixVecteur<2,double> node2d;
typedef FixVecteur<3,int> trinode;


#endif


