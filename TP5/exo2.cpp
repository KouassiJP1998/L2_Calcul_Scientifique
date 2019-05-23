#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double coefficientBinomial(int a,int b,int k,int n,int *r){
  int i = 0;

  a = 1;
  b = 1;
  *r = 0;

  for(i = (n - k+1); i<=n; i++){
    a*=i;
  }

  for(i = 2; i <= k; i++){
      b*=i;
  }

  *r = a/(b);

  return 0;
}


int main() {
  int a,b,k,n,r,s;

  //Saisie par l'utilisateur
  cout << "Choix de l'utilisateur : " << endl;
  cout << "n = ";
  cin >> n;

  cout << "" << endl;
  cout << "Coefficients binomiaux : " << endl;

  //Affichage avec appels
  for(k = 0; k <= n; k++){
    coefficientBinomial(a,b,k,n,&r);
    cout << "(" << r << " * (x^" << n-k << ") * (y^" << k << "))" << endl;
    if(k<n){
      cout << " + " << endl;
    }
  }
  return (0);
}
