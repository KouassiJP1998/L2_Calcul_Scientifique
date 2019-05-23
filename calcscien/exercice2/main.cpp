#include <iostream>
#include <cmath>

using namespace std;

double equationDifferentielle(double t, double y){
  return(t-(t*y));
}

int main() {
  double k1,k2,k3;
  double t=0.0;
  double y=2.0;
  double dt=0.01;

  for(int i=0;i<10 ;i++){
    k1=equationDifferentielle(t,y);

    k2=equationDifferentielle(t+dt/2,y+k1*dt/2);

    k3=equationDifferentielle(t+dt,y-k1*dt+2*k2*dt);

    y=y+k1/6+2*k2/3+k3/6;

    t=t+dt;
  };

  cout << "Valeur de y : " << y << endl;

  return 0;
}