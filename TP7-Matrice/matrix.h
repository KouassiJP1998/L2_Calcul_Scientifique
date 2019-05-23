#include "vecteur.h"
#include <iostream>

using namespace std;

class Matrix : public Vecteur<double>{
	public :
		int lig;
		int col;

		Matrix();	//Constructeur par défaut
		~Matrix();	//Destructeur
		
		//Redéfinition des opérateurs :
		double operator()(int x, int y){
			return((*this)[col*x+y]);
		}	//Accés à l'élément en position (i,j) de la matrice.

		void operator=(Matrix &m){	//En écriture
			for(int i=0; i < lig; i++){
				for(int j=0; j < col; j++){
					(i,j) = m(i,j);
				}
			}
		}//Recopie entre deux matrices.

		void reInit(int nl , int nc){
			//nl : nbLignes
			//nc : nbCol

			int n = nl * nc;
			Vecteur<double>::reInit(n);
		} //Dimmensionnement de la matrice.

		void zero(){
			for(int i=0; i < lig; i++){
				for(int j=0; j < col; j++){
					(i,j) = 0;
				}
			}
		} //Mise à zéro des valeurs de la matrice.

		void linearCombi(double alpha, Matrix A, double beta, Matrix B);	//C.linearCombi(ALPHA, m1, BETA, m2), où C est une matrice

		void productMatCol(const Matrix& X, Matrix& Y){	//Exemple d'appel : A.productMatCol(X,Y)
		
		}

		void productMat(Matrix &mparam){	//Produit de la matrice par une matrice donnée en paramètre
			for(int i=0; i < lig; i++){
				for(int j=0; j < col; j++){
					(i,j) = (i,j)*mparam(i,j);
				}
			}
		}

		void productMat2(Matrix &m1, Matrix &m2){	//Initialisation d'une matrice par le produit de deux matrices
			for(int i=0; i < lig; i++){
				for(int j=0; j < col; j++){
					(i,j) = m1(i,j)*m2(i,j);
				}
			}
		}
};
