#ifndef __Vecteur_h
#define __Vecteur_h

#include  <vector>
#include  <iostream>
#include  <iterator>
#include  <climits>
#include  <limits>
#include  <numeric>
#include  <cassert>
#include  <cmath>
#include  <sstream>

/*----------------------------------------------------------*/


  template<class T>
  class Vecteur : public std::vector<T>
  {
  public:

   /// Itérateur pour parcourir le vecteur
    typedef typename std::vector<T>::iterator       iterator;
   /// Itérateur pour parcourir le vecteur sans le modifier
    typedef typename std::vector<T>::const_iterator const_iterator;

  /// constructeur sans argument
    Vecteur() : std::vector<T>()    {}
  /// Contructeur par recopie
  /**
    * Le vecteur est dimensionné à la taille du vecteur à recopier
    * puis on recopie les valeurs grâce à l'opérateur =
    * @param v vecteur à recopier
    **/
    Vecteur(const Vecteur& v) : std::vector<T>(v) {
      reInit(v.size());
      *this = v;
    }
    /// Constructeur avec dimensionement du vecteur
    /**
      * Ce constructeur se contente de dimensionner le vecteur.
      * @param n dimension à donner au vecteur
      **/
    Vecteur(size_t n)               : std::vector<T>(n)   {}
    /// Constructeur qui dimensione le vecteur et initialise toutes les composantes à la valeur d
    /**
      * @param n est la dimension à donner au vecteur
      * @param d valeur à donner à chaque composante du vecteur
      **/
    Vecteur(size_t n, const T d)   : std::vector<T>(n,d) {}
    /// Constructeur par recopie d'un vecteur de type std::vector<T>
    /**
      * @param v est le vecteur de type std::vector<T> à recopier
      **/
    Vecteur(const std::vector<T>& v) : std::vector<T>(v)   {}

    /// Fonction renvoyant le nom de la classe
    /**
      * @return Le nom de la classe
      **/
    std::string getName() const { return "Vecteur<T>";}
    /// Fonction renvoyant la dimension du vecteur sous forme de chaîne de caractères
    /**
      * @return La dimension du vecteur sous forme de châine de caractères
      **/
    std::string getSize() const { std::stringstream ss; ss << Vecteur<T>::size(); return ss.str();}

    /// Opérateur d'écriture dans un fichier
    /**
      * @param s est un flux de sorties (un fichier en général)
      * @param A le vecteur à écrire
      * @return la référence du flux de sorties est renvoyé de manière à enchaîner les sorties
      **/
    friend std::ostream& operator<<(std::ostream &s, const Vecteur<T>& A)
    {
      if(!A.size()) return s;
      std::ostream_iterator<T>  os(s, " ");
      copy(A.begin(),A.end(),os);
      return s;
    }

    /// Opérateur de lecture dans un fichier
    /**
      * @param s est un flux d'entrées (un fichier en général)
      * @param A le vecteur à écrire
      * @return la référence du flux d'entrées est renvoyé de manière à enchaîner les lectures
      **/
    friend std::istream& operator>>(std::istream &s, Vecteur<T>& A)
    {
      iterator p = A.begin();
      while(p!=A.end())
          s >> *p++;
      return s;
    }

    /// Opérateur produit scalaire avec un Vecteur
    /**
      * Cet opérateur renvoie (this)*v
      *  @param v est un vecteur opérande du produit scalaire
      *  @return La valeur du produit scalaire
      **/
    T operator*(const Vecteur& v) const;


    /// Opérateur d'affectation
    /**
      * Cet opérateur initialise toutes les composantes à la valeur \e d
      *  @param d est un objet de type T permettant d'initialiser toutes les composantes du vecteur
      *  @return La reférence du vecteur pour enchaîner les opérateurs
    **/
    Vecteur<T>&   operator=(const T d) { equal(d); return *this; }

    /// Opérateur de recopie d'un vecteur de type std::vector<T>
    /**
      * Cet opérateur initialise recopie dans le vecteurun vecteur de type std::vector<T
      *  @param v est le vecteur à recopier dans (this)
      *  @return La reférence du vecteur pour enchaîner les opérateurs
      **/
    Vecteur<T>&   operator=(const std::vector<T>& v) { equal(v); return *this; }

    /// Opérateur multipliant chaque composante par le même scalaire
    /**
      * Toutes les composantes du vecteur sont multipliés par \e d.
      * @param d est l'objet de type T, par lequel on multiplie toutes les composantes du vecteur
      * @return La reférence du vecteur pour enchaîner les opérateurs
      **/
    Vecteur<T>&   operator*=(const T d);

    /// Opérateur ajoutant le même scalaire à chaque composante
    /**
      * On ajoute \e d à toutes les composantes du vecteur
      * @param d est l'objet de type T, que l'on ajoute à toutes les composantes du vecteur
      * @return La reférence du vecteur pour enchaîner les opérateurs
      **/
    Vecteur<T>&   operator+=(const T d) { add(d); return *this; }

    /// Opérateur somme de vecteurs
    /**
      * Il s'agit ici de la somme de deux vecteurs, composante à composante.
      * @param v est un vecteur de type Vecteur, que l'on ajoute à \e this composante à composante
      * @return La reférence du vecteur pour enchaîner les opérateurs
      **/
    Vecteur<T>&   operator+=(const Vecteur& v) { add(1,v); return *this; }

    /// Opérateur soustraction de vecteurs
    /**
      * Il s'agit ici de la soustraction de deux vecteurs, composante à composante.
      * @param v est un vecteur de type Vecteur, que l'on soustrait à \e this composante à composante
      * @return La reférence du vecteur pour enchaîner les opérateurs
      **/
    Vecteur<T>&   operator-=(const Vecteur& v) { add(-1,v); return *this; }

    /// Fonction d'initialisation du vecteur à zéro
    void   zero();

    /// Fonction d'initialisation de toutes les composantes à la valeur
    /**
      * (this)_i = d pour tout i
      * @param d est un scalaire de type T, servant à initialiser toutes les composantes du vecteur
      **/
    void   equal(const T d);

    /// Fonction de recopie d'un autre vecteur de type Vecteur
    /**
      * this = v
      * @param v est un vecteur de type Vecteur, que l'on recopie dans (this)
      **/
    void   equal(const Vecteur& v);

    /// Fonction initialisant le vecteur par d*v où d es vecteur de type Vecteur
    /**
      * this = d*v
      * Dans cette fonction le vecteur est initialisé par d*v où \e d est un scalaire de type T
      * et \e v est un autre vecteur de type Vecteur.
      * @param v est un vecteur de type Vecteur.
      * @param d est un coefficient multiplicatif de type T.
      **/
    void   equal(const T d, const Vecteur& v);

    /// Fonction initialisant le vecteur par la combinaison linéaire d1*v1 +d2*v2
    /**
      * this = d1*v1+d2*v2
      * Dans cette fonction le vecteur est initialisé par d1*v1+d2*v2 où \e d1 et \e d2 sont
      * des scalaires de type et \e v1 et \e v2 sont deux vecteurs de type Vecteur.
      * @param v1 est un vecteur de type Vecteur.
      * @param v2 est un vecteur de type Vecteur.
      * @param d1 est un coefficient multiplicatif de type T.
      * @param d2 est un coefficient multiplicatif de type T.
      **/
    void   equal(const T d1, const Vecteur& v1, const T d2, const Vecteur& v2);

    /// Fonction initialisant le vecteur par la combinaison linéaire d1*v1 +d2*v2 +d3*v3
    /**
      * this = d1*v1+d2*v2+d3*v3
      * Dans cette fonction le vecteur est initialisé par d1*v1+d2*v2+ d3*v3 où \e d1, \e d2 et \e d3
      * sont des scalaires de type et \e v1, \e v2 et \e v3 sont des vecteurs de type Vecteur.
      * @param v1 est un vecteur de type Vecteur.
      * @param v2 est un vecteur de type Vecteur.
      * @param v3 est un vecteur de type Vecteur.
      * @param d1 est un coefficient multiplicatif de type T.
      * @param d2 est un coefficient multiplicatif de type T.
      * @param d3 est un coefficient multiplicatif de type T.
      **/
    void   equal(const T d1, const Vecteur& v1, const T d2, const Vecteur& v2, const T d3, const Vecteur& v3);

    /// Fonction remplaçant le vecteur par la combinaison linéaire s*this +d*v
    /**
      * this= s*this + d*v
      * Les composantes du vecteur sont multipliées par \e s et on ajoute d*v composante à composante
      * @param s est un coefficent multicatif de type T par lequel on multiplie les composantes du vecteur this
      * @param d est un coefficent multicatif de type T par lequel on multiplie les composantes de \e v
      * @param v est un vecteur de type Vecteur
      **/
    void   sequ (const T s, const T d, const Vecteur& v);

    /// Fonction ajoutant un même scalaire à toutes les composantes
    /**
      * (this)_i = (this)_i + d
      * @param d valeur scalaire de type T que l'on ajoute à chaque composante du vecteur
      **/
    void   add  (const T d);

    /// Fonction ajoutant au vecteur la combinaison linéaire d*v
    /**
      * this = this +d*v
      * @param d scalaire de type T
      * @param v vecteur de type Vecteur
      **/
    void   add  (const T d, const Vecteur& v);

    /// Fonction ajoutant au vecteur la combinaison linéaire d1*v1 + d2*v2
    /**
      * this = this +d1*v1 + d2*v2
      * @param d1 scalaire de type T
      * @param d2 scalaire de type T
      * @param v1 vecteur de type Vecteur
      * @param v2 vecteur de type Vecteur
      **/
    void   add  (const T d1, const Vecteur& v1, const T d2, const Vecteur& v2);

    /// Fonction ajoutant au vecteur la combinaison linéaire d1*v1 + d2*v2 + d3*v3
    /**
      * this = this +d1*v1 + d2*v2 + d3*v3
      * @param d1 scalaire de type T
      * @param d2 scalaire de type T
      * @param d3 scalaire de type T
      * @param v1 vecteur de type Vecteur
      * @param v2 vecteur de type Vecteur
      * @param v3 vecteur de type Vecteur
      **/
    void   add  (const T d1, const Vecteur& v1, const T d2, const Vecteur& v2, const T d3, const Vecteur& v3);

    /// Fonction renvoyant le maximum du vecteur
    /**
      * @return le maximum de toutes les composantes du vecteur
      **/
    T max() const;

    /// Fonction renvoyant le minimum du vecteur
    /**
      * @return le minimum de toutes les composantes du vecteur
      **/
    T min() const;

    /// Fonction la somme des composantes du vecteur
    /**
      * @return la somme  des composantes du vecteur
      **/
    T sum() const;

    /// Fonction renvoyant la norme2 du vecteur
    /**
      * Cette fonction renvoie la norme du vecteur définie par
      * la racine carrée de la somme des composantes au carré.
      * @return la norme2 des composantes du vecteur
      **/
    const T  norm()     const;

    /// Fonction la norme1 du vecteur
    /**
      * Cette fonction renvoie la norme du vecteur définie par
      * la somme des valeurs absolues des composantes
      * @return la norme1 des composantes du vecteur
      **/
    const T  norm1()     const;

    /// Fonction renvoyant la norme2 du vecteur
    /**
      * Cette fonction renvoie la norme du vecteur définie par
      * la racine carrée de la somme des composantes au carré.
      * @return la norme2  des composantes du vecteur
      **/
    const T  norm2()     const;

    /// Fonction renvoyant la norme infinie du vecteur
    /**
      * Cette fonction renvoie la norme infinie du vecteur
      * définie par la plus grande composante en valeur absolue.
      * @return la norme infinie des composantes du vecteur
      **/
    const T  normInfty()     const;

    /// Fonction redimensionnant le vecteur
    /**
      * @param n est la taille que l'on souhaite donner au vecteur
      **/
    void reInit(size_t n)
    {
      std::vector<T>::reserve(n); std::vector<T>::resize(n);
    }

    /// Fonction redimensionnant le vecteur et initialisant les composantes à la même valeur \e d
    /**
      * @param n est la taille que l'on souhaite donner au vecteur
      * @param d est la valeur à donner aux composantes du vecteur
      **/
    void reInit(size_t n, const T d)
    {
      std::vector<T>::reserve(n); std::vector<T>::resize(n,d);
    }

    /// Fonction d'écriture binaire dans un fichier
    /**
      * @param out est le flux de sorties (généralement un fichier)
      * @return le flux de sorties pour enchaîner les écritures
      **/
    std::ostream& writeBin(std::ostream& out) const;

    /// Fonction de lecture binaire dans un fichier
    /**
      * @param in est le flux d'entrées (généralement un fichier)
      * @return le flux d'entrées pour enchaîner les lectures
      **/
    std::istream& readBin (std::istream& in);

    /// Fonction d'écriture dans un fichier
    /**
      * Cette fonction permet d'écrire le vecteur dans un fichier.
      * Deux format sont possibles: ascii ou binary.
      * Le fichier créé peut être relu par la fonction read()
      * @param out est le flux de sorties (généralement un fichier)
      * @param datatype est une chaîne de caractères précisant le format de sortie
      * @return le flux de sorties pour enchaîner les écritures
      **/
    std::ostream& write(std::ostream& out, const std::string& datatype="binary") const;

    /// Fonction de lecture dans un fichier des vecteurs de Map
    /**
      * @param in est le flux d'entrées (généralement un fichier)
      * @return le flux d'entrées pour enchaîner les lectures
      **/
    std::istream& readMapVector(std::istream& in);

    /// Fonction d'écriture dans un fichier des vecteurs de Map
    /**
      * @param out est le flux de sorties (généralement un fichier)
      * @return le flux de sorties pour enchaîner les écritures
      **/
    std::ostream& writeMapVector(std::ostream& out) const;

    /// Fonction de lecture du vecteur dans un fichier
    /**
      * Cette fonction permet de relire les fichiers créés par la fonction write().
      * Deux formats sont possibles: ascii et binary.
      * @param in est le flux d'entrées (généralement un fichier)
      **/
    void read (std::istream& in);
  };


