#include <iostream>
#include <cmath>
#include <stack> // pile
#include <vector>

using namespace std;

vector<int> toBaseB(int n,int b){
  int res;
  stack<int> s;
  vector<int> v;
  res = n;
  while(res != 0){
    s.push(res%b);
    res = res/b;
  }

  while(s.size() < b){
    s.push(0);
  }

  while(!s.empty()){
    v.push_back(s.top());
    s.pop();
  }
  return v;
}

void convertir(vector<char> &c,int l){
  long key = pow(c.size(),l);
  cout <<"key vaut : " << key << '\n';
  for (int i = 0; i < key; i++) {
    vector<int> map = toBaseB(i,c.size());
    cerr << "" << '\n';
    for (int j = c.size()-l; j < map.size(); j++) {
      cout << c[map[j]];
    }
    cout << "" << endl;
  }
}

int main() {
  char meschar[] = {'A','B','C','D'};
  vector<char> phrase (meschar, meschar + sizeof(meschar) / sizeof(char) );
  //vector<char> phrase = {'A','B','C','D'};
  convertir(phrase,2);
  return 0;
}
