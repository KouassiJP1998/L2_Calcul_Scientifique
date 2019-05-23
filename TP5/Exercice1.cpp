#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void conversion(vector<int> &c, int b, int n, int p){
	int i = 1;
	int j = 0;

	while(n!=0){
		c[p-i] = n%b;
		n = n/b;
		i++;
	}

	while(i <= p){
		c[p-i] = 0;
		i++;
	}

	//Boucle d'affichage du vecteur
	for(j=0; j < p; j++){
		//cout << c[j];
		if(c[j] == 0){
			cout << "A";
		}

		if(c[j] == 1){
			cout << "B";
		}

		if(c[j] == 2){
			cout << "C";
		}

		if(c[j] == 3){
			cout << "D";
		}
	}

	cout << endl;
}

void encryptage(vector<int> &c){	
	int i;
	int b = 4; //Taille d'Omega
	int p = 3;	//Taille de la chaine / combinaison

	int N = pow(b,p);

	for(i = 0; i < N-1; i++){
		conversion(c,4,i,3);
	}
	cout << "Nombre de clefs : " << i << endl;
}

int main(){
	int baseDest = 4;
	int tailleVecteur = 4;

	vector<int> monVecteur(tailleVecteur);
	int nombreAConvertir = 45;

	encryptage(monVecteur);
	//cin >> nombreAConvertir;

	//Exercice 1 :
	//conversion(monVecteur, baseDest, nombreAConvertir, tailleVecteur);

  	return(0);
}