/*----------------------------------------------------------*/

template<class T>
  inline const T Vecteur<T>::norm() const
  {
    const_iterator first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    T d(0);
    if(first==last) return d;
    while( first != last)
    {
      d += ((*first)) * ((*first));
      first++;
    }
    return std::sqrt(d);
  }

/*----------------------------------------------------------*/

template<class T>
  inline T Vecteur<T>::sum() const
  {
    const_iterator first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    T n(0);
    while( first != last)
    {
      n += (*first++);
    }
    return n;
  }

/*----------------------------------------------------------*/

template<class T>
  inline const T Vecteur<T>::norm1() const
  {
    const_iterator first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    T n(0);
    while( first != last)
    {
      n += fabs((*first++));
    }
    return n;
  }

/*----------------------------------------------------------*/

template<class T>
  inline const T Vecteur<T>::norm2() const
  {
    const_iterator first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    T n(0);
    if(first==last) return n;
    while( first != last)
    {
      n += ((*first)) * ((*first));
      first++;
    }
    return std::sqrt(static_cast<double>(n));
  }

/*----------------------------------------------------------*/

template<class T>
  inline const T Vecteur<T>::normInfty() const
  {
    const_iterator first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    T d(0);
    while( first != last)
    {
      d = max(d,fabs(*first));
      first++;
    }
    return d;
  }

