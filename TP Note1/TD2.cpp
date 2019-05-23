#include <iostream>
#include <math.h>

using namespace std;

//Exercice 1.1 :

//f renvoi sin(x)
double f(double x){
	return (sin(x)); 
}

double ptsMilieux(double a, double b, int N){
	double v = 0.0;
	double x1 = a;
	double x2;
	double h = (b-a)/N;

	for(int i=0; i<N; i++){
		//Parcours des sous intervalles
		x2 = x1+h;
		v += f((x1+x2/2));
		//La borne de gauche devient la borne de droite
		x1 = x2;
	}
	v *= h;
	return (v);
}

double trapeze(double a, double b, int N){
	double v = 0.0;
	double h = (b-a)/N;

	for(int i=0; i<N; i++){
		v += (f(i)+f(i+h))/2;
	}
	v *= h;
	return(v);
}

double simpson(double a, double b, int N){
	double v = 0.0;
	double h = (b-a)/N;
	double x1,x2,x3;

	x1 = (1.0/6.0);
	x2 = (1.0/6.0);
	x3 = (2.0/3.0);

	for (int i=0; i<N ; i++){
		v += x1 * f(i) + x2 * f(i+h) + x3 * f((2*i+h)/2);
	}

	v *= h;
	return(v);

}

void erreurMilieu(){
	for (int i=10; i<=30; i=i+5){
		cout << " " << endl;
		cout << "N = " << i << endl;
		cout << "Appel de ptsMilieux : " << fabs(0.5 - ptsMilieux(0.0,M_PI,i)) << endl;
		cout << "Appel de trapeze : " << fabs(0.5 - trapeze(0.0,M_PI,i)) << endl;
		cout << "Appel de simpson : " << fabs(0.5 - simpson(0.0,M_PI,i)) << endl;
	}

}

int main(){
	double a = 0;
	//M_PI = Valeur de pi renvoyée grâce à l'include math.h
	double b = M_PI/3;
	int N = 50;

	//Point Milieu
	cout << "Appel de ptsMilieux, valeur retournée : " << ptsMilieux(a,b,N) << endl;
	
	//Trapèze
	cout << "Appel de trapeze, valeur retournée : " << trapeze(a,b,N) << endl;

	//Simpson
	cout << "Appel de simpson, valeur retournée : " << simpson(a,b,N) << endl;

	//Erreur Milieu
	cout << "---------- DEBUT DES TESTS ----------" << endl;
	erreurMilieu();
	cout << " " << endl;
	cout << "---------- FIN DES TESTS ----------" << endl;
	return(0);

}