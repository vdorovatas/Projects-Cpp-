#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;


template <typename C>
void print (C &v) {
  for(auto x: v)
  cout << x << endl;
}

int main () {
  vector<int> v;
  for(int i=1;i<6;++i) v.push_back(i);
  list<int> l;
  for(int i=1;i<6;++i) l.push_back(i);
  list<string> ls;
  ls.push_back("one");
   ls.push_back("two");
    ls.push_back("three");
  print(v);
  print(l);
  print(ls);
}