/*----------------------------------------------------------*/

template<class T>
  inline Vecteur<T>& Vecteur<T>::operator*=(const T d)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    while(first != last)
    {
      (*first++) *= d;
    }
    return *this;
  }

/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::zero()
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    while( first != last)
    {
      *first++ = 0;
    }
  }

/*----------------------------------------------------------*/

template<class T>
  inline T Vecteur<T>::max() const
  { 
    T d = std::numeric_limits<T>::min();
    const_iterator first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    while( first != last)
    {
      d = max( d, (*first++));
    }
    return d;
  }

/*----------------------------------------------------------*/

template<class T>
  inline T Vecteur<T>::min() const
  {
    T d = std::numeric_limits<T>::max();
    const_iterator first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    while( first != last)
    {
      d = min( d, (*first++));
    }
    return d;
  }

/*----------------------------------------------------------*/

template<class T>
  inline T Vecteur<T>::operator* (const Vecteur<T>& v) const
  {
    const_iterator first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    const_iterator first2 = v.begin();

    T d(0);
    while(first != last)
    {
      d += (*first++) * (*first2++);
    }
    return d;
  }


/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::equal (const T d)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    while(first != last)
    {
      (*first++) = d;
    }
  }
/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::equal(const Vecteur<T>& v)
  {
    assert(std::vector<T>::size()==v.std::vector<T>::size());
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    const_iterator vfirst = v.std::vector<T>::begin();

    while( first != last)
    {
      *first++ = *vfirst++;
    }
  }

