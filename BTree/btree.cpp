#include <iostream>
#include <string>

using namespace std;

class lexicon {
class node {
public:
string word;
int freq;
int dep;
node *right,*left;
node(const string &s, node *l, node *r,int d) : word(s),left(l), right(r), dep(d),
 freq(1) {};
};
node *root;

int preorder (node *t, const string &s, int k) {
  if (s == t->word) {
    if(k==0) { return t->freq; }
    if(k==1) { return t->dep; }
    }
  preorder(t->left, s, k);
  preorder(t->right, s, k);
  return 0;
}


public:
  lexicon() {
    root=NULL;
  }

  ~lexicon();

  void insert(const string &s) {
    node *p;
    p=root;
    node *n=new node(s,NULL,NULL,0);
    while(1==1) {
      if(s == p->word) { ++p->freq; delete n; break; }
      if(s < p->word) {
        if(p->left==NULL) { p->left=n; n->dep=(p->dep+1); break; }
        p=p->left;
      }
      if(s > p->word) {
        if(p->right==NULL) { p->right=n; n->dep=(p->dep)+1; break; }
        p=p->right;
      }
    }
  }

  int lookup (const string &s) {
    node *p;
    p=root;
  preorder(p, s, 0);
  }

  int depth (const string &s) {
    node *p;
    p=root;
    preorder(p, s, 1);
  }


};
