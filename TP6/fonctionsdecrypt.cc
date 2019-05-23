
#include <iostream>
#include "vecteur.h"
#include  <fstream>



using namespace  std;
/*----------------------------------------------------------*/
// UTILITE : Permet de tester une clé donnée
void decode(const Vecteur<int>&  textnum, const Vecteur<int> & clenum, Vecteur<int> & textdecodenum)
{
  int n=textnum.size();
  int nc=clenum.size();
  int p=n/nc;
  int r=n%nc;
  int count=0;
  textdecodenum.reInit(n);
  textdecodenum=textnum;
  for (int i=0; i<p; i++)
  {
    for (int ic=0; ic<nc; ic++)
    {
      textdecodenum[count]-=clenum[ic];
      if(textdecodenum[count]<0) textdecodenum[count]+=26;
      count++;
    }
  }
  for (int i=0; i<r; i++)
  {
    textdecodenum[p*nc+i]-=clenum[i];
    if(textdecodenum[p*nc+i]<0) textdecodenum[p*nc+i]+=26;
  }
}
/*----------------------------------------------------------*/
//UTILITE : Donne l'indice de coïncidence d'une phrase numérisée
double indiceCoincidence(const Vecteur<int> & textnum)
{
  int n=textnum.size();
  Vecteur<int> x;
  x.reInit(26);
  x.zero();
  for (int i=0; i<n; i++)
  {
    x[textnum[i]]++;
  }
  double ic=0.0;
  for (int i=0; i<26; i++)
  {
    ic=ic+double(x[i]*(x[i]-1.0));
  }
  ic= ic/double(n)/double(n-1);
  return ic;
}
/*----------------------------------------------------------*/

void numerise(const string& text,Vecteur<int>& textnum )
{
  textnum.reInit(text.length());
  for (int i=0; i<text.length(); i++)
  {
    textnum[i]=int(text[i])-int('a');
  }
}
/*----------------------------------------------------------*/
void textise(string& text,const Vecteur<int>& textnum)
{
  text="";
  for (int i=0; i<textnum.size(); i++)
  {
    text.push_back(char(textnum[i]+int('a')));
  }
}



/*---------------------------------------------------------*/
void combinaison(Vecteur<int>& clenum, int ideb, int k, const std::vector<int> &omega,const Vecteur<int>& textnum)
{
  if (k==0)
  {
    Vecteur<int> txtdecode;
    string x,y;
    decode(textnum,clenum,txtdecode);

    //Indice de coïncidence
    cout << indiceCoincidence(txtdecode) << endl;

    textise(x,clenum);
    textise(y,txtdecode);
    cout << x << "  ";
    cout << y << endl;
    cout << "" << endl;
    return;
  }

  int n=omega.size();
  for (int i=0; i<n-k+1;i++)
  {
    clenum[ideb]=omega[i];
    vector<int> subOmega(omega.begin()+i+1,omega.end());//Permet grâce à la librairie Vecteur de tronqué la partie de gauche à partir d'un indice
    combinaison(clenum,ideb+1,k-1,subOmega,textnum);//Récursivité
  }

}


/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
void _conversion(int n, int b, Vecteur<int>& v)
{
  for(int i=v.size()-1; i>=0;i--)
  {
    v[i]=n%b;
    n=n/b;
  }

}
void arrangements(const Vecteur<int>& omeganum, int clelong, const Vecteur<int>& textnum)
{
  ofstream file;
  file.open("decript.txt");
  Vecteur<int> clenum(clelong);
  int b=omeganum.size();
  int N = pow(b, clelong);
  Vecteur<int> textdecodenum(textnum.size());
  for(int i=0; i<N; i++)
  {
    _conversion(i, b, clenum);
    Vecteur<int> txtdecode;
    string phrase;
    decode(textnum,clenum,txtdecode);
    textise(phrase,txtdecode);
    file << clenum << "\t" << phrase << "\t" << indiceCoincidence(txtdecode) << "\n";
  }
  file.close();
}
/*---------------------------------------------------------*/
int main()
{
  // exercice 1 : décryptage de l'IC
  std::string omegastring1="aeibcd";
  Vecteur<int> omega1;
  numerise(omegastring1,omega1);
  std::string indicecrypte="hgzqxqqpbbmtwpmwnumrbjckbpmwnfmwfpmwn";
  //Clé de taille 2
  Vecteur<int> cle1(2);
  Vecteur<int> indiceCryptage;
  numerise(indicecrypte,indiceCryptage);

  combinaison(cle1,0,2,omega1,indiceCryptage);

  // exercice 2 : décryptage de la citation
  std::string omegastring2="abcdefghijklmnopqrstuvwxyz";
  Vecteur<int> omega2;
  numerise(omegastring2,omega2);
  std::string citation="gazcmwdwrgwdemizszsfxijiskxrsruwvsmwswwgscsrpojsilmbwizdiskxagvhwpzw";

  Vecteur<int> decryptCitation;
  numerise(citation,decryptCitation);
  arrangements(omega2,3,decryptCitation);
  
  //0.0750751 ic  zeropointzeroneufsepthuitneufdeuxneuf
  //Indice trouvé : 0.0978929
  //Résultats avec cet indice : 26
  //Ligne : 9937
  //Phrase/Citation : Si vous pensez que l'aventure est dangereuse essayez la routine elle est mortelle
}