/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::equal (const T d, const Vecteur<T>& v)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    const_iterator first2 = v.begin();

    while(first != last)
    {
      (*first++) = d*(*first2++);
    }
  }

/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::equal (const T d, const Vecteur<T>& v,
    const T e, const Vecteur<T>& w)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    const_iterator first2 = v.begin();
    const_iterator first3 = w.begin();

    while(first != last)
    {
      (*first++) = d*(*first2++) + e*(*first3++);
    }
  }

/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::equal (const T d, const Vecteur<T>& v,
    const T e, const Vecteur<T>& w,
    const T f, const Vecteur<T>& x)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    const_iterator first2 = v.begin();
    const_iterator first3 = w.begin();
    const_iterator first4 = x.begin();

    while(first != last)
    {
      (*first++) = d*(*first2++) + e*(*first3++) + f*(*first4++);
    }
  }

/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::sequ (const T s, const T d, const Vecteur<T>& v)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    const_iterator first2 = v.begin();

    while(first != last)
    {
      (*first) = s*(*first) + d*(*first2++);
      first++;
    }
  }

/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::add (const T d)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();

    while(first != last)
    {
      (*first++) += d;
    }
  }

/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::add (const T d, const Vecteur<T>& v)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    const_iterator first2 = v.begin();

    while(first != last)
    {
      (*first++) += d*(*first2++);
    }
  }

