#include <cmath>
#include <iostream>

using namespace std;

double f(double x){
	return (x*x*x*x*x);
}

double formuleBoole(double a, double b, int N){
	double s=0.0;
	double x1=a, x2;
	double h=(b-a)/N;
	
	for(int i=0; i<N; i++){
		x2=x1+h;

		s = s + 7.0*f(x1) + 32.0* f((3*x2 + x1)/4)  + 12.0*f((x1+x2)/2) + 32.0*f((3*x1 + x2)/4) + 7.0*f(x2);
		//			Borne a 					Borne 1/4						Milieu						Borne 3/4						Borne b

		x1=x2;
	} 
	s = (s*h)/90.0;
	return s;
}

int main() {
  cout<<" "<<endl;
  cout<<"PERROT JOSUAH, GNEBEHI BAGRE (L2 Informatique)"<<endl;
  cout<<"----- FORMULE DE BOOLE -----"<<endl;
  cout<<" "<<endl;
  cout<<"N = 10:"<<endl;
  cout<<formuleBoole(0,1,10)<<endl;

  cout<<" "<<endl;

  cout<<"N = 20:"<<endl;
  cout<<formuleBoole(0,1,20)<<endl;

  cout<<" "<<endl;
  cout<<"Intégral exact : "<< 1.00/6.00 << endl;
  cout<<"Degré d'exactitude : 5"<<endl;
  cout<<"Ordre de la méthode : 6"<<endl;
  cout<<" "<<endl;
  cout<<"-----------------------------"<<endl;
  return 0;
}
