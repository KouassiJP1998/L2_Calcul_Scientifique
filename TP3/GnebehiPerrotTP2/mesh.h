#ifndef __Mesh_h
#define __Mesh_h

#include  <vector>
#include  <set>
#include  "fixvecteur.h"
#include  "vecteur.h"


/*----------------------------------------------------------*/

    class Mesh
    {
    protected:
      
        Vecteur<trinode>   _cells;
        std::string _name;
        Vecteur< node2d >   _nodes;
    public:
        Mesh(){}
        const trinode&  getCell(int i) const {return _cells[i];}
        trinode&  getCell(int i) {return _cells[i];}
        const node2d&   getNode(int i) const {return _nodes[i];}
        node2d&   getNode(int i) {return _nodes[i];}
        Vecteur<trinode>&   getCells() {return _cells;}
        const Vecteur<trinode>&  getCells() const {return _cells;}
        Vecteur<node2d>&   getNodes() {return _nodes;}
        const Vecteur<node2d>&   getNodes() const {return _nodes;}
        const std::string & getName() const {return _name;}
        std::string & getName() {return _name;}
        int getNCells()const {return _cells.size();}
        int getNNodes()const {return _nodes.size();}
        int getNodeIdOfCell(int ic, int in)const {return _cells[ic][in];}
        const node2d& getNodeOfCell(int ic, int in)const {return getNode(_cells[ic][in]);}
        void writeVtk(const std::string& filename) const;
        void readData(const std::string& filename);
        void writeData(const std::string& filename) const;
        double computeArea() const;


       };

#endif

    
