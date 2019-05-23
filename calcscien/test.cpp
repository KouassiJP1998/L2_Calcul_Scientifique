
#include <iostream>
#include "vecteur.h"
#include  <fstream>



using namespace  std;
/*----------------------------------------------------------*/
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
/*
@{param} omega : ensemble de caractère

*/
void combinaison(Vecteur<int>& clenum, int ideb, int k, const std::vector<int> &omega,const Vecteur<int>& textnum)
{
  if (k==0){
    Vecteur<int> txtDecodeNum;
    string a,b;
    decode(textnum,clenum,txtDecodeNum);
    //cout << indiceCoincidence(txtDecodeNum) << endl;
    textise(a,clenum);
    textise(b,txtDecodeNum);
    cout << a << "\t";
    cout << b;
    cout << '\n';
    return;
  }
  int n=omega.size();
  for (int i=0; i<n-k+1;i++){
    clenum[ideb]=omega[i];
    std::vector<int> subOmega(omega.begin()+i+1,omega.end());
    combinaison(clenum,ideb+1,k-1,subOmega,textnum);
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
    Vecteur<int> txtDecodeNum;
    string phrase;
    decode(textnum,clenum,txtDecodeNum);
    textise(phrase,txtDecodeNum);
    file << clenum << "\t" << phrase<< "\t" << indiceCoincidence(txtDecodeNum) << "\n";
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
  std::string indicecrypte="hgzqxqqpbbmtwumrbeqpysccbtmsccbtmumrbuqz";
  Vecteur<int> clenum1(2);
  Vecteur<int> indicecrypteNum;
  numerise(indicecrypte,indicecrypteNum);

  combinaison(clenum1,0,2,omega1,indicecrypteNum);

//exercice 2 : décryptage de la citation
  std::string omegastring2="abcdefghijklmnopqrstuvwxyz";
  Vecteur<int> omega2;
  numerise(omegastring2,omega2);
  std::string citation="usdfwduowziiosxpgalfpyhdnocusyliclwulaltgfysyqoyeofdgtrsytowbipwswpic";
  Vecteur<int> citationInt;
  numerise(citation,citationInt);
  arrangements(omega2,3,citationInt);


}
