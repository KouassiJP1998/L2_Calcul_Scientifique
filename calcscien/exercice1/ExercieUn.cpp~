#include <iostream>
#include <cmath>
#include <cstdio>
#include <fstream>

using namespace std;

const double grav = 9.81; 
const double coef = 2.0;

double methodeEuler(double temps,double masse,int nbI){
  double vitesse = 0.0;
  double delta = temps/nbI;

  for (double i = 0.0; i < temps; i++) {
    vitesse = ((((-coef)*vitesse*vitesse + masse*grav)/masse)*delta)+vitesse;
  }

  return vitesse;
}

int CSV(){
  ofstream monFichier;
      monFichier.open ("fichier.csv");
      monFichier << "\"T\",\"V\""<<endl;

      for (double i = 0.0; i < 100; i++) {
        monFichier << methodeEuler(2*i,70.0,180) << "," <<methodeEuler((2*i)+1,70.0,180)<< '\n';

      }
      monFichier.close();
      return 0;
}

int main() {
  cout << methodeEuler((3.0*60.0),70.0,1800) << '\n';
  CSV();
  return 0;
}