/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::add (const T d, const Vecteur<T>& v,
    const T e, const Vecteur<T>& w)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    const_iterator first2 = v.begin();
    const_iterator first3 = w.begin();

    while(first != last)
    {
      (*first++) += d*(*first2++) + e*(*first3++);
    }
  }

/*----------------------------------------------------------*/

template<class T>
  inline void Vecteur<T>::add (const T d, const Vecteur<T>& v,
    const T e, const Vecteur<T>& w,
    const T f, const Vecteur<T>& x)
  {
    iterator  first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    const_iterator first2 = v.begin();
    const_iterator first3 = w.begin();
    const_iterator first4 = x.begin();

    while(first != last)
    {
      (*first++) += d*(*first2++) + e*(*first3++) + f*(*first4++);
    }
  }

    /*----------------------------------------------------------*/

template<class T>
  inline std::ostream& Vecteur<T>::writeBin(std::ostream& out) const
  {
    out.write(reinterpret_cast<const char*>(&(*this)[0]),this->size()*sizeof(T));
    return out;
  }

/**********************************************************/

template<class T>
  inline std::istream& Vecteur<T>::readBin(std::istream& in)
  {
    in.read(reinterpret_cast<char*>(&(*this)[0]),this->size()*sizeof(T));
    return in;
  }

/*----------------------------------------------------------*/

template<class T>
  inline std::ostream& Vecteur<T>::write(std::ostream& out, const std::string& datatype) const
  {
    out <<  Vecteur<T>::size() << " "  << datatype << " " << std::endl;
    if(datatype=="ascii")
    {
      out << *this;
    }
    else
    {
      writeBin(out);
    }
    return out;
  }
  /**********************************************************/

template<class T>
  inline std::istream& Vecteur<T>::readMapVector(std::istream& in)
  {
    int n;
    std::string datatype;
    in >> n  >> datatype;
    reInit(n);
    iterator first  = std::vector<T>::begin();
    iterator last   = std::vector<T>::end();
    while(first != last)
    {
      (*first).read(in);
      first++;
    }
    return in;
  }
    /**********************************************************/

template<class T>
  inline std::ostream& Vecteur<T>::writeMapVector(std::ostream& out) const
  {
    out <<  Vecteur<T>::size() << " "  << "ascii" << " " << std::endl;
    const_iterator first  = std::vector<T>::begin();
    const_iterator last   = std::vector<T>::end();
    while(first != last)
    {
      (*first).write(out,"ascii");
      first++;
    }
    return out;
  }
/**********************************************************/

template<class T>
  inline void Vecteur<T>::read(std::istream& in)
  {
    int n;
    std::string datatype;
    in >> n  >> datatype;
    reInit(n);
    if(datatype=="ascii")
    {
      in >> *this;
    }
    else if(datatype=="binary")
    {
      readBin(in);
    }
    else
    {
      std::cerr << "*** Vecteur<T>::read() : wrong datatype \"" << datatype << "\"\n";
      assert(0);
    }

  }

#endif
